#ifndef _PACKTREE_BASE_H_
#define _PACKTREE_BASE_H_


#include "packnode.h"
#include "liftbase.h"

class packtree_base {
protected:
  packnode<double> *root;
  liftbase<packcontainer, double> *waveObj;

  typedef enum { BadPrintKind,
                 printData,
                 printCost,
                 printBestBasis } printKind;

  void breadthFirstPrint(printKind kind);

  void newLevel( packnode<double>* top, bool freqCalc, bool reverse );

public:
  void pr();
  packnode<double> *getRoot() { return root; }
};

#endif
