#pragma once
#include "User.h"
#include "Book.h"
#include <string>
#include <ctime>
class Librarian : public User
{
public:
    //constructor
    Librarian(std::string uid, const std::string &upassword);
    //librarian specific methods
    bool create_user(std::string uid, std::string upassword,int role);
    bool delete_user(std::string uid);
    bool update_user(std::string old_uid,std::string new_uid, std::string new_upassword);
    bool search_user(std::string uid, User &user);
    bool addbook(std::string title, std::string author, std::string publisher, int year, std::string ISBN, std::string status, std::time_t dueDate);
    bool deletebook(std::string ISBN);
    bool updatebook(std::string ISBN, std::string status, int dueDate);
    bool searchbook(std::string ISBN, Book &book);

};