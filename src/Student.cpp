
#include "Book.h"
#include "Account.h"
#include "Student.h"
#include <iostream>
#include <string>


//constructor
Student::Student(std::string uid, const std::string &upassword) : User(uid, upassword) {}
//student specific methods
int Student::calculateFine( int overdueDays) {
    getAccount();
    return account.calculateFine(overdueDays);
}
bool Student::canBorrow(bool isFaculty) {
    getAccount();
    return account.canBorrow();
}
bool Student::borrowBook( Book &book) {
    getAccount();
    return account.borrowBook(book,uid);
}
bool Student::returnBook(Book &book) {
    getAccount();
    return account.returnBook(book,uid);
}
bool Student::reserveBook(Book &book) {
    getAccount();
    return account.reserveBook(book,uid);
}
bool Student::payFine(float amount,std::string Uid) {
    getAccount();
    return account.payFine(amount,Uid);
}




