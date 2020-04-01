/*
 * Author: Dat Do
 * Contact: datdo1017@gmail.com
 * Copyright 2020 Dat Do
*/

#ifndef BIDIJKSTRASOLVER_H_
#define BIDIJKSTRASOLVER_H_

#include <map>
#include <vector>
#include "Graph.h"

/*
 * Class for the Bidirectional Dijkstra's Algorithm solver.
 * This class only provides functions for getting results of a
 * shortest path problem, since the solving is performed in the
 * constructor of the class.
*/
template <typename Vertex> class BiDijkstraSolver {
 public:
  /*
   * Ctor.
   * Immediately solves and stores the result of running the Bidirectional
   * Dijkstra's Algorithm, computing everything necessary for all other methods
   * to return their results in constant time. The timeout is given in seconds.
  */
  BiDijkstraSolver(Graph<Vertex> input, Vertex start, Vertex end, double timeout);

  /*
   * Dtor.
  */
  ~BiDijkstraSolver() { }

  /*
   * Returns 1 for 'solved', 0 for 'unsolvable', -1 for 'timed-out'.
  */
  int outcome() { return outcome; }

  /*
   * A vector of vertices corresponding to the solution, from start to end.
   * Returns an uninitialized vector if problem was unsolvable or solving timed out.
  */
  const std::vector<Vertex>& solution() { return solution; }

  /*
   * The total weight of the solution, taking into account edge weights.
   * Returns std::numeric_limits<double>::infinity() if problem was
   * unsolvable or solving timed out.
  */
  double solutionWeight() { return solutionWeight; }

  /*
   * The total number of states explored while solving.
  */
  int numStatesExplored() { return numStatesExplored; }

  /*
   * The total time spent in seconds by the constructor to run the Bidirectional
   * Dijkstra's Algorithm.
  */
  double explorationTime() { return timeSpent; }

 private:
  ExtrinsicMinPQ<Vertex> fringe;
  std::map<Vertex, Vertex> edgeTo;
  std::map<Vertex, double> distTo;

  int outcome;
  std::vector<Vertex> solution;
  double solutionWeight;
  int numStatesExplored;
  double timeSpent;
};

#include "BiDijkstraSolver.cpp"

#endif  // BIDIJKSTRASOLVER_H_
