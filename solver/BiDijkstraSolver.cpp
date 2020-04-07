/*
 * Author: Dat Do
 * Contact: datdo1017@gmail.com
 * Copyright 2020 Dat Do
*/

#include <algorithm>
#include <unordered_set>
#include <limits>  // For numeric_limits
#include <chrono>  // For high_resolution_clock and duration
#include "BiDijkstraSolver.h"

template <typename Vertex>
BiDijkstraSolver<Vertex>::BiDijkstraSolver(
                const Graph<Vertex>& input,
                Vertex start, Vertex end,
                const double& timeout) {
  auto start_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed;

  // Check if start/end vertices are the same. If so, easy solve.
  // Utilizes the fact that graph's vertices' type must support
  // == operator to check for equality.
  if (start == end) {
    outcome_ = 1;
    solution_.push_back(start);
    solutionWeight_ = 0;
    numStatesExplored_ = 1;

    auto finish1 = std::chrono::high_resolution_clock::now();
    elapsed = finish1 - start_time;
    timeSpent = elapsed.count();
    return;
  }

  std::unordered_set<Vertex> visited;

  // Initially, assume that problem is 'unsolvable'.
  outcome_ = 0;
  solutionWeight_ = std::numeric_limits<double>::infinity();
  numStatesExplored_ = 0;

  // Add start vertex to the forward-fringe/edgeTo/DistTo data structures.
  forwardFringe.add(start, 0.0);
  forwardEdgeTo[start] = start;
  forwardDistTo[start] = 0.0;

  // Add end vertex to the backward-fringe/edgeTo/DistTo data structures.
  backwardFringe.add(end, 0.0);
  backwardEdgeTo[end] = end;
  backwardDistTo[end] = 0.0;

  Vertex mid;  // Vertex where both path meets.
  double prevDist;  // Distance to the vertex being removed from the fringe.
  double dist;  // Distance to the vertex being relaxed.
  double totalTimeSoFar;

  // Both fringe must be non-empty while examining/relaxing each vertex.
  while (!forwardFringe.isEmpty() && !backwardFringe.isEmpty()) {
    /* -------------------- Forward path. -------------------- */
    // Once removed from fringe. Shortest path to this vertex is established.
    Vertex* a = forwardFringe.removeSmallest();
    numStatesExplored_++;

    // Check if this vertex has already been visited in the other direction.
    if (visited.insert(*a).second == false) {
      mid = *a;  // Initialize 'mid'.
      outcome_ = 1;  // Update 'outcome_' to 1 for 'solved'.
      delete a;
      break;
    }

    prevDist = forwardDistTo[*a];
    // Relax the removed vertex's neighbors.
    for (auto& edge : input.outgoingNeighbors(*a)) {
      Vertex b = (*edge).to();
      dist = prevDist + (*edge).weight();
      if (forwardDistTo.find(b) == forwardDistTo.end()) {
        // First time seeing this vertex; simply add to data structures.
        forwardFringe.add(b, dist);
        forwardEdgeTo[b] = *a;
        forwardDistTo[b] = dist;
      } else {
        /* 
         * Seen this vertex before. Only update its distance/edgeTo
         * if new 'dist' is smaller than existing distance.
         * 
         * Possibly, this vertex could be one that has already
         * been removed from the fringe. But since the shortest path
         * to it has already been established (invariant of Dijkstra's
         * once a vertex is removed), there would be no updates.
        */
        if (dist < forwardDistTo[b]) {
          forwardFringe.changePriority(b, dist);
          forwardEdgeTo[b] = *a;
          forwardDistTo[b] = dist;
        }
      }
    }

    /* -------------------- Backward path. -------------------- */
    // Once removed from fringe. Shortest path to this vertex is established.
    Vertex* v = backwardFringe.removeSmallest();
    numStatesExplored_++;

    // Check if this vertex has already been visited in the other direction.
    if (visited.insert(*v).second == false) {
      mid = *v;  // Initialize 'mid'.
      outcome_ = 1;  // Update 'outcome_' to 1 for 'solved'.
      delete a;
      delete v;
      break;
    }

    prevDist = backwardDistTo[*v];
    // Relax the removed vertex's neighbors.
    for (auto& edge : input.incomingNeighbors(*v)) {
      Vertex w = (*edge).to();
      dist = prevDist + (*edge).weight();
      if (backwardDistTo.find(w) == backwardDistTo.end()) {
        // First time seeing this vertex; simply add to data structures.
        backwardFringe.add(w, dist);
        backwardEdgeTo[w] = *v;
        backwardDistTo[w] = dist;
      } else {
        /* 
         * Seen this vertex before. Only update its distance/edgeTo
         * if new 'dist' is smaller than existing distance.
         * 
         * Possibly, this vertex could be one that has already
         * been removed from the fringe. But since the shortest path
         * to it has already been established (invariant of Dijkstra's
         * once a vertex is removed), there would be no updates.
        */
        if (dist < backwardDistTo[w]) {
          backwardFringe.changePriority(w, dist);
          backwardEdgeTo[w] = *v;
          backwardDistTo[w] = dist;
        }
      }
    }

    // Clean up.
    delete a;
    delete v;

    // Extract total time so far.
    auto finish2 = std::chrono::high_resolution_clock::now();
    elapsed = finish2 - start_time;
    totalTimeSoFar = elapsed.count();
    // Check if algorithm's taking longer than specified.
    if (totalTimeSoFar > timeout) {
      outcome_ = -1;  // Update 'outcome_' to -1 for 'timed-out'.
      timeSpent = totalTimeSoFar;  // Record time.
      return;
    }
  }

  // Path was found; populate the 'solution_' vector and update
  // 'solutionWeight_'.
  if (outcome_ == 1) {
    /* -- Forward path's vertices (including 'mid' vertex). -- */
    solution_.push_back(mid);
    Vertex trace = forwardEdgeTo[mid];
    while (trace != start) {
      solution_.push_back(trace);
      trace = forwardEdgeTo[trace];
    }
    solution_.push_back(trace);
    std::reverse(solution_.begin(), solution_.end());

    /* -- Backward path's vertices (excluding 'mid' vertex). -- */
    trace = backwardEdgeTo[mid];
    while (trace != end) {
      solution_.push_back(trace);
      trace = backwardEdgeTo[trace];
    }
    solution_.push_back(trace);

    solutionWeight_ = forwardDistTo[mid] + backwardDistTo[mid];
  }

  // Extract and record total time.
  auto finish3 = std::chrono::high_resolution_clock::now();
  elapsed = finish3 - start_time;
  timeSpent = elapsed.count();
}
