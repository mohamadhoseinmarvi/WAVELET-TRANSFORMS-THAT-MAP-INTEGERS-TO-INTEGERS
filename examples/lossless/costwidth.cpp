

#include "costwidth.h"
#include "support.h"

int
costwidth::costCalc( packnode<int> *root )
{
  assert( root != 0 );

  size_t N = root->length();
  const int *a = root->getData();

  int width = support::vecWidth( a, N );

  return width;
}
