/*
 * Author: Dat Do
 * Contact: datdo1017@gmail.com
 * Copyright 2020 Dat Do
*/

#include <assert.h>
#include <vector>
#include <iostream>
#include "WeightedDirectedGraph.h"
#include "BiDijkstraSolver.h"

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

  /*
  ////////////////// Testing BidijkstraSolver. //////////////////
  */
  WeightedDirectedGraph wdg(7);
  wdg.addEdge(0, 1, 2);
  wdg.addEdge(0, 2, 1);

  wdg.addEdge(1, 2, 5);
  wdg.addEdge(1, 3, 11);
  wdg.addEdge(1, 4, 3);

  wdg.addEdge(2, 5, 15);

  wdg.addEdge(3, 4, 2);

  wdg.addEdge(4, 2, 1);
  wdg.addEdge(4, 5, 4);
  wdg.addEdge(4, 6, 5);

  wdg.addEdge(6, 3, 1);
  wdg.addEdge(6, 5, 1);

  BiDijkstraSolver<int> solver(wdg, 0, 6, 10);

  std::cout << "Outcome: " << solver.outcome() << std::endl;
  const std::vector<int>& sol = solver.solution();
  if (sol.size() > 0) {
    for (uint i = 0; i < sol.size() - 1; i++) {
      std::cout << sol[i] << "=>";
    }
    std::cout << sol[sol.size() - 1] << std::endl;
  }
  std::cout << "Total weight: " << solver.solutionWeight() << std::endl;
  std::cout << "States explored: " << solver.numStatesExplored() << std::endl;
  std::cout << "Total time: " << solver.explorationTime();
  std::cout << "(seconds)" << std::endl;
}
