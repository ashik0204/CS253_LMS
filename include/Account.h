#pragma once
#include "Book.h"
#include <vector>
#include <string>
#include <fstream>
#include <utility> // For std::pair

class Account {
private:
    std::vector<Book> borrowedBooks;
    std::vector<Book> overdueBooks; // Book + Days Overdue
    std::vector<Book> borrowingHistory;
    float fines;
    bool isFaculty;

    // CSV helpers
    bool searchBookInCSV(const std::string& ISBN, Book& target);
    std::string booksToCSV(const std::vector<Book>& books) const;
    void csvToBooks(const std::string& csv, std::vector<Book>& target);
    void updateBookInCSV(const Book& book);

public:
    explicit Account(bool faculty = false);
    
    // Core functionality
    int calculateFine(int overdueDays) const;
    bool borrowBook(Book& book, std::string Uid);
    bool returnBook(Book& book, std::string Uid);
    bool reserveBook(Book& book, std::string Uid);
    bool payFine(float amount,std::string Uid);
    bool canBorrow() const;

    // File operations
    void saveToFile(std::ofstream& file, const std::string& uid) const;
    bool loadFromFile(std::ifstream& file, const std::string& targetUid);
    bool updateAccount(const std::string& Uid);
    // Getters
    float getFines() const;
    const std::vector<Book>& getBorrowedBooks() const;
    const std::vector<Book>& getOverdueBooks() const;
    const std::vector<Book>& getBorrowingHistory() const;
};
