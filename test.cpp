/*
 * Author: Dat Do
 * Contact: datdo1017@gmail.com
 * Copyright 2020 Dat Do
*/

#include <chrono>  // For high_resolution_clock and duration
#include <iostream>
#include <assert.h>
#include "WeightedEdge.h"

int main(int argc, char* argv[]) {
  /*
  ////////////////// Testing WeightedEdge. //////////////////
  */

  // Record start time.
  auto start = std::chrono::high_resolution_clock::now();

  WeightedEdge<int> we1 = WeightedEdge<int>(10, 17, -12.3);
  assert(10 == we1.from());
  assert(17 == we1.to());
  assert(-12.3 == we1.weight());

  WeightedEdge<int> we2 = we1.flip();
  assert(17 == we2.from());
  assert(10 == we2.to());
  assert(-12.3 == we2.weight());

  // Record end time.
  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  double total_time = elapsed.count();
  std::cout << "Elapsed time: " << total_time << " seconds." << std::endl;
}
