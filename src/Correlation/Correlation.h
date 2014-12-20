#ifndef CORRELATION_H
#define CORRELATION_H

#include <fftw3.h>

/// Fast cross correlation between two functions
class Correlation
{
public:
  /// Single constructor. Slow memory allocations are done once and then reused repeatedly.
  Correlation(int N);
  ~Correlation();

  /// Return the shift in function1 that best aligns that function with function2. The functions
  /// are normalized internally.
  void correlate (int N,
                  double function1 [],
                  double function2 [],
                  int &binStepMax,
                  double &corrMax) const;

private:
  Correlation();

  int m_N;

  fftw_complex *m_signala_ext;
  fftw_complex *m_signalb_ext;
  fftw_complex *m_out_shifted;
  fftw_complex *m_outa;
  fftw_complex *m_outb;
  fftw_complex *m_out;

  fftw_plan m_planA;
  fftw_plan m_planB;
  fftw_plan m_planX;
};

#endif // CORRELATION_H
