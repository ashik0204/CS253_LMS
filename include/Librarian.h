#pragma once
#include "User.h"

class Librarian : public User
{
public:
    //constructor
    Librarian(int uid, const std::string &uname, const std::string &upassword);
    //librarian specific methods
    void create_user(int uid, std::string uname, std::string upassword,bool type);
    void delete_user(int uid);
    void update_user(int uid, std::string uname, std::string upassword);
    void search_user(int uid);
    void addbook(std::string title, std::string author, std::string publisher, int year, std::string ISBN, std::string status, std::time_t dueDate);
    void deletebook(std::string ISBN);
    void updatebook(std::string ISBN, std::string status, std::time_t dueDate);
    void searchbook(std::string ISBN);
    //overridden methods
    

    //overridden methods
    void saveToFile(std::ofstream& file) const;
    void loadFromFile(std::ifstream& file);

};