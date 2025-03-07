#pragma once
#include "User.h"

class Faculty : public User{
    static const int MAX_BOOKS = 5;
    static const int MAX_DAYS = 30;
    public:
        //constructor
        Faculty(std::string uid, const std::string &upassword);
        //faculty specific methods
        bool canBorrow(bool isFaculty);
        bool borrowBook( Book &book);
        bool returnBook(Book &book);
        bool reserveBook(Book &book);

};