/*
 * Author: Dat Do
 * Contact: datdo1017@gmail.com
 * Copyright 2020 Dat Do
*/

#include <memory>
#include <vector>
#include "Graph.h"
#include "WeightedEdge.h"

#ifndef WEIGHTEDDIRECTEDGRAPH_H_
#define WEIGHTEDDIRECTEDGRAPH_H_

class WeightedDirectedGraph: public Graph<int> {
 public:
  /*
   * Ctor.
   * Takes in number of vertices specified and populate the
   * underlying vectors accordingly.
  */
  explicit WeightedDirectedGraph(const int& V) {
    for (int i = 0; i < V; i++) {
      outgoing.push_back(vector<unique_ptr<WeightedEdge<int>>>());
      incoming.push_back(vector<unique_ptr<WeightedEdge<int>>>());
    }
  }

  /*
   * Dtor.
  */
  ~WeightedDirectedGraph() { }

  const vector<unique_ptr<WeightedEdge<int>>>& outgoingNeighbors(
                                            const int& v) const {
    return outgoing[v];
  }

  const vector<unique_ptr<WeightedEdge<int>>>& incomingNeighbors(
                                            const int& v) const {
    return incoming[v];
  }

  /*
   * Adds an edge to the graph. Populates both underlying vectors
   * accordingly. Arguments:
   * 
   * - p: The 'from' vertex.
   * - q: The 'to' vertex.
   * - weight: Weight of the edge.
  */
  void addEdge(const int p, const int q, const double weight) {
    outgoing[p].push_back(
      unique_ptr<WeightedEdge<int>>(new WeightedEdge<int>(p, q, weight)));
    incoming[q].push_back(
      unique_ptr<WeightedEdge<int>>(new WeightedEdge<int>(q, p, weight)));
  }

 private:
  vector<vector<unique_ptr<WeightedEdge<int>>>> outgoing;
  vector<vector<unique_ptr<WeightedEdge<int>>>> incoming;
};

#endif  // WEIGHTEDDIRECTEDGRAPH_H_
