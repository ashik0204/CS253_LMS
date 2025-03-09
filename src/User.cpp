
#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

User::User(const std::string &uid, const std::string &upassword) : uid(uid), upassword(upassword) {}
//getters
std::string User::getUid() const {
    return uid;
}

std::string User::getUpassword() const {
    return upassword;
}
 
Account User::getAccount() {
    std::ifstream file("data/accounts.csv");
  
    account.loadFromFile(file,uid);

    return account;
}
//setters
bool User::setUid(const std::string &uid_input) {
    
    std::ifstream ifile("data/users.csv");
    std::string line;
    std::vector<std::string> lines;
    while(std::getline(ifile, line)) {
        std::stringstream ss(line);
        std::string current_uid, password, role;
        std::getline(ss, current_uid, ',');
        std::getline(ss, password, ',');
        std::getline(ss, role, ',');
        if(current_uid != uid) {
            if(current_uid == uid_input) {
                std::cout<<"User already exists"<<std::endl;
                return false;
            }
        }
        if(current_uid == uid) {
            line = uid_input + "," + upassword + "," + role;
        }
        lines.push_back(line);
    }
    ifile.close();
    std::ofstream ofile("data/users.csv");
    for(const auto& l : lines) {
        ofile << l << "\n";
    }
    ofile.close();
    
    std::ifstream ifile1("data/accounts.csv");
    std::vector<std::string>lines1;
    std::string line1;
    while(std::getline(ifile1, line1)) {
        std::stringstream ss(line1);
        std::string current_uid, rest;
        std::getline(ss, current_uid, ',');
        std::getline(ss, rest);
        if(current_uid == uid) {
            line1 = uid_input + "," + rest;
        }
        lines1.push_back(line1);
    }
    ifile1.close();
    std::ofstream ofile1("data/accounts.csv");
    for(const auto& l : lines1) {
        ofile1 << l << "\n";
    }
    ofile1.close();
    uid =uid_input;
    return true;
}


void User::setUpassword(const std::string &upassword_input) {
    std::ifstream ifile("data/users.csv");
    std::string line;
    std::vector<std::string> lines;
    while(std::getline(ifile, line)) {
        std::stringstream ss(line);
        std::string current_uid, password, role;
        std::getline(ss, current_uid, ',');
        std::getline(ss, password, ',');
        std::getline(ss, role, ',');
        if(current_uid == uid) {
            line = uid + "," + upassword_input + "," + role;
        }
        lines.push_back(line);
    }
    ifile.close();
    std::ofstream ofile("data/users.csv");
    for(const auto& l : lines) {
        ofile << l << "\n";
    }
    ofile.close();
    upassword = upassword_input;
}
