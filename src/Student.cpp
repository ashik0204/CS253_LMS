
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
    std::cout<<"HERE"<<std::endl;
    getAccount();
    return account.returnBook(book,uid);
}
bool Student::reserveBook(Book &book) {
    getAccount();
    return account.reserveBook(book,uid);
}
void Student::payFine(float amount,std::string Uid) {
    getAccount();
    account.payFine(amount,Uid);
}
// std::vector<Book>& Student::getBorrowingHistory(){
//     getAccount();
//     return account.getBorrowingHistory();
// }
// std::vector<Book>& Student::getBorrowedBooks(){
//     getAccount();
//     return account.getBorrowedBooks();
// }
// std::vector<Book>& Student::getOverdueBooks(){
//     getAccount();
//     return account.getOverdueBooks();
// }



