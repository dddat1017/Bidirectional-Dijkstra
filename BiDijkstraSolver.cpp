/*
 * Author: Dat Do
 * Contact: datdo1017@gmail.com
 * Copyright 2020 Dat Do
*/

#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <limits>  // For numeric_limits
#include <chrono>  // For high_resolution_clock and duration

template <typename Vertex>
BiDijkstraSolver<Vertex>::BiDijkstraSolver(
                const Graph<Vertex>& input,
                Vertex start, Vertex end,
                const double& timeout) {
  auto start_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed;

  // Check if start/end vertices are the same. If so, easy solve.
  // Utilizes the fact that Vertices' type must support == operator
  // to check for equality.
  if (start == end) {
    outcome_ = 1;
    solution_.push_back(start);  // Or end; does not matter.
    solutionWeight_ = 0;
    numStatesExplored_ = 1;

    auto finish1 = std::chrono::high_resolution_clock::now();
    elapsed = finish1 - start_time;
    timeSpent = elapsed.count();  // Total time.
    return;
  }

  std::unordered_set<Vertex> visited;

  outcome_ = 0;
  solutionWeight_ = std::numeric_limits<double>::infinity();
  numStatesExplored_ = 0;

  forwardFringe.add(start, 0.0);
  forwardEdgeTo[start] = start;
  forwardDistTo[start] = 0.0;

  backwardFringe.add(end, 0.0);
  backwardEdgeTo[end] = end;
  backwardDistTo[end] = 0.0;

  Vertex mid;
  double prevDist;
  double dist;
  double totalTimeSoFar;

  while (!forwardFringe.isEmpty() && !backwardFringe.isEmpty()) {
    Vertex* a = forwardFringe.removeSmallest();
    numStatesExplored_++;
    prevDist = forwardDistTo[*a];
    for (auto& edge : input.outgoingNeighbors(*a)) {
      Vertex b = (*edge).to();
      dist = prevDist + (*edge).weight();
      if (forwardDistTo.find(b) == forwardDistTo.end()) {
        forwardFringe.add(b, dist);
        forwardEdgeTo[b] = *a;
        forwardDistTo[b] = dist;
      } else {
        if (dist < forwardDistTo[b]) {
          forwardFringe.changePriority(b, dist);
          forwardEdgeTo[b] = *a;
          forwardDistTo[b] = dist;
        }
      }
    }

    if (visited.insert(*a).second == false) {
      mid = *a;
      outcome_ = 1;
      delete a;
      break;
    }

    Vertex* v = backwardFringe.removeSmallest();
    numStatesExplored_++;
    prevDist = backwardDistTo[*v];
    for (auto& edge : input.incomingNeighbors(*v)) {
      Vertex w = (*edge).to();
      dist = prevDist + (*edge).weight();
      if (backwardDistTo.find(w) == backwardDistTo.end()) {
        backwardFringe.add(w, dist);
        backwardEdgeTo[w] = *v;
        backwardDistTo[w] = dist;
      } else {
        if (dist < backwardDistTo[w]) {
          backwardFringe.changePriority(w, dist);
          backwardEdgeTo[w] = *v;
          backwardDistTo[w] = dist;
        }
      }
    }

    if (visited.insert(*v).second == false) {
      mid = *v;
      outcome_ = 1;
      delete a;
      delete v;
      break;
    }

    delete a;
    delete v;

    auto finish2 = std::chrono::high_resolution_clock::now();
    elapsed = finish2 - start_time;
    totalTimeSoFar = elapsed.count();
    if (totalTimeSoFar > timeout) {
      outcome_ = -1;
      timeSpent = totalTimeSoFar;
      return;
    }
  }

  if (outcome_ == 1) {
    solution_.push_back(mid);
    Vertex trace = forwardEdgeTo[mid];
    while (trace != start) {
      solution_.push_back(trace);
      trace = forwardEdgeTo[trace];
    }
    solution_.push_back(trace);
    std::reverse(solution_.begin(), solution_.end());

    trace = backwardEdgeTo[mid];
    while (trace != end) {
      solution_.push_back(trace);
      trace = backwardEdgeTo[trace];
    }
    solution_.push_back(trace);
    solutionWeight_ = forwardDistTo[mid] + backwardDistTo[mid];
  }

  auto finish3 = std::chrono::high_resolution_clock::now();
  elapsed = finish3 - start_time;
  timeSpent = elapsed.count();
}
