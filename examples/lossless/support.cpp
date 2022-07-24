
#include "support.h"
int support::roundVal_( const double val )
{
  int intPart =  static_cast<int>(val);
  double fracPart = val - intPart;
  int threeDigits = fracPart * 1000.0;
  int fourDigits = fracPart * 10000.0;
  int forthDigit = fourDigits % 10;
  int thirdDigit = threeDigits % 10;

  double roundVal = 0.001;
  if (forthDigit < 5) {
    roundVal = 0.0;
  }
  else if (forthDigit == 5) {
    if ((thirdDigit & 0x1) == 0) {
      roundVal = 0.0;
    }
  }
  double newVal = val + roundVal;
  double intRslt = newVal * 1000.0;
  return intRslt;
}

void support::roundToInt( int *intVec,
			  const double *realVec,
			  const size_t len )
{
  if (intVec != 0 && realVec != 0) {
    for (size_t i = 0; i < len; i++) {
      intVec[i] = roundVal_( realVec[i] );
    }
  }
}

void support::decimalToInt( int *intVec,
			    const double *realVec,
			    const size_t len )
{
  if (intVec != 0 && realVec != 0) {
    for (size_t i = 0; i < len; i++) {
      intVec[i] = (int)(realVec[i] * 100.0);
    }
  }
}




size_t support::nearestPower2Width_( size_t val )
{
  size_t width = 0;
  if (val > 0) {
    width = 1;
    size_t power = 1;
    while (power < val && width < 32) {
      power = power << 1;
      width++;
    }
  }

  return width;
}
size_t support::valWidth( const int val )
{
  size_t wholeNum = (val < 0) ? -val : val;
  size_t width = 1 + nearestPower2Width_( wholeNum );

  return width;
} // valWidth
size_t support::UnsignedValWidth( const size_t val )
{
  size_t width = nearestPower2Width_( val );

  return width;
} // valWidth
size_t support::vecWidth( const int *vec, const size_t N )
{
  size_t totalWidth = 0;
  if (vec != 0) {
    for (size_t i = 0; i < N; i++) {
      totalWidth += valWidth( vec[i] );
    }
  }
  return totalWidth;
} 
