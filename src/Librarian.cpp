
#include "Librarian.h"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

// Constructor
bool checkifISBNexists(std::string ISBN){
    std::ifstream file("data/books.csv");
    if (!file.is_open()) return false;

    std::string line;
    
    // Skip header
    std::getline(file, line);

    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string title, author, publisher, year, currentISBN, status, dueDate;

        std::getline(ss, title, ',');
        std::getline(ss, author, ',');
        std::getline(ss, publisher, ',');
        std::getline(ss, year, ',');
        //5th field is the ISBN
        std::getline(ss, currentISBN, ',');

        if(currentISBN == ISBN) return true;
    }
    
    return false;
}

bool checkifUIDexists(std::string uid){
    std::ifstream file("data/users.csv");
    std::string line;
    //skip header
    std::getline(file, line);
    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string current_uid;
        std::getline(ss, current_uid, ',');
        if(current_uid==uid) return true;
    }
    return false;
}
Librarian::Librarian(std::string uid, const std::string &upassword) 
    : User(uid, upassword) {}

// User Management
bool Librarian::create_user(std::string uid, std::string upassword, int role) {
    // Add to users.csv

    std::ofstream users_file("data/users.csv", std::ios::app);
    if (checkifUIDexists(uid)) return false;
    users_file << uid << "," << upassword << "," << role << "\n";
    users_file.close();

    // Add to accounts.csv
    std::ofstream accounts_file("data/accounts.csv", std::ios::app);
    if (!accounts_file) return false;
    accounts_file << uid << "," 
                << std::boolalpha << (role != 2) << "," // isFaculty
                << "0.0,,,\n"; // fines, borrowed, overdue, history
    accounts_file.close();
    
    return true;
}


int Librarian::delete_user(std::string uid) {
    
    int flag=0;
    std::string line;
    // Delete from accounts.csv
    std::vector<std::string> accounts_lines;
    std::ifstream accounts_in("data/accounts.csv");
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
            if(borrowed!=""||overdue!="") flag=2;
            accounts_lines.push_back(line);
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

// bool Librarian::update_user(std::string old_uid, std::string new_uid, std::string new_password) {
//     // Update users.csv
//     std::string line;
//     std::vector<std::string> users_lines;
//     bool found = false;
//     std::ifstream users_in("data/users.csv");
    
//     while(std::getline(users_in, line)) {
//         std::stringstream ss(line);
//         std::string current_uid, password, role;
//         std::getline(ss, current_uid, ',');
//         std::getline(ss, password, ',');
//         std::getline(ss, role, ',');

//         if(current_uid == old_uid) {
//             line = new_uid + "," + new_password + "," + role;
//             found = true;
//         }
//         users_lines.push_back(line);
//     }
//     users_in.close();

//     if(found) {
//         std::ofstream users_out("data/users.csv");
//         for(const auto& l : users_lines) users_out << l << "\n";
//         users_out.close();
//     }

//     // Update accounts.csv
//     std::vector<std::string> accounts_lines;
//     std::ifstream accounts_in("data/accounts.csv");
    
//     while(std::getline(accounts_in, line)) {
//         std::stringstream ss(line);
//         std::string current_uid, rest;
//         std::getline(ss, current_uid, ',');
//         std::getline(ss, rest);
        
//         if(current_uid == old_uid) {
//             line = new_uid + "," + rest;
//         } 
//         accounts_lines.push_back(line);
//     }
//     accounts_in.close();

//     if(found) {
//         std::ofstream accounts_out("data/accounts.csv");
//         for(const auto& l : accounts_lines) accounts_out << l << "\n";
//         accounts_out.close();
//     }

//     return found;
// }

bool Librarian::search_user(std::string uid, User &user) {
    std::ifstream file("data/users.csv");
    std::string line;
    //skip header
    std::getline(file, line);
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string current_uid, password, role;
        std::getline(ss, current_uid, ',');
        std::getline(ss, password, ',');
        std::getline(ss, role, ',');

        if(current_uid == uid) {
            user.setUid(current_uid);
            user.setUpassword(password);
            return true;
        }
    }
    return false;
}

// Book Management
bool Librarian::addbook(std::string title, std::string author, std::string publisher,
                      int year, std::string ISBN, std::string status, std::time_t dueDate) {
    std::ofstream file("data/books.csv", std::ios::app);
    //ISBN has to be unique
    if(checkifISBNexists(ISBN)) return false;

    file << title << "," << author << "," << publisher << ","
         << year << "," << ISBN << "," << status << "," << dueDate << "\n";
    file.close();
    return true;
}

int Librarian::deletebook(std::string ISBN) {
    std::vector<std::string> lines;
    std::ifstream in("data/books.csv");
    std::string line;
    int flag=0;
    // Skip header
    std::getline(in, line);
    lines.push_back(line);

    while(std::getline(in, line)) {
        std::stringstream ss(line);
        std::string current_ISBN;
        for(int i = 0; i < 4; i++) ss.ignore(1000, ',');
        std::getline(ss, current_ISBN, ',');
        if(current_ISBN == ISBN) {
            flag=1;
            std::string status;
            std::getline(ss, status, ',');
            if(status == "Borrowed") {
                flag=2;
                lines.push_back(line);
            }
        }
        if(current_ISBN != ISBN) {
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

bool Librarian::updatebook(std::string ISBN, std::string new_status) {
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
        std::string parts[7];
        for(int i = 0; i < 7; i++) {
            std::getline(ss, parts[i], ',');
        }
        if(parts[4] == ISBN) {
            flag=1;
            parts[5] = (parts[5]=="Borrowed")? parts[5]:new_status;
            parts[6] = (parts[5]=="Borrowed")? parts[6]:"0";
            line = parts[0] + "," + parts[1] + "," + parts[2] + "," 
                 + parts[3] + "," + parts[4] + "," + parts[5] + "," + parts[6];
        }
        lines.push_back(line);
    }
    in.close();

    std::ofstream out("data/books.csv");
    for(const auto& l : lines) {
        out << l << "\n";
    }
    out.close();
    return flag;
}

bool Librarian::searchbook(std::string ISBN, Book &book) {
    std::ifstream file("data/books.csv");
    std::string line;
    
    // Skip header
    std::getline(file, line);

    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string current_ISBN;
        std::string temp;
        for(int i = 0; i < 4; i++) std::getline(ss, temp, ',');
        std::getline(ss, current_ISBN, ',');
        
        if(current_ISBN == ISBN) {
            ss = std::stringstream(line);  // Reset stream
            book.loadFromCSV(ss);          // Load all fields
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
