
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "yahooTS.h"

const char *yahooTS::getStr_( char *&line,
			      char *buf,
			      size_t bufSize ) const
{
  const char *rtnPtr = 0;
  if (line != 0) {
    for (size_t charCnt = 0; charCnt < bufSize-1 && *line != '\0'; charCnt++) {
      if (*line == ',') {
	line++;
	break;
      }
      else {
	buf[charCnt] = *line++;
      }
    }

    buf[charCnt] = '\0';
    if (charCnt > 0)
    {
      rtnPtr = buf;
    }
  }
  return rtnPtr;
}
void yahooTS::parseVals_( char *line,
			  double *vals,
			  const size_t n ) const
{
  char buf[128];
  const char *ptr;
  ptr = getStr_( line, buf, sizeof( buf ) );
  if (ptr == 0) {
    fprintf(stderr, "parseVals: date expected\n" );
    return;
  }
  size_t cnt = 0;
  for (dataKind kind = Open;
       kind <= Volume && cnt < n;
       kind = (dataKind)((size_t)kind + 1)) {

    ptr = getStr_( line, buf, sizeof( buf ) );
    if (ptr == 0) {
      fprintf(stderr, "parseVals: value expected\n");
      return;
    }

    double v;

    sscanf( buf, "%lf", &v );
    vals[cnt] = v;
    cnt++;
  }

}
const double yahooTS::getValue_( char *line,
				 const yahooTS::dataKind kind ) const
{
  double retval = 0;

  if (kind > badEnum && kind < lastEnum) {
    const size_t NUM_VALS = 5;
    double vals[ NUM_VALS ];

    parseVals_( line, vals, NUM_VALS );

    size_t ix = (size_t)kind - 1;
    if (ix < NUM_VALS) {
      retval = vals[ix];
    }
  }

  return retval;
}
const double *yahooTS::getTS( const char *fileName,
			      double *a,
			      size_t &N,
			      const yahooTS::dataKind kind ) const
{
  const double *rtnPtr = 0;
  char fullPath[512];
  size_t freePath = sizeof( fullPath );
  FILE *fptr;

  if (path_ != 0) {
    strncpy( fullPath, path_, freePath-1 );
    freePath = freePath - strlen( fullPath );
  }
  strncat( fullPath, fileName, freePath-1 );
  fptr = fopen( fullPath, "r" );
  if (fptr != 0) {
    char line[512];
    size_t lineSize = sizeof( line );
    int ix = N-1;

    if (fgets( line, lineSize, fptr ) != 0) {
      rtnPtr = a;
      while (fgets( line, lineSize, fptr ) != 0) {
	if (ix >= 0) {
	  a[ix] = getValue_( line, kind );
	  ix--;
	}
	else {
	  break;
	}
      }
    }
    else {
      fprintf(stderr, "getTS: title line expected\n");
    }
    ix++;
    N = N - ix;
  }
  else {
    const char *error = strerror( errno );
    fprintf(stderr, "getTS: Error opening %s: %s\n", fullPath, error );
  }

  return rtnPtr;
} 
