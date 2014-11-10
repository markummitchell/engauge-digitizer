#include "CallbackAngleAbstractBase.h"
#include <QFile>
#include <QTextStream>

using namespace std;

const double DEG_2_RAD = 3.1415926535 / 180.0;

CallbackAngleAbstractBase::CallbackAngleAbstractBase (int histogramSize,
                                                      double angleRadians,
                                                      const QString &xOrY) :
  m_histogramSize (histogramSize),
  m_arraySize (2 * histogramSize - 1),
  m_angleRadians (angleRadians),
  m_xOrY (xOrY)
{
  m_histogram = new int [histogramSize];

  for (int bin = 0; bin < histogramSize; bin++) {
    m_histogram [bin] = 0;
  }

  m_histogramU = (fftw_complex *) fftw_malloc(sizeof (fftw_complex) * m_arraySize);
  m_histogramT = (fftw_complex *) fftw_malloc(sizeof (fftw_complex) * m_arraySize);
  m_patternU = (fftw_complex *) fftw_malloc(sizeof (fftw_complex) * m_arraySize);
  m_patternT = (fftw_complex *) fftw_malloc(sizeof (fftw_complex) * m_arraySize);
  m_correlationU = (fftw_complex *) fftw_malloc(sizeof (fftw_complex) * m_arraySize);
  m_correlationT = (fftw_complex *) fftw_malloc(sizeof (fftw_complex) * m_arraySize);
}

CallbackAngleAbstractBase::~CallbackAngleAbstractBase ()
{
  fftw_destroy_plan (m_planHisto);
  fftw_destroy_plan (m_planPattern);
  fftw_destroy_plan (m_planCorrelation);
  fftw_free (m_histogramU);
  fftw_free (m_histogramT);
  fftw_free (m_patternU);
  fftw_free (m_patternT);
  fftw_free (m_correlationU);
  fftw_free (m_correlationT);

  fftw_cleanup();

  delete m_histogram;
}

double CallbackAngleAbstractBase::correlation (double period,
                                               int gridlineCount)
{
  int bin;

  loadNonHistogramArrays (gridlineCount, period);

  fftw_execute (m_planPattern);

  fftw_complex scale = {1.0 / m_arraySize, 0};

  double maxCorrelation = 0.0;
  for (bin = 0; bin < m_arraySize; bin++) {
    hConjPScale (m_histogramT [bin],
                 m_patternT [bin],
                 scale,
                 m_correlationT [bin]);
  }

  fftw_execute (m_planCorrelation);

  for (bin = 0; bin < m_arraySize; bin++) {
    double real = m_correlationU [bin] [0];
    double imag = m_correlationU [bin] [1];
    double magnitude = sqrt (real * real + imag * imag);
    if (magnitude > maxCorrelation) {
      maxCorrelation = magnitude;
    }
  }

#ifdef OUTPUTS
  QString filenameUP = QString ("patternU_%1_%2_%3.tsv")
      .arg (m_xOrY)
      .arg (m_angleRadians / DEG_2_RAD)
      .arg (gridlineCount);
  QString filenameTP = QString ("patternT_%1_%2_%3.tsv")
      .arg (m_xOrY)
      .arg (m_angleRadians / DEG_2_RAD)
      .arg (gridlineCount);
  QString filenameUC = QString ("correlationU_%1_%2_%3.tsv")
      .arg (m_xOrY)
      .arg (m_angleRadians / DEG_2_RAD)
      .arg (gridlineCount);

  outputComplexArray(m_patternU,
                     filenameUP);
  outputComplexArray(m_patternT,
                     filenameTP);
  outputComplexArray(m_correlationU,
                     filenameUC);
#endif

  return maxCorrelation;
}

void CallbackAngleAbstractBase::hConjPScale (const fftw_complex &h,
                                             const fftw_complex &p,
                                             const fftw_complex &scale,
                                             fftw_complex &correlation)
{
  double hConjP [2];
  hConjP [0] = h[0] * p[0] + h[1] * p[1];
  hConjP [1] = h[1] * p[0] - h[0] * p[1];

  correlation[0] = hConjP[0] * scale[0] - hConjP[1] * scale[1];
  correlation[1] = hConjP[1] * scale[0] + hConjP[0] * scale[1];
}

int CallbackAngleAbstractBase::histogramSize () const
{
  return m_histogramSize;
}

void CallbackAngleAbstractBase::incrementHistogramBin (int bin)
{
  Q_ASSERT (bin < histogramSize ());

  ++m_histogram [bin];
}

void CallbackAngleAbstractBase::initialize()
{
  loadHistogramArray ();

  m_planHisto = fftw_plan_dft_1d (m_arraySize, m_histogramU, m_histogramT, FFTW_FORWARD, FFTW_ESTIMATE);
  m_planPattern = fftw_plan_dft_1d (m_arraySize, m_patternU, m_patternT, FFTW_FORWARD, FFTW_ESTIMATE);
  m_planCorrelation = fftw_plan_dft_1d (m_arraySize, m_correlationT, m_correlationU, FFTW_BACKWARD, FFTW_ESTIMATE);

  fftw_execute (m_planHisto);

#ifdef OUTPUTS
  QString filenameUH = QString ("histogramU_%1_%2.tsv")
      .arg (m_xOrY)
      .arg (m_angleRadians / DEG_2_RAD);
  QString filenameTH = QString ("histogramT_%1_%2.tsv")
      .arg (m_xOrY)
      .arg (m_angleRadians / DEG_2_RAD);

  outputComplexArray(m_histogramU,
                     filenameUH);
  outputComplexArray(m_histogramT,
                     filenameTH);
#endif
}

void CallbackAngleAbstractBase::loadHistogramArray ()
{
  for (int bin = 0; bin < m_arraySize; bin++) {
    if (bin < m_histogramSize) {
      m_histogramU [bin] [0] = m_histogram [bin];
    } else {
      m_histogramU [bin] [0] = 0.0;
    }
    m_histogramU [bin] [1] = 0.0;
    m_histogramT [bin] [0] = 0.0;
    m_histogramT [bin] [1] = 0.0;
  }

  spreadPeaks (m_histogramU);

  normalizeArray (m_histogramU);
}

void CallbackAngleAbstractBase::loadNonHistogramArrays (int gridlineCount,
                                                        double period)
{
  const double PEAK_VALUE = 1.0;

  for (int bin = 0; bin < m_arraySize; bin++) {
    m_patternU [bin] [0] = 0.0;
    m_patternU [bin] [1] = 0.0;
    m_patternT [bin] [0] = 0.0;
    m_patternT [bin] [1] = 0.0;
    m_correlationU [bin] [0] = 0.0;
    m_correlationU [bin] [1] = 0.0;
    m_correlationT [bin] [0] = 0.0;
    m_correlationT [bin] [1] = 0.0;
  }

  int center = m_histogramSize / 2;
  int first = center - period * (gridlineCount - 1.0) / 2.0;
  for (int peak = 0; peak < gridlineCount; peak++) {

    int bin = first + peak * period;
    Q_ASSERT (0 <= bin);
    Q_ASSERT (bin < m_histogramSize);

    m_patternU[bin][0] = PEAK_VALUE;
  }

  spreadPeaks (m_patternU);

  normalizeArray (m_patternU);
}

void CallbackAngleAbstractBase::normalizeArray (fftw_complex *array)
{
  // Bins below histogramSize are normalized. Bins above histogramSize keep their current zero values

  int bin;
  double sum = 0.0;
  for (bin = 0; bin < m_histogramSize; bin++) {
    sum += array [bin] [0];
  }
  double mean = sum / m_histogramSize;
  for (bin = 0; bin < m_histogramSize; bin++) {
    array [bin] [0] -= mean;
  }
}

void CallbackAngleAbstractBase::outputComplexArray (const fftw_complex *array,
                                                    const QString &filename) const
{
  QFile fArray(filename);
  fArray.open (QIODevice::WriteOnly | QIODevice::Text);
  QTextStream strArray (&fArray);

  for (int bin = 0; bin < m_arraySize; bin++) {
    double real = array [bin] [0];
    double imag = array [bin] [1];
    double magnitude = sqrt (real * real + imag * imag);
    strArray << bin << "\t" << real << "\t" << imag << "\t" << magnitude << endl;
  }

  fArray.close ();
}

void CallbackAngleAbstractBase::outputHistogram (double histogram [],
                                                 const QString &filename) const
{
  QFile fHistogram (filename);
  fHistogram.open (QIODevice::WriteOnly | QIODevice::Text);
  QTextStream strHistogram (&fHistogram);

  for (int bin = 0; bin < m_histogramSize; bin++) {

    strHistogram << bin << "\t" << histogram [bin] << endl;
  }

  fHistogram.close ();
}

void CallbackAngleAbstractBase::spreadPeaks (fftw_complex *array)
{
  double halfWidth = 15.0;

  // Need two passes so result are symmetric:
  // 1) First pass leaves leaves straight line on left side of delta peak, and smooth curve on right side
  // 2) Second pass leaves smooth curves on both sides of each delta peak

  for (int pass = 0; pass < 2; pass++) {
    for (int bin = 0; bin < m_histogramSize; bin++) {

      // Triangle with peak at (bin, array (bin)) drops down to (bin-period/2,0) and (bin+period/2,0)
      for (int neighborOffset = 1; neighborOffset < halfWidth; neighborOffset++) {

        double s = (double) neighborOffset / halfWidth;
        double height = (1.0 - s) * array [bin] [0] + s * 0.0;
        if (height > 0) {
          if (0 <= bin - neighborOffset) {
            if (array [bin - neighborOffset] [0] < height) {
              array [bin - neighborOffset] [0] = height;
            }
          }
          if (bin + neighborOffset < m_histogramSize) {
            if (array [bin + neighborOffset] [0] < height) {
              array [bin + neighborOffset] [0] = height;
            }
          }
        }
      }
    }
  }
}
