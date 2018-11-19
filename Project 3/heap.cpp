#include "heap.h"

// heap - The constructor allocates space for the nodes of the heap
// and the mapping (hash table) based on the specified capacity
heap::heap(int capacity) {
        data.resize(capacity + 1);
        mapping = new hashTable(capacity * 2);
        this->capacity = capacity;
        filled = 0; // Keeps track of index of bottom-rightmost node
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
        if (filled < capacity)
                if (mapping->contains(id) == false) {
                        filled++;
                        data[filled].id = id;
                        data[filled].key = key;
                        data[filled].pData = pv;
                        mapping->insert(id, &data[filled]);
                        percolateUp(filled); // Ensures proper placement of new node
                } else
                        return 2;
        else
                return 1;
        return 0;
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
        int original;
        if (mapping->contains(id) == true) {
                node * pn = static_cast<node*> (mapping->getPointer(id));
                original = pn->key;
                pn->key = key;
                int pos = getPos(pn);
                if (key < original) // Ensures that the min heap retains its properties
                        percolateUp(pos);
                if (key > original)
                        percolateDown(pos);
                return 0;
        } else
                return 1;


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

        if (filled > 0) {
                if (pId != nullptr)
                        *pId = data[1].id;
                if (pKey != nullptr)
                        *pKey = data[1].key;
                if (ppData != nullptr)
                        *(static_cast<void **> (ppData)) = data[1].pData;
                remove(data[1].id);   // Simply removes the first element as it would any other
                return 0;

        } else
                return 1;
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
        int pos, original;
        if (mapping->contains(id) == true) {
                node * pn = static_cast<node*> (mapping->getPointer(id));
                if (pKey != nullptr)
                        *pKey = pn->key;
                if (ppData != nullptr)
                        *(static_cast<void **> (ppData)) = pn->pData;

                pos = getPos(pn);
                mapping->remove(id);
                original = data[pos].key;
                std::swap(data[pos], data[filled]); // Swaps node with last node
                mapping->setPointer(data[pos].id, &data[pos]); // Sets pointer to the new node in that position
                // No need to set pointer to the previous min node since it's supposed to be deleted
                filled--;

                if (data[pos].key > original) { // Percolates up or down
                        percolateDown(pos);
                } else if (data[pos].key < original) {
                        percolateUp(pos);
                }

                return 0;
        } else
                return 1;
}

// percolateUp - move a node up through a binary heap
void heap::percolateUp(int posCur) {
        while (data[posCur].key < data[posCur/2].key && posCur > 1) {
                std::swap(data[posCur], data[posCur/2]);
                mapping->setPointer(data[posCur].id, &data[posCur]);
                mapping->setPointer(data[posCur/2].id, &data[posCur/2]);
                posCur /= 2;
        }
}

// percolateDown - move a node down through a binary heap
void heap::percolateDown(int posCur) {
        int child1, child2, smallerChild;
        while (2 * posCur <= filled) {
                child1 = 2 * posCur;
                child2 = child1 + 1;
                smallerChild = child1;
                if (data[child2].key < data[smallerChild].key && child1 < filled) {
                        smallerChild = child2;
                }
                if (data[smallerChild].key < data[posCur].key) {
                        std::swap(data[posCur], data[smallerChild]);
                        mapping->setPointer(data[posCur].id, &data[posCur]);
                        mapping->setPointer(data[smallerChild].id, &data[smallerChild]);
                        posCur = smallerChild;
                } else {
                        break;
                }
        }
}

// getPos - returns the position of a node in the binary heap
int heap::getPos(node *pn) {
        int pos = pn - &data[0];
        return pos;
}
