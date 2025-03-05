#pragma once
#include "Book.h"
#include <vector>
#include <string>
#include <fstream>
#include <utility> // For std::pair

class Account {
private:
    std::vector<Book> borrowedBooks;
    std::vector<std::pair<Book, int>> overdueBooks; // Book + Days Overdue
    std::vector<Book> borrowingHistory;
    float fines;
    bool isFaculty;

    // CSV helpers
    std::string booksToCSV(const std::vector<Book>& books) const;
    void csvToBooks(const std::string& csv, std::vector<Book>& target);
    void updateBookInCSV(const Book& book) {}

public:
    explicit Account(bool faculty = false);
    
    // Core functionality
    int calculateFine(int overdueDays) const;
    bool borrowBook(Book& book);
    bool returnBook(Book& book);
    bool reserveBook(Book& book);
    bool payFine(float amount);
    bool canBorrow() const;

    // File operations
    void saveToFile(std::ofstream& file, const std::string& uid) const;
    bool loadFromFile(std::ifstream& file, const std::string& targetUid);

    // Getters
    float getFines() const;
    const std::vector<Book>& getBorrowedBooks() const;
    const std::vector<std::pair<Book, int>>& getOverdueBooks() const;
    const std::vector<Book>& getBorrowingHistory() const;
};
