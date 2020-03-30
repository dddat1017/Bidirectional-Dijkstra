/*
 * Author: Dat Do
 * Contact: datdo1017@gmail.com
 * Copyright 2020 Dat Do
*/

/*
 * Helper functions to calculate the index position of an
 * item's child (left or right) in the underlying vector.
*/
static int leftIndex(int parentIndex, int size);
static int rightIndex(int parentIndex, int size);

/*
 * Helper function to calculate the index position of an
 * item's parent in the underlying vector.
*/
static int parentIndex(int childIndex);

template <typename T>
bool ExtrinsicMinPQ<T>::add(T item, double priority) {
  PriorityNode pn;

  // Easy add when PQ is empty.
  if (isEmpty()) {
    // Construct a unique_ptr object from the dynamically
    // allocated item. Then, add the unique_ptr to the PQ.
    pq.push_back(std::unique_ptr<T>(new T(item)));
    pn.index = size() - 1;
    pn.priority = priority;
    storage[item] = pn;  // Add to the map.
    return true;
  }

  // Return false if item already exists in the PQ.
  if (storage.find(item) != storage.end())
    return false;

  // Add to the PQ and map.
  pq.push_back(std::unique_ptr<T>(new T(item)));
  pn.index = size() - 1;
  pn.priority = priority;
  storage[item] = pn;

  // Swim up the PQ if necessary.
  int currentIndex = size() - 1;
  swim(currentIndex, priority);
  return true;
}

template <typename T>
bool ExtrinsicMinPQ<T>::contains(const T& item) const {
  return (storage.find(item) != storage.end());
}

template <typename T>
const T* ExtrinsicMinPQ<T>::getSmallest() const {
  if (isEmpty())
    return nullptr;

  // Item with smallest priority is at index 0.
  return pq[0].get();
}

template <typename T>
T* ExtrinsicMinPQ<T>::removeSmallest() {
  if (isEmpty())
    return nullptr;

  // Swap the item with the smallest priority with whatever
  // is at the last index in the PQ. Only swap if more than
  // 1 item.
  int lastIndex = size() - 1;
  if (size() > 1)
    swapItems(lastIndex, 0);

  // Extract the pointer to return.
  T* result = pq[lastIndex].release();

  // Remove item with the smallest priority from the PQ and map.
  storage.erase(*result);
  pq.erase(pq.begin() + lastIndex);

  // Return right away if PQ only contained one item.
  if (isEmpty())
    return result;

  // Sink the item that is currently at index 0 to its correct
  // place in the PQ.
  double priority = storage[*(pq[0])].priority;
  sink(0, priority);

  return result;
}

template <typename T>
bool ExtrinsicMinPQ<T>::changePriority(const T& item, double priority) {
  // Return false if the item is not in the PQ.
  if (storage.find(item) == storage.end())
    return false;

  // Change the priority of the item in the map.
  storage[item].priority = priority;

  // First, try swimming the item up the PQ.
  // Then, attempt to sink the item down the PQ.
  // Will be only one or the other.
  int currentIndex = storage[item].index;
  swim(currentIndex, priority);
  sink(currentIndex, priority);
  return true;
}

template <typename T>
void ExtrinsicMinPQ<T>::swapItems(int a, int b) {
  // Release() and Reset() the two pointers to transfer ownership.
  T* aPtr = pq[a].release();
  T* bPtr = pq[b].release();
  pq[a].reset(bPtr);
  pq[b].reset(aPtr);

  // Update the new index of each item in the map.
  storage[*aPtr].index = b;
  storage[*bPtr].index = a;
}

template <typename T>
void ExtrinsicMinPQ<T>::swim(int currentIndex, double priority) {
  int pi = parentIndex(currentIndex);
  T parent = *(pq[pi]);  // Extract the parent item.

  // Keep comparing the item's priority to its parent's priority and
  // swap when needed. Also, making sure that currentIndex is greater
  // than the parent index as it swims up.
  while ((priority < storage[parent].priority) && (currentIndex > pi)) {
    swapItems(currentIndex, pi);
    currentIndex = pi;
    pi = parentIndex(pi);
    parent = *(pq[pi]);
  }
}

template <typename T>
void ExtrinsicMinPQ<T>::sink(int currentIndex, double priority) {
  // Assume left child is item with the smaller priority than the
  // right child.
  int childIndex = leftIndex(currentIndex, size());
  while (childIndex != -1) {
    T child = *(pq[childIndex]);

    // Check if the right child exists, and see if it has a smaller
    // priority than the left child. If so, right child is the child
    // to be compared with.
    int ri = rightIndex(currentIndex, size());
    if (ri != -1) {
      T rightChild = *(pq[ri]);
      if (storage[rightChild].priority < storage[child].priority) {
        childIndex = ri;
        child = rightChild;
      }
    }

    // Check if the priority of the element that is being sunk is
    // greater than the priority of the smaller child. If so, swap.
    if (priority > storage[child].priority) {
      swapItems(currentIndex, childIndex);
      currentIndex = childIndex;
      childIndex = leftIndex(childIndex, size());
    } else {
      break;
    }
  }
}

static int leftIndex(int parentIndex, int size) {
  int index = (parentIndex * 2) + 1;
  if (index < size)
    return index;
  return -1;
}

static int rightIndex(int parentIndex, int size) {
  int index = (parentIndex * 2) + 2;
  if (index < size)
    return index;
  return -1;
}

static int parentIndex(int childIndex) {
  int index = (childIndex - 1) / 2;
  if (index >= 0)
    return index;
  return -1;
}
