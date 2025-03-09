
#include "Account.h"
#include "Library.h"    
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <ctime>
//constructor
Account::Account(bool faculty) : isFaculty(faculty), fines(0.0f) {}

// Core functionality implementation
bool Account::borrowBook(Book& book,std::string Uid) {
    // std::cout<<canBorrow()<<" "<<book.getStatus()<<std::endl;
    if (canBorrow() && (book.getStatus() == "available"||book.getStatus() == "Available")) {
        book.setStatus("Borrowed");
        book.setDueDate((isFaculty ? 30 : 15) );
        borrowedBooks.push_back(book);
        
        // Update CSV
        updateAccount(Uid);
        updateBookInCSV(book);
        return true;
    }
    return false;
}

bool Account::returnBook(Book& book,std::string Uid) {

    auto it = std::find_if(borrowedBooks.begin(), borrowedBooks.end(),
        [&book](const Book& b) { return b.getISBN() == book.getISBN(); });
        // std::cout<<"HERE"<<std::endl;
    if (it != borrowedBooks.end()) {
        // Calculate overdue days
        int overdueDays = static_cast<int>((time(0) - it->getDueDate()) / 86400);
        overdueDays = std::max(0, overdueDays);

        // Update fines for students
        if (!isFaculty && overdueDays > 0) {
            fines += overdueDays * 10;
        }

        // Update book status and history
        book.setStatus("Available");
        book.setDueDate(0); // Reset due date
        borrowingHistory.push_back(*it);
        
        // Record overdue books
        if (overdueDays > 0) {
            overdueBooks.push_back(*it);
        }
        // std::cout<<it->getISBN()<<std::endl;
        // std::cout<<borrowedBooks.size()<<std::endl;
        borrowedBooks.erase(it);
        // std::cout<<borrowedBooks.size()<<std::endl;
        // std::cout<<"HERE"<<std::endl;
        updateAccount(Uid);
        // Update CSV
        // std::cout<<"HERE"<<std::endl;
        updateBookInCSV(book);
        return true;
    }
    return false;
}
bool Account::reserveBook(Book& book,std::string Uid) {
    
    if (canBorrow()&&(book.getStatus() == "available"||book.getStatus() == "Available")) {
        book.setStatus("Reserved");
        updateAccount(Uid);
        updateBookInCSV(book);
        return true;
    }
    return false;
}
int Account::calculateFine(int overdueDays) const {
    return overdueDays * 10;
}

bool Account::payFine(float amount,std::string Uid) {
    if (this->isFaculty) return false;
    fines = std::max(0.0f,this->fines - amount);
    if(updateAccount(Uid)){
        return true;
    }
    return false;
}

bool Account::canBorrow() const {
    if (isFaculty) {
        bool hasSevereOverdue = std::any_of(borrowedBooks.begin(), borrowedBooks.end(),
            [](const Book& entry) { return static_cast<int>((time(0) - entry.getDueDate()) / 86400) > 60; });
        return borrowedBooks.size() < 5 && !hasSevereOverdue;
    }
    return borrowedBooks.size() < 3 && fines == 0;
}

// CSV helper implementations
std::string Account::booksToCSV(const std::vector<Book>& books) const {
    std::string book_ISBN="";
    for (size_t i = 0; i < books.size(); ++i) {
        if(i!=0) book_ISBN+="|";
        book_ISBN+=books[i].getISBN();
    }
    return book_ISBN;
}

void Account::csvToBooks(const std::string& csv, std::vector<Book>& target) {
    target.clear();
    std::stringstream ss(csv);
    std::string entry;
    Library l1;
    while (std::getline(ss, entry, '|')) {
        
        Book b;
        
        if(entry!=""){if(l1.searchBook(entry, b)) {
            
            target.push_back(b);
        }}
    }
}
void Account::updateBookInCSV(const Book& book) {
    // Read all books from file
    std::vector<Book> books;
    std::ifstream in("data/books.csv");
    std::string header;
    std::getline(in, header); // Skip header
    
    std::string line;
    while(std::getline(in, line)) {
        Book b;
        std::stringstream ss(line);
        b.loadFromCSV(ss);
        books.push_back(b);
    }
    in.close();

    // Find and update the book
    for(auto& b : books) {
        if(b.getISBN() == book.getISBN()) {
            b = book;
            break;
        }
    }

    // Write back to file
    std::ofstream out("data/books.csv");
    out << "title,author,publisher,year,ISBN,status,dueDate\n";
    for(const auto& b : books) {
        b.saveToCSV(out);
    }
    out.close();
}
// File operations
void Account::saveToFile(std::ofstream& file,const std::string &uid) const {
    file << uid << ","
         << std::boolalpha << isFaculty << ','
         << fines << ','
         << booksToCSV(borrowedBooks) << ','
         << booksToCSV(overdueBooks) << ','
         << booksToCSV(borrowingHistory) << '\n';
}

bool Account::loadFromFile( std::ifstream &file, const std::string &targetuid) {

    std::string line;
    
    // Skip header
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string current_uid;
        std::getline(ss, current_uid, ',');
        
        if (current_uid == targetuid) {
            // Process the matching record
            std::string field;
            // Read isFaculty
            std::getline(ss, field, ',');
            isFaculty = (field == "true");
            
            // Read fines
            std::getline(ss, field, ',');
            fines = std::stof(field);
     
            // Load borrowed books
            std::getline(ss, field, ',');

            csvToBooks(field, borrowedBooks);
           
            // Load overdue books
            std::getline(ss, field, ',');
            csvToBooks(field, overdueBooks);

            // Load borrowing history
            std::getline(ss, field);
            csvToBooks(field, borrowingHistory);

            return true; // Successfully loaded
        }
    }
    
    return false; // UID not found
}

bool Account::updateAccount(const std::string& Uid) {
    std::ifstream ifile("data/accounts.csv");
    if (!ifile.is_open()) return false;

    std::vector<std::string> lines;
    std::string line;
    
    while (std::getline(ifile, line)) {
        std::stringstream ss(line);
        std::string current_uid;
        std::getline(ss, current_uid, ',');
        
        if (current_uid == Uid) {
            line = Uid + "," +
                   (isFaculty ? "true" : "false") + "," +
                   std::to_string(fines) + "," +
                   booksToCSV(borrowedBooks) + "," +
                   booksToCSV(overdueBooks) + "," +
                   booksToCSV(borrowingHistory);
        }

        lines.push_back(line);
    }
    ifile.close();

    
    std::ofstream ofile("data/accounts.csv", std::ios::trunc);  
    if (!ofile.is_open()) return false;

    for (const auto& l : lines) {
        ofile << l << "\n";
    }
    ofile.close();

    return true;
}

// Getter implementations
float Account::getFines() const { return fines; }
const std::vector<Book>& Account::getBorrowedBooks() const { return borrowedBooks; }
const std::vector<Book>& Account::getOverdueBooks() const { return overdueBooks; }
const std::vector<Book>& Account::getBorrowingHistory() const { return borrowingHistory; }
void Account::display(std::string uid) const {
    std::cout << "\n--------ACCOUNT INFORMATION--------\n"
              << "UID: " << uid << "\n"
              << "isFaculty: " << (isFaculty ? "true" : "false") << "\n"
              << "Fines: " << fines << "\n"
              << "Borrowed books: " << borrowedBooks.size() << "\n"
              << "Overdue books: " << overdueBooks.size() << "\n"
              << "Borrowing history: " << borrowingHistory.size() << std::endl;
    std::cout<<"Do you want to display borrowed books? (y/n): ";
    std::string choice;
    std::cin>>choice;
    
    if (choice == "y") {
        std::cout << "\n--------BORROWED BOOKS--------\n";
        for (const auto& book : borrowedBooks) {
            book.display();
        }
    }

    std::cout<<"Do you want to display overdue books? (y/n): ";
    std::cin>>choice;
    
    if (choice == "y") {
        std::cout << "\n--------OVERDUE BOOKS--------\n";
        for (const auto& book : overdueBooks) {
            book.display();
        }
    }
    std::cout<<"Do you want to display borrowing history? (y/n): ";
    std::cin>>choice;
    
    if (choice == "y") {
        std::cout << "\n--------BORROWING HISTORY--------\n";
        for (const auto& book : borrowingHistory) {
            book.display();
        }
    }
    

}
