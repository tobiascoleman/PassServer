#include <iostream>
#include <string>
#include "passserver.h"

using namespace std;

void Menu()
{
    cout << "\n\n";
    cout << "l - Load From File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice : ";
}

int main() {
    int size;
    cout<< "Enter preferred hash table size: ";
    cin >> size;
    PassServer passServer(size);

    char choice;
    string filename, username, password, newpassword;

    Menu(); // Display menu

    while (cin >> choice) {
        switch (choice) {
            case 'l':
                cout << "Enter password file name to load from: ";
                cin >> filename;
                cout << endl;
                if (passServer.load(filename.c_str())) {
                    cout << "Passwords successfully loaded from file." << endl;
                } else {
                    cout << "Error loading passwords from file." << endl;
                }
                break;
            case 'a':
                cout << "Enter username: ";
                cin >> username;
                cout << endl << "Enter password: ";
                cin >> password;
                cout << endl;
                if (passServer.addUser(make_pair(username, password))) {
                    cout << "User successfully added." << endl;
                } else {
                    cout << "Error adding user." << endl;
                }
                break;
            case 'r':
                cout << "Enter username to remove: ";
                cin >> username;
                cout << endl;
                if (passServer.removeUser(username)) {
                    cout << "User successfully removed." << endl;
                } else {
                    cout << "Error removing user." << endl;
                }
                break;
            case 'c':
                cout << "Enter username: ";
                cin >> username;
                cout << endl;
                cout << "Enter old password: ";
                cin >> password;
                cout << endl;
                cout << "Enter new password: ";
                cin >> newpassword;
                cout << endl;
                if (passServer.changePassword(std::pair<std::string, std::string>(username, password), newpassword)) {
                    cout << "Password successfully changed." << endl;
                } else {
                    cout << "Error changing password." << endl;
                }
                break;
            case 'f':
                cout << "Enter username to find: ";
                cin >> username;
                cout << endl;
                if (passServer.find(username)) {
                    cout << "User found." << endl;
                } else {
                    cout << "User not found." << endl;
                }
                break;
            case 'd':
                passServer.dump();
                break;
            case 's':
                cout << "Size of HashTable: " << passServer.size() << endl;
                break;
            case 'w':
                cout << "Enter password file name to write to: ";
                cin >> filename;
                cout << endl;
                if (passServer.write_to_file(filename.c_str())) {
                    cout << "Passwords successfully written to file." << endl;
                } else {
                    cout << "Error writing passwords to file." << endl;
                }
                break;
            case 'x':
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        Menu();
    }
    return 0;
}