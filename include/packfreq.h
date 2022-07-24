
#ifndef _PACKFREQ_H_
#define _PACKFREQ_H_


#include "packnode.h"
#include "packcontainer.h"
#include "packtree_base.h"
#include "liftbase.h"
#include "grow_array.h"

class packfreq : public packtree_base {
private:
  GrowableArray<packnode<double> *> mat;

  void findLevel( packnode<double>* top,
		  size_t cur_level,
		  const size_t level );

protected:
  packfreq( const packfreq &rhs ) {};

  packfreq() {};

public:
  packfreq( const double *vec,
            const size_t n,
            liftbase<packcontainer, double> *w );

  ~packfreq() {}

  void getLevel( const size_t level );

  void plotMat(const size_t N);

  void prMat();
}; // packfreq

#endif
