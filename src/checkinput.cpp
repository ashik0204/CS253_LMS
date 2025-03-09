#include "checkinput.h"
#include <string>
#include <cctype>
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
    return status == "Available" || status == "Reserved" || status == "Borrowed";
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
 
