#ifndef CALLBACK_ANGLE_ABSTRACT_BASE_H
#define CALLBACK_ANGLE_ABSTRACT_BASE_H

#include <complex>
#include <fftw3.h>
#include <QList>
#include <QPoint>
#include <QString>

typedef QList<QPoint> ForegroundPoints;

class CallbackAngleAbstractBase
{
 public:
  CallbackAngleAbstractBase (int histogramSize,
                             double angleRadians,
                             const QString &xOrY);
  virtual ~CallbackAngleAbstractBase ();

 protected:

  double correlation (double period,
                      int gridlineCount);
  int histogramSize () const;
  void incrementHistogramBin (int bin);

  /// Call this from the subclass constructor have m_histogramU has been populated
  void initialize();

private:

  // Multiply h * conjugate(p) * scale into the correlation array, where all arguments are complex
  void hConjPScale (const fftw_complex &h,
                    const fftw_complex &p,
                    const fftw_complex &scale,
                    fftw_complex &correlation);
  void loadHistogramArray ();
  void loadNonHistogramArrays (int gridlineCount,
                               double period);
  void normalizeArray (fftw_complex *array);
  void outputComplexArray (const fftw_complex *array,
                           const QString &filename) const;
  void outputHistogram (double histogram [],
                        const QString &filename) const;
  void spreadPeaks (fftw_complex *array);

  const int m_histogramSize;
  const int m_arraySize;
  const double m_angleRadians;
  const QString m_xOrY;

  int *m_histogram;

  fftw_complex *m_histogramU;
  fftw_complex *m_histogramT;
  fftw_complex *m_patternU;
  fftw_complex *m_patternT;
  fftw_complex *m_correlationU;
  fftw_complex *m_correlationT;

  fftw_plan m_planHisto;
  fftw_plan m_planPattern;
  fftw_plan m_planCorrelation;
};

#endif // CALLBACK_ANGLE_ABSTRACT_BASE_H
