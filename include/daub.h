
#include <math.h>

template <class T>
class Daubechies : public liftbase<T, double> {

protected:
  void predict( T& vec, int N, transDirection direction )
  {
    assert( false );
  } // predict

  virtual void update( T& vec, int N, transDirection direction )
  {
    assert( false );
  } // update

private:

  double h0, h1, h2, h3;

  double g0, g1, g2, g3;

  double Ih0, Ih1, Ih2, Ih3;
  double Ig0, Ig1, Ig2, Ig3;

public:

  void forwardStep( T& a, const int n )
  {
    if (n >= 4) {
      int i, j;
      const int half = n >> 1;

      double* tmp = new double[n];

      for (i = 0, j = 0; j < n-3; j += 2, i++) {
	tmp[i]      = a[j]*h0 + a[j+1]*h1 + a[j+2]*h2 + a[j+3]*h3;
	tmp[i+half] = a[j]*g0 + a[j+1]*g1 + a[j+2]*g2 + a[j+3]*g3;
      }

      tmp[i]      = a[n-2]*h0 + a[n-1]*h1 + a[0]*h2 + a[1]*h3;
      tmp[i+half] = a[n-2]*g0 + a[n-1]*g1 + a[0]*g2 + a[1]*g3;

      for (i = 0; i < n; i++) {
	a[i] = tmp[i];
      }
      delete [] tmp;
    }
  }

  void forwardStepRev( T& a, const int n )
  {
    if (n >= 4) {
      int i, j;
      const int half = n >> 1;

      double* tmp = new double[n];

      for (i = 0, j = 0; j < n-3; j += 2, i++) {
	tmp[i+half] = a[j]*h0 + a[j+1]*h1 + a[j+2]*h2 + a[j+3]*h3;
	tmp[i]      = a[j]*g0 + a[j+1]*g1 + a[j+2]*g2 + a[j+3]*g3;
      }

      tmp[i+half] = a[n-2]*h0 + a[n-1]*h1 + a[0]*h2 + a[1]*h3;
      tmp[i]      = a[n-2]*g0 + a[n-1]*g1 + a[0]*g2 + a[1]*g3;

      for (i = 0; i < n; i++) {
	a[i] = tmp[i];
      }
      delete [] tmp;
    }
  }

  /**
    Inverse Daubechies D4 transform
    */
  void inverseStep( T& a, const int n )
  {
    if (n >= 4) {
      int i, j;
      const int half = n >> 1;
      const int halfPls1 = half + 1;

      double* tmp = new double[n];

      //      last smooth val  last coef.  first smooth  first coef
      tmp[0] = a[half-1]*Ih0 + a[n-1]*Ih1 + a[0]*Ih2 + a[half]*Ih3;
      tmp[1] = a[half-1]*Ig0 + a[n-1]*Ig1 + a[0]*Ig2 + a[half]*Ig3;
      for (i = 0, j = 2; i < half-1; i++) {
	//     smooth val     coef. val       smooth val    coef. val
	tmp[j++] = a[i]*Ih0 + a[i+half]*Ih1 + a[i+1]*Ih2 + a[i+halfPls1]*Ih3;
	tmp[j++] = a[i]*Ig0 + a[i+half]*Ig1 + a[i+1]*Ig2 + a[i+halfPls1]*Ig3;
      }
      for (i = 0; i < n; i++) {
	a[i] = tmp[i];
      }
      delete [] tmp;
    }
  } // inverseStep

  Daubechies()
  {
    const double sqrt_3 = sqrt( 3 );
    const double denom = 4 * sqrt( 2 );

    h0 = (1 + sqrt_3)/denom;
    h1 = (3 + sqrt_3)/denom;
    h2 = (3 - sqrt_3)/denom;
    h3 = (1 - sqrt_3)/denom;

    g0 =  h3;
    g1 = -h2;
    g2 =  h1;
    g3 = -h0;

    Ih0 = h2;
    Ih1 = g2;  // h1
    Ih2 = h0;
    Ih3 = g0;  // h3

    Ig0 = h3;
    Ig1 = g3;  // -h0
    Ig2 = h1;
    Ig3 = g1;  // -h2
  }

  void forwardTrans( T& ts, int N )
  {
    int n;
    for (n = N; n >= 4; n >>= 1) {
      forwardStep( ts, n );
    }
  } // forwardTrans

  void inverseTrans( T& coef, int N )
  {
    int n;
    for (n = 4; n <= N; n <<= 1) {
      inverseStep( coef, n );
    }
  } // inverseTrans

}; // Daubechies
