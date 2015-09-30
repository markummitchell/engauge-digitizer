#ifndef CORRELATION_H
#define CORRELATION_H

#include "fftw3.h"

/// Fast cross correlation between two functions. We do not use complex.h along with fftw3.h since then the
/// complex numbers will be native, which would then require platform-dependent code
class Correlation
{
public:
  /// Single constructor. Slow memory allocations are done once and then reused repeatedly.
  Correlation(int N);
  ~Correlation();

  /// Return the shift in function1 that best aligns that function with function2. The functions
  /// are normalized internally. The correlations vector, as a function of shift, is returned for logging
  void correlateWithShift (int N,
                           const double function1 [],
                           const double function2 [],
                           int &binStartMax,
                           double &corrMax,
                           double correlations []) const;

  /// Return the correlation of the two functions, without any shift. The functions
  /// are normalized internally.
  void correlateWithoutShift (int N,
                              const double function1 [],
                              const double function2 [],
                              double &corrMax) const;

private:
  Correlation();

  int m_N;

  fftw_complex *m_signalA;
  fftw_complex *m_signalB;
  fftw_complex *m_outShifted;
  fftw_complex *m_outA;
  fftw_complex *m_outB;
  fftw_complex *m_out;

  fftw_plan m_planA;
  fftw_plan m_planB;
  fftw_plan m_planX;
};

#endif // CORRELATION_H
