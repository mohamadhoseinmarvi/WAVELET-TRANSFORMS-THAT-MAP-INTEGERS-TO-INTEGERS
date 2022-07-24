
#include <stdio.h>

#include "invpacktree_int.h"
#include "packtree_int.h"
#include "support.h"
#include "delta.h"
#include "haar_int.h"
#include "ts_trans_int.h"
#include "line_int.h"
#include "costwidth.h"
#include "yahooTS.h"

int *copy( int *intVec, const size_t N )
{
  int *newVec = new int[ N ];

  for (size_t i = 0; i < N; i++)
  {
    newVec[i] = intVec[i];
  }

  return newVec;
}

bool compare( const int *v1, const int *v2, const size_t N )
{
  bool rslt = true;

  for (size_t i = 0; i < N; i++)
  {
    if (v1[i] != v2[i])
    {
      rslt = false;
      break;
    }
  }

  return rslt;
}

size_t calcPacketWidth( packdata_list<int> &bestBasisList )
{
  packdata_list<int>::handle h;
  size_t totalWidth = 0;

  for (h = bestBasisList.first(); h != 0; h = bestBasisList.next( h )) {
    packdata<int> *node = bestBasisList.get_item( h );
    const size_t len = node->length();
    const int *vec = node->getData();
    int nodeWidth = support::vecWidth( vec, len );
    totalWidth += nodeWidth;
  }

  return totalWidth;
}

size_t packet_calc( const int *intVec,
		    const int *copyVec,
		    const int N )
{

  line_int<packcontainer_int> line;


  packtree_int tree( intVec, N, &line );

  packnode<int> *treeRoot = tree.getRoot();

  // Assign a cost on the basis of bit width
  costwidth cost( treeRoot );

  // Calculate the "best basis" function from the tree
  tree.bestBasis();


  if (! tree.bestBasisOK()) {
    printf("Best basis calculation failed\n");
  }

  packdata_list<int> bestBasis = tree.getBestBasisList();

  size_t width = calcPacketWidth( bestBasis );

  invpacktree_int invtree( bestBasis, &line );

  const int *invRslt = invtree.getData();

  bool isEqual = compare( invRslt, copyVec, N );
  if (! isEqual)
    printf("Wavelet packet inverse is wrong\n");

  return width;
}

size_t delta_calc( int *intVec,
		   const int *copyVec,
		   const int N )
{
  delta_trans<int> delta;

  delta.forward( intVec, N );

  const size_t deltaWidth = support::vecWidth( intVec, N );

  delta.inverse( intVec, N);

  bool isEqual = compare( intVec, copyVec, N);
  if (! isEqual)
    printf("Delta compression inverse failed\n");

  return deltaWidth;
}

size_t wave_calc( int *intVec,
		  const int *copyVec,
		  const int N,
		  liftbase<int *, int> *w )
{
  w->forwardTrans( intVec, N );

  const size_t waveWidth = support::vecWidth( intVec, N );

  w->inverseTrans( intVec, N );

  bool isEqual = compare( intVec, copyVec, N);
  if (! isEqual)
    printf("Line wavelet inverse is wrong\n");

  return waveWidth;
}

int main()
{
  const char *files[] = { "aa",
			  "amat",  // Applied Materials
			  "ba",    // Boeing
			  "cof",   // Capital One
			  "ge",    // General Electric
			  "ibm",   // IBM Corp.
			  "intc",  // Intel
			  "mmm",   // 3M
			  "mrk",   // Merck
			  "wmt",   // Wal-Mart
			  0        // The null pointer
			};

  const size_t N = 512;
  double realVec[ N ];
  int intVec[ N ];

  const char *dataDirPath = "..\\data\\equities\\";
  yahooTS ts( dataDirPath );

  printf("Equity Uncompressed  delta  Haar  line  TS    wavelet packet (line)\n");


  for (size_t i = 0; files[i] != 0; i++) {

    size_t n = N;
    if (! ts.getTS( files[i], realVec, n, yahooTS::Close )) {
      break;
    }

    if (n != N) {
      printf("Error: %d out of %d data elements read\n", n, N );
      break;
    }

    support::decimalToInt( intVec, realVec, N );

    int *copyVec = copy( intVec, N );

    const size_t beforeWidth = support::vecWidth( intVec, N );

    const size_t deltaWidth = delta_calc( intVec, copyVec, N );

    haar_int haar;
    const size_t haarWidth = wave_calc( intVec, copyVec, N, &haar );

    line_int<int *> line;
    const size_t lineWidth = wave_calc( intVec, copyVec, N, &line );

    ts_trans_int ts_trans;
    const size_t tsTransWidth = wave_calc( intVec,
					   copyVec,
					   N,
					   &ts_trans);

    const size_t packetWidth = packet_calc( intVec, copyVec, N );

    printf("  %4s       %4d    %4d   %4d  %4d  %d      %4d\n",
	   files[i], beforeWidth, deltaWidth, haarWidth, lineWidth, tsTransWidth, packetWidth );

  }
  return 0;
}
