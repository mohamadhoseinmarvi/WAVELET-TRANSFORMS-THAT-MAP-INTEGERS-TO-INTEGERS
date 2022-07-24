
#ifndef _YAHOOTS_H_
#define _YAHOOTS_H_
class yahooTS
{
private:
  const char *path_;

public:

  typedef enum { badEnum,
		 Open,
		 High,
		 Low,
		 Close,
		 Volume,
		 lastEnum } dataKind;

  yahooTS()
  {
    path_ = 0;
  };
  yahooTS( const char *p ) : path_(p) {}

  const double *getTS( const char *fileName,
		       double *a,
		       size_t &N,
		       dataKind kind ) const;

  void path( const char *p ) { path_ = p; }
  const char *path() { return path_; }

private:
  const char *getStr_( char *&line,
		       char *buf,
		       size_t bufSize ) const;

  void parseVals_( char *line,
		   double *vals,
		   const size_t n ) const;

  const double getValue_( char *line,
			  const yahooTS::dataKind kind ) const;

};


#endif
