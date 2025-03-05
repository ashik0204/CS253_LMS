#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream>

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
void User::setUname(const std::string &uid_input) {
    uid = uid_input;
}

void User::setUpassword(const std::string &upassword_input) {
    upassword = upassword_input;
}
