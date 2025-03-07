
#include "Library.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Library::Library() {}

Library::~Library() {}

bool Library::authenticateUser(const std::string& uid, 
                        const std::string& upassword,
                        int& outRole) 
{
    std::ifstream fin("data/users.csv");
    if (!fin.is_open()) {
        std::cerr << "Error: Unable to open users file" << std::endl;
        return false;
    }

    std::string line;
    // Skip header line 
    std::getline(fin, line);

    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string uid_real, upassword_real, role_str;

        // Parse fields
        std::getline(ss, uid_real, ',');
        std::getline(ss, upassword_real, ',');
        std::getline(ss, role_str, ',');

        if (uid == uid_real) {
            if (upassword == upassword_real) {
                try {
                    outRole = std::stoi(role_str);
                    std::cout << "Login Successful" << std::endl;
                    return true;
                }
                catch (...) {
                    std::cerr << "Invalid role format" << std::endl;
                    return false;
                }
            }
            else {
                std::cout << "Incorrect Password\nPlease try again" << std::endl;
                return false;
            }
        }
    }

    std::cout << "Username does not exist" << std::endl;
    return false;
}


bool Library::searchBook(const std::string& ISBN, Book &book) {
    std::ifstream fin("data/books.csv");
    if (!fin.is_open()) return false;

    std::string line;
    // Skip header
    std::getline(fin, line);

    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string field;
        
        // Skip first 4 fields (title, author, publisher, year)
        for(int i = 0; i < 4; i++) {
            std::getline(ss, field, ',');
        }
        
        // Read 5th field (ISBN)
        std::string currentISBN;
        std::getline(ss, currentISBN, ',');
        
        if (currentISBN == ISBN) {
            // Rewind and load full book data
            ss = std::stringstream(line);  // Reset stream
            book.loadFromCSV(ss);          // Load all fields
            fin.close();
            return true;
        }
    }
    
    fin.close();
    return false;
}

