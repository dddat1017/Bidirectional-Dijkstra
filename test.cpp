/*
 * Author: Dat Do
 * Contact: datdo1017@gmail.com
 * Copyright 2020 Dat Do
*/

#include <assert.h>
#include "WeightedEdge.h"

int main(int argc, char* argv[]) {
  /*
  ////////////////// Testing WeightedEdge. //////////////////
  */
  WeightedEdge<int> we1 = WeightedEdge<int>(10, 17, -12.3);
  assert(10 == we1.from());
  assert(17 == we1.to());
  assert(-12.3 == we1.weight());

  WeightedEdge<int> we2 = we1.flip();
  assert(17 == we2.from());
  assert(10 == we2.to());
  assert(-12.3 == we2.weight());
}
