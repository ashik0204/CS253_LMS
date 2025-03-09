#include "checkinput.h"
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>
#include <algorithm>
int count_ISBN_digits(const std::string &ISBN) {
    int counter_var=0;
    for(int i=0;i<ISBN.length();i++) {
        if(std::isdigit(ISBN[i])) counter_var++;
    }
    return counter_var;
}
checkinput::checkinput() {};
checkinput::~checkinput() {};
bool checkinput::days_to_int_convertible(const std::string &days, int &daysInt) { 
    try {
        size_t pos;
        daysInt = std::stoi(days, &pos);
        return pos == days.length();
    } catch (...) {
        return false;
    }
 }
 bool checkinput::status_check(const std::string &status) {
    return status == "Available" || status == "Borrowed";
 }
 bool checkinput::ISBN_check(const std::string &ISBN) {
    return count_ISBN_digits(ISBN) == 13 && std::all_of(ISBN.begin(), ISBN.end(), [](char c) { return std::isdigit(c)||(c=='-'); });
 }
 
 void checkinput::ISBN_standardize(std::string &ISBN) {
     std::string temp;
     for (char ch : ISBN) {
         if (std::isdigit(ch)) {
             temp += ch;
         }
     }
     if (temp.length() > 3) {
         temp.insert(3, "-");
     }

     ISBN = temp;
 }

 bool checkinput::checkifbookIDexists(const std::string& bookID){
    std::ifstream file("data/books.csv");
    if (!file.is_open()) return false;

    std::string line;
    
    // Skip header
    std::getline(file, line);

    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string current_bookID;
        std::getline(ss, current_bookID, ',');

        if(current_bookID == bookID) return true;
    }
    
    return false;
}
bool checkinput::checkifUIDexists(const std::string &uid){
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