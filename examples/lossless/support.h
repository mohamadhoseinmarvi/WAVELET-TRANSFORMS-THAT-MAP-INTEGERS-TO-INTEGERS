
#ifndef _SUPPORT_H_
#define _SUPPORT_H_
class support
{
private:
  static size_t nearestPower2Width_( size_t val );
  static int roundVal_( const double val );

public:
  support();
  ~support();
  support( const support &rhs );

  static size_t valWidth( const int val );

  size_t UnsignedValWidth( const size_t val );

  static size_t vecWidth( const int *vec,
				const size_t N );
  static void roundToInt( int *intVec,
			  const double *realVec,
			  const size_t len );

  static void decimalToInt( int *intVec,
			    const double *realVec,
			    const size_t len );
}; // support

#endif
