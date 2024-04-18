#include "passserver.h"
#include <unistd.h>
#include <crypt.h>

PassServer::PassServer(size_t size) : hashTable(size) {}

PassServer::~PassServer() {
    hashTable.clear();
}

bool PassServer::load(const char* filename) {
    return hashTable.load(filename);
}

bool PassServer::addUser(std::pair<std::string, std::string>& kv) {
    std::string encPassword = encrypt(kv.second);
    return hashTable.insert(std::pair<std::string, std::string>(kv.first, encPassword));
}

bool PassServer::addUser(std::pair<std::string, std::string>&& kv) {
    std::string encPassword = encrypt(kv.second);
    return hashTable.insert(std::pair<std::string, std::string>(std::move(kv.first), std::move(encPassword)));
}

bool PassServer::removeUser(const std::string& k) {
    return hashTable.remove(k);
}

bool PassServer::changePassword(const std::pair<std::string, std::string>& p, const std::string& newpassword) {

    std::string encryptedNewPassword = encrypt(newpassword);
    std::string encryptedOldPassword = encrypt(p.second);
    if (!hashTable.contains(p.first)) {
        return false; // User not found
    }
    if (!hashTable.match(std::pair<std::string, std::string>(p.first, encryptedOldPassword))) {
        return false; // Provided old password does not match
    }

    // Check if the new password is the same as the old password
    if (p.second == newpassword) {
        return false;
    }

    std::pair<std::string, std::string> newUserPassword(p.first, encryptedNewPassword);
    hashTable.remove(p.first);

    return hashTable.insert(newUserPassword);
}

bool PassServer::find(const std::string& user) {
    return hashTable.contains(user);
}

void PassServer::dump() {
    hashTable.dump();
}

size_t PassServer::size() {
    return hashTable.size();
}

bool PassServer::write_to_file(const char* filename) {
    return hashTable.write_to_file(filename);
}

std::string PassServer::encrypt(const std::string& str) {
    char salt[] = "$1$########";
    std::string encrypted = crypt(str.c_str(), salt);
    return encrypted.substr(12); //don't need the first 12 characters
}
