#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>

namespace cop4530 {

template<typename K, typename V>
class HashTable {
public:
    // Constructor. Initialize the hash table's size.
    explicit HashTable(std::size_t size = 101);

    // Destructor. Clean up all dynamic data.
    ~HashTable();

    // Check if the hash table contains a key.
    bool contains(const K& k) const;

    // Check if a key-value pair is in the hash table.
    bool match(const std::pair<K, V>& kv) const;

    // Insert a key-value pair into the hash table.
    bool insert(const std::pair<K, V>& kv);

    // Move version of insert.
    bool insert(std::pair<K, V>&& kv);

    // Remove a key (and its corresponding value) from the hash table.
    bool remove(const K& k);

    // Clear the hash table.
    void clear();

    // Load content from a file into the hash table.
    bool load(const char* filename);

    // Display all entries in the hash table.
    void dump() const;

    // Return the size of the hash table.
    std::size_t size() const;

    // Write all elements in the hash table into a file.
    bool write_to_file(const char* filename) const;

private:
    // Internal storage for the hash table; a vector of lists (chaining).
    std::vector<std::list<std::pair<K, V>>> theLists;
    //size of hash table
    int currentSize;
    // max_prime is used by the helpful functions provided
    // to you.
    static const unsigned int max_prime = 1301081;
    // the default_capacity is used if the initial capacity
    // of the underlying vector of the hash table is zero.
    static const unsigned int default_capacity = 11;

    // Delete all elements in the hash table.
    void makeEmpty();

    // Rehash the table if necessary.
    void rehash();

    // Compute the hash value for a key.
    std::size_t myhash(const K& k) const;

    // Helper function to find a prime number below a given value.
    unsigned long prime_below(unsigned long n);

    // Helper function to set prime numbers for the size of the vector.
    void setPrimes(std::vector<unsigned long>& v);
};

} // namespace cop4530

#include "hashtable.hpp"

#endif // HASHTABLE_H
