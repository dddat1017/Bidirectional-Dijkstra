#ifndef EXTRINSICMINPQ_H_
#define EXTRINSICMINPQ_H_

/*
 * Priority queue where objects have a priority that is provided extrinsically,
 * i.e., priorities are supplied as an argument during insertion and can be
 * changed using the changePriority method. Cannot contain duplicate items.
*/
template <typename T> class ExtrinsicMinPQ {
 public:
  /*
   * Adds an item with the given priority value.
   * Returns true on success, false if item is already present in the PQ.
  */
  virtual bool add(const T& item, double priority) = 0;

  /*
   * Returns true if the PQ contains the given item; false otherwise.
  */
  virtual bool contains(const T& item) const = 0;

  /*
   * Returns the pointer to the item with the smallest priority.
   * Returns 'nullptr' if the PQ is empty.
   * Caller does not receive ownership of the item.
  */
  virtual const T* getSmallest() const = 0;

  /*
   * Removes and returns (the pointer to) the item with the smallest priority.
   * Returns 'nullptr' if the PQ is empty.
   * Caller receives ownership of the item.
  */
  virtual T* removeSmallest() = 0;

  /*
   * Changes the priority of the given item.
   * Returns true on success, false if item is not present in the PQ.
  */
  virtual bool changePriority(const T& item, double priority) = 0;

  /*
   * Returns the number of items in the PQ.
  */
  virtual int size() const = 0;

  /*
   * Returns true if the PQ is empty, false otherwise.
  */
  bool isEmpty() const { return size() == 0; } 
};

#endif  // EXTRINSICMINPQ_H_
