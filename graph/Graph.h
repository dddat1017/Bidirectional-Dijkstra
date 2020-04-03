/*
 * Author: Dat Do
 * Contact: datdo1017@gmail.com
 * Copyright 2020 Dat Do
*/

#ifndef GRAPH_H_
#define GRAPH_H_

#include <memory>
#include <vector>
#include "WeightedEdge.h"

using std::unique_ptr;
using std::vector;

/*
 * Represents a graph of vertices.
 * Cannot contain duplicate vertices nor negative edge weights.
 * Vertices' type must support less-than operator (<) and
 * equal-to operator (==).
 *
 * Class with pure virtual functions. Cannot instantiate an object
 * of this class; meant for deriving subclasses.
*/
template <typename Vertex> class Graph {
 public:
  /*
   * Returns the vector of (unique_ptr's to) outgoing edges from the given vertex.
   * Caller does not receive ownership of the vector (i.e. cannot change the vector
   * in any way); only access to the elements is provided.
  */
  virtual const vector<unique_ptr<WeightedEdge<Vertex>>>& outgoingNeighbors(
                                                  const Vertex& v) const = 0;

  /*
   * Returns the vector of (unique_ptr's to) incoming edges to the given vertex.
   * Caller does not receive ownership of the vector (i.e. cannot change the vector
   * in any way); only access to the elements is provided.
  */
  virtual const vector<unique_ptr<WeightedEdge<Vertex>>>& incomingNeighbors(
                                                  const Vertex& v) const = 0;
};

#endif  // GRAPH_H_
