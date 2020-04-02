/*
 * Author: Dat Do
 * Contact: datdo1017@gmail.com
 * Copyright 2020 Dat Do
*/

#ifndef EXTRINSICMINPQ_H_
#define EXTRINSICMINPQ_H_

#include <memory>
#include <vector>
#include <map>

/*
 * Structure storing:
 * 1. index of the item in the PQ.
 * 2. priority of the item.
*/ 
typedef struct {
  int index;
  double priority;
} PriorityNode;

/*
 * Priority queue where objects have a priority that is provided extrinsically,
 * i.e., priorities are supplied as an argument during insertion and can be
 * changed using the changePriority() function. Cannot contain duplicate items.
 * Items' type must support less than operator (<).
*/
template <typename T> class ExtrinsicMinPQ {
 public:
  /*
   * Ctor & Dtor.
  */
  ExtrinsicMinPQ() { }
  ~ExtrinsicMinPQ() { }

  /*
   * Adds an item with the given priority value.
   * Returns true on success, false if item is already present in the PQ.
  */
  bool add(const T item, const double priority);

  /*
   * Returns true if the PQ contains the given item; false otherwise.
  */
  bool contains(const T& item) const;

  /*
   * Returns the pointer to the item with the smallest priority.
   * Returns 'nullptr' if the PQ is empty.
   * Caller does not receive ownership of the item.
  */
  const T* getSmallest() const;

  /*
   * Removes and returns (the pointer to) the item with the
   * smallest priority. Returns 'nullptr' if the PQ is empty.
   * Caller receives ownership of the item and must 'delete'
   * the pointer once done with it.
  */
  T* removeSmallest();

  /*
   * Changes the priority of the given item.
   * Returns true on success, false if item is not present
   * in the PQ.
  */
  bool changePriority(const T& item, const double priority);

  /*
   * Returns the number of items in the PQ.
  */
  int size() const { return pq.size(); }

  /*
   * Returns true if the PQ is empty, false otherwise.
  */
  bool isEmpty() const { return size() == 0; }

 private:
  /* The PQ, which is a binary min-heap. Implemented as a
   * vector of unique_ptr's to the items (whose type
   * is user-specified).
   * The item with the smallest priority would be at
   * index 0, its children would be at index 1
   * (for left child) and index 2 (for right child),
   * and so on.
  */
  std::vector<std::unique_ptr<T>> pq;

  /*
   * An auxiliary map to store information of each item.
   * Each key is the item itself, which maps to a
   * PriorityNode struct. Items' type must support less
   * than operator (<) since maps are typically implemented as
   * binary search trees.
  */
  std::map<T, PriorityNode> storage;

  /*
   * Swaps the items at index 'a' and 'b' in the PQ.
  */
  void swapItems(const int a, const int b);

  /*
   * Swims an item to its correct position after adding
   * it to the PQ. Arguments:
   * 
   * - currentIndex: The index in which the item is
   * currently at in the PQ.
   * 
   * - priority: The priority of the item.
  */
  void swim(int currentIndex, const double& priority);

  /*
   * Sinks an item to its correct position after removing
   * the item with the smallest priority. Arguments:
   * 
   * - currentIndex: The index in which the item is
   * currently at in the PQ.
   * 
   * - priority: The priority of the item.
  */
  void sink(int currentIndex, const double& priority);
};

#include "ExtrinsicMinPQ.cpp"

#endif  // EXTRINSICMINPQ_H_
