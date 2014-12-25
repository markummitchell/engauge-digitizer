#include <complex.h>
#include "Correlation.h"
#include "fftw3.h"
#include "Logger.h"
#include <QDebug>
#include <qmath.h>

Correlation::Correlation(int N) :
  m_N (N),
  m_signalA ((fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (2 * N - 1))),
  m_signalB ((fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (2 * N - 1))),
  m_outShifted ((fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (2 * N - 1))),
  m_outA ((fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (2 * N - 1))),
  m_outB ((fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (2 * N - 1))),
  m_out ((fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (2 * N - 1)))
{
  m_planA = fftw_plan_dft_1d(2 * N - 1, m_signalA, m_outA, FFTW_FORWARD, FFTW_ESTIMATE);
  m_planB = fftw_plan_dft_1d(2 * N - 1, m_signalB, m_outB, FFTW_FORWARD, FFTW_ESTIMATE);
  m_planX = fftw_plan_dft_1d(2 * N - 1, m_out, m_outShifted, FFTW_BACKWARD, FFTW_ESTIMATE);
}

Correlation::~Correlation()
{
  fftw_destroy_plan(m_planA);
  fftw_destroy_plan(m_planB);
  fftw_destroy_plan(m_planX);

  fftw_free(m_signalA);
  fftw_free(m_signalB);
  fftw_free(m_outShifted);
  fftw_free(m_out);
  fftw_free(m_outA);
  fftw_free(m_outB);

  fftw_cleanup();
}

void Correlation::correlateWithShift (int N,
                                      const double function1 [],
                                      const double function2 [],
                                      int &binStartMax,
                                      double &corrMax) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "Correlation::correlateWithShift";

  int i;

  Q_ASSERT (N == m_N);

  // Normalize input functions so that:
  // 1) mean is zero. This is used to compute an additive normalization constant
  // 2) max value is 1. This is used to compute a multiplicative normalization constant
  double sumMean1 = 0, sumMean2 = 0, max1 = 0, max2 = 0;
  for (i = 0; i < N; i++) {

    sumMean1 += function1 [i];
    sumMean2 += function2 [i];
    max1 = qMax (max1, function1 [i]);
    max2 = qMax (max2, function2 [i]);

  }

  double additiveNormalization1 = sumMean1 / N;
  double additiveNormalization2 = sumMean2 / N;
  double multiplicativeNormalization1 = 1.0 / max1;
  double multiplicativeNormalization2 = 1.0 / max2;

  // Load length N functions into length 2N+1 arrays, padding with zeros before for the first
  // array, and with zeros after for the second array
  for (i = 0; i < N - 1; i++) {

    m_signalA [i] = 0.0;
    m_signalB [i + N] = 0.0;

  }
  for (i = 0; i < N; i++) {

    m_signalA [i + N - 1] = (function1 [i] - additiveNormalization1) * multiplicativeNormalization1;
    m_signalB [i] = (function2 [i] - additiveNormalization2) * multiplicativeNormalization2;

  }

  fftw_execute(m_planA);
  fftw_execute(m_planB);

  // Correlation in frequency space
  fftw_complex scale = 1.0/(2.0 * N - 1.0);
  for (i = 0; i < 2 * N - 1; i++) {
    m_out[i] = m_outA[i] * conj(m_outB[i]) * scale;
  }

  fftw_execute(m_planX);

  // Search for highest correlation. We have to account for the shift in the index. Specifically,
  // 0 to N was mapped to the second half of the array that is 0 to 2 * N - 1
  corrMax = 0.0;
  for (int i0AtLeft = 0; i0AtLeft < N; i0AtLeft++) {

    int i0AtCenter = (i0AtLeft + N) % (2 * N - 1);
    fftw_complex shifted = m_outShifted [i0AtCenter];
    double corr = qSqrt (creal (shifted) * creal (shifted) + cimag (shifted) * cimag (shifted));

    if ((i0AtLeft == 0) || (corr > corrMax)) {
      binStartMax = i0AtLeft;
      corrMax = corr;
    }
  }
}

void Correlation::correlateWithoutShift (int N,
                                         const double function1 [],
                                         const double function2 [],
                                         double &corrMax) const
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "Correlation::correlateWithoutShift";

  corrMax = 0.0;

  for (int i = 0; i < N; i++) {
    corrMax += function1 [i] * function2 [i];
  }
}
