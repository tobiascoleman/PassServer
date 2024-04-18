#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <iostream>
#include <fstream>

namespace cop4530 {
    template<typename K, typename V>
    HashTable<K, V>::HashTable(std::size_t size) : theLists(prime_below(size)), currentSize(0) {}

    template<typename K, typename V>
    HashTable<K, V>::~HashTable() {
        clear();
    }

    template<typename K, typename V>
    bool HashTable<K, V>::contains(const K &k) const {
        auto &whichList = theLists[myhash(k)];
        for(auto& bucket : whichList){
            if(bucket.first == k){
                return true;
            }
        }
        return false;
    }

    template<typename K, typename V>
    bool HashTable<K, V>::match(const std::pair<K, V> &kv) const {
        auto &whichList = theLists[myhash(kv.first)];
        for (const auto &pair: whichList) {
            if (pair.first == kv.first && pair.second == kv.second)
                return true;
        }
        return false;
    }

    template<typename K, typename V>
    bool HashTable<K, V>::insert(const std::pair<K, V> &kv) {
        auto &whichList = theLists[myhash(kv.first)];
        for(auto& bucket : whichList){
            if(bucket.first == kv.first){
                return false;
            }
        }

        whichList.push_back(kv);

        //  rehash, see Section 5.5
        if (++currentSize > theLists.size())
            rehash();

        return true;
    }

    template<typename K, typename V>
    bool HashTable<K, V>::insert(std::pair<K, V> &&kv) {
        auto &whichList = theLists[myhash(kv.first)];
        for(auto& bucket : whichList){
            if(bucket.first == kv.first){
                return false;
            }
        }

        whichList.push_back(std::move(kv));

        //  rehash, see Section 5.5
        if (++currentSize > theLists.size())
            rehash();

        return true;
    }

    template<typename K, typename V>
    bool HashTable<K, V>::remove(const K &k) {
        auto& whichList = theLists[myhash(k)];
        for (auto it = whichList.begin(); it != whichList.end(); ++it) {
            if (it->first == k) {
                whichList.erase(it);
                --currentSize;
                return true;
            }
        }
        return false;
    }

    template<typename K, typename V>
    void HashTable<K, V>::clear() {
        makeEmpty();
        currentSize = 0;
    }

    template<typename K, typename V>
    bool HashTable<K, V>::load(const char *filename) {
        std::ifstream in;
        in.open(filename);
        if (!in.is_open()) {
            std::cerr << "Error opening file." << std::endl;
            return false;
        }
        K key;
        V value;
        while (!in.eof()) {
            in>>key>>value;
            insert(std::pair<K, V>(key, value));
        }
        in.close();
        return true;
    }

    template<typename K, typename V>
    void HashTable<K, V>::dump() const {
        int i = 0;
        std::cout<<"V[" << i++ << "]: " << std::endl;
        for (const auto &bucket: theLists) {
            std::cout << "V[" << i++ << "]";
            for (const auto &kv: bucket) {
                std::cout<<kv.first << " " << kv.second;
                if (bucket.size() > 1)
                    std::cout << " : ";
            }
            std::cout << std::endl;
        }
    }

    template<typename K, typename V>
    std::size_t HashTable<K, V>::size() const {
        return currentSize;
    }

    template<typename K, typename V>
    bool HashTable<K, V>::write_to_file(const char *filename) const {
        std::ofstream out;
        out.open(filename);
        if (!filename) {
            std::cerr << "Error opening file." << std::endl;
            return false;
        }
        for (const auto &bucket: theLists) {
            for (const auto &kv: bucket) {
                out << kv.first << " " << kv.second << std::endl;
            }
        }
        out.close();
        return true;
    }

    template<typename K, typename V>
    void HashTable<K, V>::makeEmpty() {
        for (auto &thisList: theLists) {
            thisList.clear();
        }
    }

    template<typename K, typename V>
    void HashTable<K, V>::rehash() {
        auto oldLists = theLists;

        // create new double-sized, empty table
        theLists.resize(prime_below(2 * theLists.size()));
        for (auto &thisList: theLists)
            thisList.clear();

        // copy table over
        currentSize = 0;
        for (auto &thisList: oldLists)
            for (auto &x: thisList)
                insert(std::move(x));

    }

    template<typename K, typename V>
    std::size_t HashTable<K, V>::myhash(const K &k) const {
        static std::hash<K> hf;
        return hf(k) % theLists.size();
    }

    template<typename K, typename V>
    unsigned long HashTable<K, V>::prime_below(unsigned long n) {
        if (n > max_prime) {
            std::cerr << "** input too large for prime_below()\n";
            return 0;
        }
        if (n == max_prime) {
            return max_prime;
        }
        if (n <= 1) {
            std::cerr << "** input too small \n";
            return 0;
        }

        // now: 2 <= n < max_prime
        std::vector<unsigned long> v(n + 1);
        setPrimes(v);
        while (n > 2) {
            if (v[n] == 1)
                return n;
            --n;
        }

        return 2;
    }

    //Sets all prime number indexes to 1. Called by method prime_below(n)
    template<typename K, typename V>
    void HashTable<K, V>::setPrimes(std::vector<unsigned long> &vprimes) {
        int i = 0;
        int j = 0;

        vprimes[0] = 0;
        vprimes[1] = 0;
        int n = vprimes.capacity();

        for (i = 2; i < n; ++i)
            vprimes[i] = 1;

        for (i = 2; i * i < n; ++i) {
            if (vprimes[i] == 1)
                for (j = i + i; j < n; j += i)
                    vprimes[j] = 0;
        }
    }
}
#endif // HASHTABLE_HPP