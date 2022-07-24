
#ifndef _PACKTREE_H_
#define _PACKTREE_H_
#include "packtree_base.h"
#include "packdata_list.h"
#include "packcontainer.h"
#include "liftbase.h"

class packtree : public packtree_base {
private:

  bool foundOriginalData;
  bool foundBestBasisVal;

private:
  packtree( const packtree &rhs ) {};
  packtree() {};

  double bestBasisWalk( packnode<double> *root );

  void buildBestBasisList( packnode<double> *root,
			   packdata_list<double> &list );

  void checkBestBasis( packnode<double> *root );

  void cleanTree(packnode<double> *root, bool removeMark );

public:

  packtree( const double *vec,
            const size_t n,
            liftbase<packcontainer, double> *w );
  ~packtree() {}

  void prCost();
  void prBestBasis();

  void bestBasis();

  bool bestBasisOK();

  packdata_list<double> getBestBasisList();

};

#endif
