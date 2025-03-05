#pragma once
#include "Account.h"
#include <string>

 class User{
    protected:
        //data members
        std::string uid;
        std::string upassword;
        Account account;
    public:
        //constructor
        User(const std::string &uid, const std::string &upassword);

        //pure virtual functions
        std::string getUid() const;
        std::string getUpassword() const;
        Account getAccount();
        void setUname(const std::string &uname);
        void setUpassword(const std::string &upassword);
 };