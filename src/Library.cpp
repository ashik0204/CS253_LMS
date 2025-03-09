
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

void Library::displayBooks() const{
    std::ifstream fin("data/books.csv");
    if (!fin.is_open()) {
        std::cerr << "Error: Unable to open books file" << std::endl;
        return;
    }       

    std::string line;
    // Skip header line
    std::getline(fin, line);
    std::cout<<"BookID\tTitle"<<std::endl;
    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string bookID, title,status;
        //;pading bookID
        std::getline(ss, bookID, ',');
        std::getline(ss, title, ',');
        std::string temp;
        for(int i=0;i<4;i++){
            std::getline(ss, temp, ',');
        }
        std::getline(ss, status, ',');
        if(status=="Available"||status=="available") std::cout<<bookID<<"\t"<<title<<std::endl;
    }
    fin.close();
}
void Library::displayBooksforReservation() const{
    std::ifstream fin("data/books.csv");
    if (!fin.is_open()) {
        std::cerr << "Error: Unable to open books file" << std::endl;
        return;
    }       

    std::string line;
    // Skip header line
    std::getline(fin, line);
    std::cout<<"BookID\tTitle"<<std::endl;
    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string bookID, title,status;
        //;pading bookID
        std::getline(ss, bookID, ',');
        std::getline(ss, title, ',');
        std::string temp;
        for(int i=0;i<6;i++){
            std::getline(ss, temp, ',');
        }
        std::getline(ss, status, ',');
        if(status=="0") std::cout<<bookID<<"\t"<<title<<std::endl;
    }
    fin.close();
}

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


bool Library::searchBook(const std::string& bookID, Book &book) {
    std::ifstream fin("data/books.csv");
    if (!fin.is_open()) return false;

    std::string line;
    // Skip header
    std::getline(fin, line);

    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string current_bookID;
        std::getline(ss, current_bookID, ',');
        if (current_bookID == bookID) {
            //Loading full book data
            ss = std::stringstream(line);  // Resetting stream
            book.loadFromCSV(ss);          // Loading  all fields
            fin.close();
            return true;
        }
    }
    
    fin.close();
    return false;
}

