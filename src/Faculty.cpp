
#include "Book.h"
#include "Account.h"
#include "Faculty.h"
#include <string>


//constructor
Faculty::Faculty(std::string uid, const std::string &upassword) : User(uid, upassword) {}
//Faculty specific methods
bool Faculty::canBorrow(bool isFaculty) {
    getAccount();
    return account.canBorrow();
}
bool Faculty::borrowBook( Book &book) {
    getAccount();
    return account.borrowBook(book,uid);
}
bool Faculty::returnBook(Book &book) {
    getAccount();
    return account.returnBook(book,uid);
}
bool Faculty::reserveBook(Book &book) {
    getAccount();
    return account.reserveBook(book,uid);
}




