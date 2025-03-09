
#include "Librarian.h"
#include "User.h"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iostream>

//helper functions



// Constructor
Librarian::Librarian(std::string uid, const std::string &upassword) 
    : User(uid, upassword) {}

// User Management
bool Librarian::create_user(std::string uid, std::string upassword, int role) {
    // Add to users.csv

    std::ofstream users_file("data/users.csv", std::ios::app);//appending to users file
    if(!users_file.is_open()) return false;
    users_file << uid << "," << upassword << "," << role << "\n";
    users_file.close();

    // Add to accounts.csv
    std::ofstream accounts_file("data/accounts.csv", std::ios::app);
    if (!accounts_file) return false;
    accounts_file << uid << "," 
                << std::boolalpha << (role != 2) << "," // isFaculty
                << "0.0,,,,\n"; // fines, borrowed, overdue, history
    accounts_file.close();
    
    return true;
}


int Librarian::delete_user(std::string uid) {
    
    int flag=0;
    std::string line;
    // Delete from accounts.csv
    std::vector<std::string> accounts_lines;
    std::ifstream accounts_in("data/accounts.csv");//reading from accounts file
    while(std::getline(accounts_in, line)) {
        std::string current_uid;
        std::stringstream ss(line);
        std::getline(ss, current_uid, ',');
        if(current_uid != uid) accounts_lines.push_back(line);
        if(current_uid == uid) {
            flag=1;
            std::string temp;
            for(int i=0;i<2;i++){
                std::getline(ss, temp, ',');
            }
            std::string borrowed, overdue;
            std::getline(ss, borrowed, ',');
            std::getline(ss, overdue, ',');
            if(borrowed!=""||overdue!="") {
                flag=2;
                accounts_lines.push_back(line);
            }
        }

    }
    accounts_in.close();
    
    std::ofstream accounts_out("data/accounts.csv");
    for(const auto& l : accounts_lines) accounts_out << l << "\n";
    accounts_out.close();
    // Delete from users.csv
    std::vector<std::string> users_lines;
    std::ifstream users_in("data/users.csv");
    
    while(std::getline(users_in, line)) {
        std::string current_uid;
        std::stringstream ss(line);
        std::getline(ss, current_uid, ',');
        if(current_uid != uid) users_lines.push_back(line);
        if(flag==2 && current_uid == uid) {
            users_lines.push_back(line);
        }
    }
    users_in.close();
    
    std::ofstream users_out("data/users.csv");
    for(const auto& l : users_lines) users_out << l << "\n";
    users_out.close();

   

    return flag;
}

bool Librarian::search_user(std::string uid) {
    std::ifstream file("data/users.csv");
    std::string line;
    //skip header
    std::getline(file, line);
    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string current_uid;
        std::getline(ss, current_uid, ',');
        if(current_uid==uid) {
            std::string current_upassword;
            std::getline(ss, current_upassword, ',');
            User current_user(current_uid, current_upassword);
            current_user.getAccount();
            current_user.account.display(uid);
            return true;
        }
    }
    return false;
}

// Book Management
#include <iostream>
#include <fstream>
#include <ctime>

bool Librarian::addbook(std::string bookID, std::string title, std::string author, std::string publisher,
                        int year, std::string ISBN, std::string status, std::time_t dueDate,std::string reserved) {
    std::ofstream file("data/books.csv", std::ios::app);
    
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open books file" << std::endl;
        return false;
    }

    // Writing to file
    file << bookID << "," << title << "," << author << "," << publisher << ","
         << year << "," << ISBN << "," << status << "," << dueDate << ',' << reserved << "\n";

    file.close();
    return true;
}


int Librarian::deletebook(std::string bookID) {
    std::vector<std::string> lines;
    std::ifstream in("data/books.csv");
    std::string line;
    int flag=0;
    // Skip header
    std::getline(in, line);
    lines.push_back(line);

    while(std::getline(in, line)) {
        std::stringstream ss(line);
        std::string current_bookID;
        std::string status;

        std::getline(ss, current_bookID, ',');
        
        if(current_bookID == bookID) {
            flag=1;
            std::string temp;
            for(int i=0;i<5;i++){
                std::getline(ss, temp, ',');
            }
            std::string status;
            std::getline(ss, status, ',');
            if(status == "Borrowed") {
                flag=2;
                lines.push_back(line);
            }
        }
        if(current_bookID != bookID) {
            lines.push_back(line);
        }
    }
    in.close();

    std::ofstream out("data/books.csv");
    for(const auto& l : lines) {
        out << l << "\n";
    }
    out.close();
    return flag;
}

bool Librarian::updatebook(std::string bookID, std::string reserved) {
    int flag=0;
    std::vector<std::string> lines;
    std::ifstream in("data/books.csv");
    std::string line;
    // std::time_t new_dueDate = std::time(0) + n_dueDate * 24 * 60 * 60;
    // if(n_dueDate == 0) new_dueDate = 0;
    // Read header
    std::getline(in, line);
    lines.push_back(line);

    while(std::getline(in, line)) {
        std::stringstream ss(line);
        std::string current_bookID;
        std::getline(ss, current_bookID, ',');
        if(current_bookID == bookID) {
            line=bookID+",";
            flag=1;
            std::string temp;
            for(int i=0;i<7;i++){
                std::getline(ss, temp, ',');
                line+=temp+",";
            }
            line+=reserved;
            lines.push_back(line);
        }
        else{
            lines.push_back(line);
        }
    }
    in.close();

    std::ofstream out("data/books.csv");
    for(const auto& l : lines) {
        out << l << "\n";
    }
    out.close();
    return flag;
}

bool Librarian::searchbook(std::string bookID, Book &book) {
    std::ifstream file("data/books.csv");
    std::string line;
    
    // Skip header
    std::getline(file, line);

    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string current_bookID;
        std::getline(ss, current_bookID, ',');
        if(current_bookID == bookID) {
            ss = std::stringstream(line);  // Reset stream
            book.loadFromCSV(ss);          // Load all fields
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
