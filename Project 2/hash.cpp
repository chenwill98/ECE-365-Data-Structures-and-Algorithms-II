//William Chen
//Professor Sable
//ECE-365 Project 2

#include "hash.h"

int prime_sizes[] = {100003, 200003, 400009, 800011, 1600033, 3200003, 6400013, 12800009, 25600013, 51200027, 102400007, 204800017, 409600001, 819200003, 1638400013};

hashTable::hashTable(int size) {
        int prime = getPrime(size);
        capacity = prime;
        filled = 0;
        data.resize(capacity);

        for (int i = 0; i < data.size(); i++)
                data[i].isOccupied = data[i].isOccupied = false;
}

// Insert the specified key into the hash table.
// If an optional pointer is provided,
// associate that pointer with the key.
// Returns 0 on success,
// 1 if key already exists in hash table,
// 2 if rehash fails.
int hashTable::insert(const std::string &key, void *pv) {
        int index = hash(key);
        if (filled*2 >= capacity)
                if (rehash() == false)
                        return 2;

        while (data[index].isOccupied) {
                if (data[index].key == key)
                        if (data[index].isDeleted) {
                                data[index].isDeleted = false;
                                return 0;
                        } else
                                return 1;

                if (index != capacity-1)
                        index++;
                else
                        index = 0;
        }

        filled++;
        data[index].key = key;
        data[index].isOccupied = true;
        data[index].isDeleted = false;
        data[index].pv = pv;
        return 0;
}

// Check if the specified key is in the hash table.
// If so, return true; otherwise, return false.
bool hashTable::contains(const std::string &key) {
        if (findPos(key) == -1)
                return false;
        else
                return true;
}

// Get the pointer associated with the specified key.
// If the key does not exist in the hash table, return NULL.
// If an optional pointer to a bool is provided,
// set the bool to true if the key is in the hash table,
// and set the bool to false otherwise.
void * hashTable::getPointer(const std::string &key, bool *b) {
        int index = findPos(key);
        if (index != -1) {
                if (b != nullptr)
                        *b = true;
                return data[index].pv;
        } else {
                if (b != nullptr)
                        *b = false;
                return nullptr;
        }
}

// Set the pointer associated with the specified key.
// Returns 0 on success,
// 1 if the key does not exist in the hash table.
int hashTable::setPointer(const std::string &key, void *pv) {
        int index = findPos(key);
        if (index != -1) {
                data[index].pv = pv;
                return 0;
        } else {
                return 1;
        }
}

// Delete the item with the specified key.
// Returns true on success,
// false if the specified key is not in the hash table.
bool hashTable::remove(const std::string &key) {
        int index = findPos(key);
        if (index != -1) {
                data[index].isDeleted = true;
                return true;
        } else {
                return false;
        }
}

// The hash function.
int hashTable::hash(const std::string &key) {
        std::hash<std::string> str_hash;
        return str_hash(key) % capacity;
}

// Search for an item with the specified key.
// Return the position if found, -1 otherwise.
int hashTable::findPos(const std::string &key) {
        int index = hash(key);
        while (data[index].isOccupied) {
                if (data[index].key == key && !data[index].isDeleted)
                        return index;
                if (index != capacity-1)
                        index++;
                else
                        index = 0;
        }
        return -1;
}

// The rehash function; makes the hash table bigger.
// Returns true on success, false if memory allocation fails.
bool hashTable::rehash() {
        int prime_prime = getPrime(2*capacity);
        capacity = prime_prime;
        filled = 0;
        std::vector<hashItem> temp_data = data;

        try {
                data.resize(prime_prime);
        } catch (std::bad_alloc) {
                return false;
        }

        for (int i = 0; i < data.size(); i++)
                data[i].isOccupied = data[i].isOccupied = false;

        for (int i = 0; i < temp_data.size(); i++)
                if (temp_data[i].isOccupied && !temp_data[i].isDeleted)
                        insert(temp_data[i].key, temp_data[i].pv);
        return true;
}

// Return a prime number at least as large as size.
// Uses a precomputed sequence of selected prime numbers.
unsigned int hashTable::getPrime(int size) {
        for (int i = 0; i < sizeof(prime_sizes)/sizeof(int); i++)
                if (size <= prime_sizes[i])
                        return prime_sizes[i];
}
