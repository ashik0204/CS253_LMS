#include "Library.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool Library::authenticateUser(const std::string& uid, const std::string& upassword){
        std::ifstream fin;
        fin.open("account.csv");
        std::string line;
        while (std::getline(fin, line)) {
            std::string uid_real, upassword_real;
            std::stringstream ss(line);
            std::getline(ss, uid_real, ',');
            std::getline(ss, upassword_real, ',');
            if (uid == uid_real ) {
                if(upassword == upassword_real){
                    fin.close();
                    std::cout<<"Login Successful"<<std::endl;
                    return true;
                }
                else{
                    fin.close();
                    std::cout<<"Incorrect Password\n"<<"Please try again"<<std::endl;
                    return false;
                }
            }
            
        }
        fin.close();
        std::cout<<"Username does not exist"<<std::endl;
        return false;
}
bool Library::searchBook(const std::string& ISBN, Book &book) {
    std::ifstream fin("books.csv");
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

