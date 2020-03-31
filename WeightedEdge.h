/*
 * Author: Dat Do
 * Contact: datdo1017@gmail.com
 * Copyright 2020 Dat Do
*/

#ifndef WEIGHTEDEDGE_H_
#define WEIGHTEDEDGE_H_

/*
 * Utility class that represents a weighted edge between two vertices.
*/
template <typename Vertex> class WeightedEdge {
 public:
  /*
   * Ctor & Dtor.
  */
  WeightedEdge(const Vertex v, const Vertex w, const double weight) :
              v_(v), w_(w), weight_(weight) { }
  ~WeightedEdge() { }

  /*
   * Returns the 'from' vertex.
  */
  Vertex from() const { return v_; }

  /*
   * Returns the 'to' vertex.
  */
  Vertex to() const { return w_; }

  /*
   * Returns the weight of the edge.
  */
  double weight() const { return weight_; }

  /*
   * Returns the "inverse" edge of this edge
   * (i.e. flipping the 'from' and 'to' vertices but leaving
   * the weight unchanged.).
  */
  WeightedEdge<Vertex> flip() const
          { return WeightedEdge<Vertex>(w_, v_, weight_); }

 private:
  Vertex v_;  // 'from' vertex.
  Vertex w_;  // 'to' vertex.
  double weight_;  // Weight of the edge.
};

#endif  // WEIGHTEDEDGE_H_
