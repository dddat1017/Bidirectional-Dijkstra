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

/*
 * Represents a graph of vertices.
*/
template <typename Vertex> class Graph {
 public:
  /*
  * Returns the vector of (unique_ptr's to) outgoing edges from the given vertex.
  */
  virtual std::vector<std::unique_ptr<WeightedEdge<Vertex>>> neighbors(const Vertex& v) = 0;
};

#endif  // GRAPH_H_
