#pragma once
#include "User.h"
#include "Book.h"
#include "Account.h"
#include "Student.h"
#include "Librarian.h"
#include "Faculty.h"
 
class Library {
public:
    Library();
    ~Library();
    bool authenticateUser(const std::string& uid, const std::string& upassword);
    void createUser(int uid, const std::string& upassword, bool isFaculty);
    void deleteUser(int uid);
    void updateUser(int uid, const std::string& upassword);
};
