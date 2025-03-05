
#include "Book.h"
#include "Account.h"
#include "Student.h"
#include <string>

//constructor
Student::Student(std::string uid, const std::string &upassword) : User(uid, upassword) {}
//student specific methods
int Student::calculateFine( int overdueDays) {
    Account acc = getAccount();
    return acc.calculateFine(overdueDays);
}
bool Student::canBorrow(bool isFaculty) {
    Account acc = getAccount();
    return acc.canBorrow();
}
bool Student::borrowBook( Book &book) {
    Account acc = getAccount();
    return acc.borrowBook(book);
}
bool Student::returnBook(Book &book) {
    Account acc = getAccount();
    acc.returnBook(book);
}
bool Student::reserveBook(Book &book) {
    Account acc = getAccount();
    return acc.reserveBook(book);
}
void Student::payFine(float amount) {
    Account acc = getAccount();
    acc.payFine(amount);
}




