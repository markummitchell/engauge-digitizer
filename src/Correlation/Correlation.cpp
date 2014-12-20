#include <complex.h>
#include "Correlation.h"
#include "fftw3.h"
#include <QDebug>

Correlation::Correlation(int N) :
  m_N (N),
  m_signala_ext ((fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (2 * N - 1))),
  m_signalb_ext ((fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (2 * N - 1))),
  m_out_shifted ((fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (2 * N - 1))),
  m_outa ((fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (2 * N - 1))),
  m_outb ((fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (2 * N - 1))),
  m_out ((fftw_complex *) fftw_malloc(sizeof(fftw_complex) * (2 * N - 1)))
{
  m_planA = fftw_plan_dft_1d(2 * N - 1, m_signala_ext, m_outa, FFTW_FORWARD, FFTW_ESTIMATE);
  m_planB = fftw_plan_dft_1d(2 * N - 1, m_signalb_ext, m_outb, FFTW_FORWARD, FFTW_ESTIMATE);
  m_planX = fftw_plan_dft_1d(2 * N - 1, m_out, m_out_shifted, FFTW_BACKWARD, FFTW_ESTIMATE);
}

Correlation::~Correlation()
{
  fftw_destroy_plan(m_planA);
  fftw_destroy_plan(m_planB);
  fftw_destroy_plan(m_planX);

  fftw_free(m_signala_ext);
  fftw_free(m_signalb_ext);
  fftw_free(m_out_shifted);
  fftw_free(m_out);
  fftw_free(m_outa);
  fftw_free(m_outb);

  fftw_cleanup();
}

void Correlation::correlate (int N,
                             double function1 [],
                             double function2 [],
                             int &binStepMax,
                             double &corrMax) const
{
  int i;

  Q_ASSERT (N == m_N);

  // Normalize input functions so that:
  // 1) mean is zero
  // 2) unsigned area between the points and the horizontal axis is (arbitrarily) one
  double sumMean1 = 0, sumMean2 = 0, sumArea1 = 0, sumArea2 = 0;
  for (i = 0; i < N; i++) {
    sumMean1 += function1 [i];
    sumMean2 += function2 [i];
    sumArea1 += qAbs (function1 [i]);
    sumArea2 += qAbs (function2 [i]);
  }
  double additiveNormalization1 = sumMean1 / N;
  double additiveNormalization2 = sumMean2 / N;
  double multiplicativeNormalization1 = 1.0 / sumArea1;
  double multiplicativeNormalization2 = 1.0 / sumArea2;

  // Load length N functions into length 2N+1 arrays, padding with zeros
  for (i = 0; i < 2 * N - 1; i++) {
    if (i < N) {
      m_signala_ext [i] = (function1 [i] - additiveNormalization1) * multiplicativeNormalization1;
      m_signalb_ext [i] = (function2 [i] - additiveNormalization2) * multiplicativeNormalization2;
    } else {
      m_signala_ext [i] = 0.0;
      m_signalb_ext [i] = 0.0;
    }
  }

  fftw_execute(m_planA);
  fftw_execute(m_planB);

  // Correlation in frequency space
  fftw_complex scale = 1.0/(2.0 * N - 1.0);
  for (i = 0; i < 2 * N - 1; i++) {
    m_out[i] = m_outa[i] * conj(m_outb[i]) * scale;
  }

  fftw_execute(m_planX);

  // Search for highest correlation. We have to account for the shift in the index. Specifically,
  // 0 to N was mapped to the second half of the array that is 0 to 2 * N - 1
  corrMax = 0.0;
  for (int i0AtLeft = 0; i0AtLeft < N; i0AtLeft++) {
    int i0AtCenter = (i0AtLeft + N) % (2 * N - 1);
    fftw_complex shifted = m_out_shifted [i0AtCenter];
    if ((i0AtLeft == 0) || (creal (shifted) > corrMax)) {
      binStepMax = i0AtLeft;
      corrMax = creal (shifted);
    }
  }
}
