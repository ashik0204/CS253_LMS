#pragma once
#include "User.h"
#include "Account.h"

class Student: public User{
    static const int MAX_BOOKS = 3;
    static const int MAX_DAYS = 15;
    
    public:
        //constructor
        
        Student(std::string uid, const std::string &upassword);
        //student specific methods

        int calculateFine( int overdueDays) ;
        bool canBorrow(bool isFaculty);
        bool borrowBook( Book &book);
        bool reserveBook(Book &book);
        bool returnBook(Book &book);
        void payFine(float amount,std::string Uid);
        // std::vector<Book>& getBorrowingHistory();
        // std::vector<Book>& getBorrowedBooks();
        // std::vector<Book>& getOverdueBooks();
};