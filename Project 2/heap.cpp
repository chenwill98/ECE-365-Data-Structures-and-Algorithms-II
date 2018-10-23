#include "heap.h"

// heap - The constructor allocates space for the nodes of the heap
// and the mapping (hash table) based on the specified capacity
heap::heap(int capacity) {

}

// insert - Inserts a new node into the binary heap
//
// Inserts a node with the specified id string, key,
// and optionally a pointer. They key is used to
// determine the final position of the new node.
//
// Returns:
//   0 on success
//   1 if the heap is already filled to capacity
//   2 if a node with the given id already exists (but the heap
//     is not filled to capacity)
int heap::insert(const std::string &id, int key, void *pv) {

}

// setKey - set the key of the specified node to the specified value
//
// I have decided that the class should provide this member function
// instead of two separate increaseKey and decreaseKey functions.
//
// Returns:
//   0 on success
//   1 if a node with the given id does not exist
int heap::setKey(const std::string &id, int key) {

}

// deleteMin - return the data associated with the smallest key
//             and delete that node from the binary heap
//
// If pId is supplied (i.e., it is not NULL), write to that address
// the id of the node being deleted. If pKey is supplied, write to
// that address the key of the node being deleted. If ppData is
// supplied, write to that address the associated void pointer.
//
// Returns:
//   0 on success
//   1 if the heap is empty
int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {

}

// remove - delete the node with the specified id from the binary heap
//
// If pKey is supplied, write to that address the key of the node
// being deleted. If ppData is supplied, write to that address the
// associated void pointer.
//
// Returns:
//   0 on success
//   1 if a node with the given id does not exist
int heap::remove(const std::string &id, int *pKey, void *ppData) {

}

// percolateUp - move a node up through a binary heap
void heap::percolateUp(int posCur) {

}

// percolateDown - move a node down through a binary heap
void heap::percolateDown(int posCur) {

}

// getPos - returns the position of a node in the binary heap
int heap::getPos(node *pn) {

}
