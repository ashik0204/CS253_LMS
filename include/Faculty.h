#pragma once
#include "User.h"

class Faculty : public User{
    static const int MAX_BOOKS = 5;
    static const int MAX_DAYS = 30;
    private:
        Account account;
    public:
        //constructor
        Faculty(int uid, const std::string &uname, const std::string &upassword, bool isFaculty=1);
        
        //overridden methods
        //getters
        std::string getUid() const override;
        std::string getUpassword() const override;
        Account* getAccount(const std::string &inputuid, const std::string &inputpwd) const override;
        //setters
        void setUname(const std::string &uname) override;
        void setUpassword(const std::string &upassword) override;
        //faculty specific methods
        void canBorrow(bool isFaculty) const;
        void borrowBook( Book &book, bool isFaculty);
        void returnBook(Book &book, bool isFaculty);
};