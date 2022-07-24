
#ifndef _PACKTREE_INT_H_
#define _PACKTREE_INT_H_


#include "packtree_base_int.h"
#include "packdata_list.h"
#include "packcontainer.h"
#include "liftbase.h"

class packtree_int : public packtree_base_int {
private:

  bool foundOriginalData;
  bool foundBestBasisVal;

private:
  packtree_int( const packtree_int &rhs ) {};
  packtree_int() {};

  int bestBasisWalk( packnode<int> *root );

  void buildBestBasisList( packnode<int> *root,
			   packdata_list<int> &list );

  void checkBestBasis( packnode<int> *root );

  void cleanTree(packnode<int> *root, bool removeMark );

public:

  packtree_int( const int *vec,
		const size_t n,
		liftbase<packcontainer_int, int> *w );
  ~packtree_int() {}

  void prCost();
  void prBestBasis();

  void bestBasis();

  bool bestBasisOK();

  packdata_list<int> getBestBasisList();

};

#endif
