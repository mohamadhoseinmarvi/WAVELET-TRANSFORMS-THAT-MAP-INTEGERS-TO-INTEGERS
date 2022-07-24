

#ifndef _PACKTREE_BASE_INT_H_
#define _PACKTREE_BASE_INT_H_

#include "packnode.h"
#include "liftbase.h"
#include "packcontainer_int.h"

class packtree_base_int {
protected:

  packnode<int> *root;

  liftbase<packcontainer_int, int> *waveObj;

  typedef enum { BadPrintKind,
                 printData,
                 printCost,
                 printBestBasis } printKind;

  void breadthFirstPrint(printKind kind);

  void newLevel( packnode<int>* top, bool freqCalc, bool reverse );

public:
  void pr();
  packnode<int> *getRoot() { return root; }
};

#endif
