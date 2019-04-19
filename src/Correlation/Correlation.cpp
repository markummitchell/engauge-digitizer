/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Correlation.h"
#include "EngaugeAssert.h"
#include "fftw3.h"
#include "Logger.h"
#include <QDebug>
#include <qmath.h>

Correlation::Correlation(int N) :
  m_N (N),
  m_signalA (static_cast<fftw_complex *> (fftw_malloc(sizeof(fftw_complex) * unsigned (2 * N - 1)))),
  m_signalB (static_cast<fftw_complex *> (fftw_malloc(sizeof(fftw_complex) * unsigned (2 * N - 1)))),
  m_outShifted (static_cast<fftw_complex *> (fftw_malloc(sizeof(fftw_complex) * unsigned (2 * N - 1)))),
  m_outA (static_cast<fftw_complex *> (fftw_malloc(sizeof(fftw_complex) * unsigned (2 * N - 1)))),
  m_outB (static_cast<fftw_complex *> (fftw_malloc(sizeof(fftw_complex) * unsigned (2 * N - 1)))),
  m_out (static_cast<fftw_complex *> (fftw_malloc(sizeof(fftw_complex) * unsigned (2 * N - 1))))
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
                                      double &corrMax,
                                      double correlations []) const
{
  // LOG4CPP_DEBUG_S ((*mainCat)) << "Correlation::correlateWithShift";

  int i;

  ENGAUGE_ASSERT (N == m_N);
  ENGAUGE_ASSERT (N > 0); // Prevent divide by zero errors for additiveNormalization* and scale

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

  // Handle all-zero data
  if (max1 == 0.0) {
    max1 = 1.0;
  }
  if (max2 == 0.0) {
    max2 = 1.0;
  }
  
  double additiveNormalization1 = sumMean1 / N;
  double additiveNormalization2 = sumMean2 / N;
  double multiplicativeNormalization1 = 1.0 / max1;
  double multiplicativeNormalization2 = 1.0 / max2;

  // Load length N functions into length 2N+1 arrays, padding with zeros before for the first
  // array, and with zeros after for the second array
  for (i = 0; i < N - 1; i++) {

    m_signalA [i] [0] = 0.0;
    m_signalA [i] [1] = 0.0;
    m_signalB [i + N] [0] = 0.0;
    m_signalB [i + N] [1] = 0.0;

  }
  for (i = 0; i < N; i++) {

    m_signalA [i + N - 1] [0] = (function1 [i] - additiveNormalization1) * multiplicativeNormalization1;
    m_signalA [i + N - 1] [1] = 0.0;
    m_signalB [i] [0] = (function2 [i] - additiveNormalization2) * multiplicativeNormalization2;
    m_signalB [i] [1] = 0.0;

  }

  fftw_execute(m_planA);
  fftw_execute(m_planB);

  // Correlation in frequency space
  fftw_complex scale = {1.0/(2.0 * N - 1.0), 0.0};
  for (i = 0; i < 2 * N - 1; i++) {
    // Multiple m_outA [i] * conj (m_outB) * scale
    fftw_complex term1 = {m_outA [i] [0], m_outA [i] [1]};
    fftw_complex term2 = {m_outB [i] [0], m_outB [i] [1] * -1.0};
    fftw_complex term3 = {scale [0], scale [1]};
    fftw_complex terms12 = {term1 [0] * term2 [0] - term1 [1] * term2 [1],
                            term1 [0] * term2 [1] + term1 [1] * term2 [0]};
    m_out [i] [0] = terms12 [0] * term3 [0] - terms12 [1] * term3 [1];
    m_out [i] [1] = terms12 [0] * term3 [1] + terms12 [1] * term3 [0];
  }

  fftw_execute(m_planX);

  // Search for highest correlation. We have to account for the shift in the index. Specifically,
  // 0 to N was mapped to the second half of the array that is 0 to 2 * N - 1
  corrMax = 0.0;
  for (int i0AtLeft = 0; i0AtLeft < N; i0AtLeft++) {

    int i0AtCenter = (i0AtLeft + N) % (2 * N - 1);
    fftw_complex shifted = {m_outShifted [i0AtCenter] [0], m_outShifted [i0AtCenter] [1]};
    double corr = qSqrt (shifted [0] * shifted [0] + shifted [1] * shifted [1]);

    if ((i0AtLeft == 0) || (corr > corrMax)) {
      binStartMax = i0AtLeft;
      corrMax = corr;
    }

    // Save for, if enabled, external logging
    correlations [i0AtLeft] = corr;
  }
}

void Correlation::correlateWithoutShift (int N,
                                         const double function1 [],
                                         const double function2 [],
                                         double &corrMax) const
{
//  LOG4CPP_DEBUG_S ((*mainCat)) << "Correlation::correlateWithoutShift";

  corrMax = 0.0;

  for (int i = 0; i < N; i++) {
    corrMax += function1 [i] * function2 [i];
  }
}
