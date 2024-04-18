#ifndef PASSSERVER_H
#define PASSSERVER_H

#include "hashtable.h"
#include <utility>
#include <string>

class PassServer {
public:
    PassServer(size_t size = 101);
    ~PassServer();
    bool load(const char *filename);
    bool addUser(std::pair<std::string, std::string>& kv);
    bool addUser(std::pair<std::string, std::string>&& kv);
    bool removeUser(const std::string& k);
    bool changePassword(const std::pair<std::string, std::string>& p, const std::string& newpassword);
    bool find(const std::string& user);
    void dump();
    size_t size();
    bool write_to_file(const char* filename);

private:
    cop4530::HashTable<std::string, std::string> hashTable;

    std::string encrypt(const std::string& str);
};

#endif // PASSSERVER_H
