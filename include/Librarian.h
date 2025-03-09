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
    int delete_user(std::string uid);
    // bool update_user(std::string old_uid,std::string new_uid, std::string new_upassword);
    bool search_user(std::string uid);
    bool addbook(std::string bookID,std::string title, std::string author, std::string publisher, int year, std::string ISBN, std::string status, std::time_t dueDate,std::string reserved);
    int deletebook(std::string bookID);
    bool updatebook(std::string bookID, std::string reserved);
    bool searchbook(std::string bookID, Book &book);

};