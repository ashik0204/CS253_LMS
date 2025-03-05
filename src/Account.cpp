#include "Account.h"
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>


// Constructor
Account::Account(bool faculty) : isFaculty(faculty), fines(0.0f) {}

// Core functionality implementation
bool Account::borrowBook(Book& book) {
    if (canBorrow() && book.getStatus() == "Available") {
        book.setStatus("Borrowed");
        book.setDueDate(time(0) + (isFaculty ? 30 : 15) * 86400);
        borrowedBooks.push_back(book);
        
        // Update CSV
        updateBookInCSV(book);
        return true;
    }
    return false;
}

bool Account::returnBook(Book& book) {
    auto it = std::find_if(borrowedBooks.begin(), borrowedBooks.end(),
        [&book](const Book& b) { return b.getISBN() == book.getISBN(); });

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
            overdueBooks.emplace_back(*it, overdueDays);
        }

        borrowedBooks.erase(it);
        
        // Update CSV
        updateBookInCSV(book);
        return true;
    }
    return false;
}
bool Account::reserveBook(Book& book) {
    if (book.getStatus() == "Available") {
        book.setStatus("Reserved");
        updateBookInCSV(book);
        return true;
    }
    return false;
}
int Account::calculateFine(int overdueDays) const {
    return overdueDays * 10;
}
bool Account::payFine(float amount) {
    if (isFaculty) return false;
    fines = std::max(0.0f, fines - amount);
    return true;
}

bool Account::canBorrow() const {
    if (isFaculty) {
        bool hasSevereOverdue = std::any_of(overdueBooks.begin(), overdueBooks.end(),
            [](const auto& entry) { return entry.second > 60; });
        return borrowedBooks.size() < 5 && !hasSevereOverdue;
    }
    return borrowedBooks.size() < 3 && fines == 0;
}

// CSV helper implementations
std::string Account::booksToCSV(const std::vector<Book>& books) const {
    std::stringstream ss;
    for (size_t i = 0; i < books.size(); ++i) {
        if (i > 0) ss << "|";
        books[i].saveToCSV(ss);
    }
    return ss.str();
}

void Account::csvToBooks(const std::string& csv, std::vector<Book>& target) {
    std::stringstream ss(csv);
    std::string entry;
    while (std::getline(ss, entry, '|')) {
        if (!entry.empty()) {
            std::stringstream bookStream(entry);
            Book b;
            b.loadFromCSV(bookStream);
            target.push_back(b);
        }
    }
}
void Account::updateBookInCSV(const Book& book) {
    // Read all books from file
    std::vector<Book> books;
    std::ifstream in("books.csv");
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
    bool found = false;
    for(auto& b : books) {
        if(b.getISBN() == book.getISBN()) {
            b = book;
            found = true;
            break;
        }
    }

    // Write back to file
    std::ofstream out("books.csv");
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
         << [this](){
             std::stringstream ss;
             for (size_t i = 0; i < overdueBooks.size(); ++i) {
                 if (i > 0) ss << "|";
                 overdueBooks[i].first.saveToCSV(ss);
                 ss << ":" << overdueBooks[i].second;
             }
             return ss.str();
         }() << ','
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
            std::stringstream overdueSS(field);
            std::string entry;
            while (std::getline(overdueSS, entry, '|')) {
                if (!entry.empty()) {
                    size_t colonPos = entry.find(':');
                    Book b;
                    std::stringstream bookSS(entry.substr(0, colonPos));
                    b.loadFromCSV(bookSS);
                    int days = std::stoi(entry.substr(colonPos+1));
                    overdueBooks.emplace_back(b, days);
                }
            }

            // Load borrowing history
            std::getline(ss, field);
            csvToBooks(field, borrowingHistory);

            return true; // Successfully loaded
        }
    }
    
    return false; // UID not found
}


// Getter implementations
float Account::getFines() const { return fines; }
const std::vector<Book>& Account::getBorrowedBooks() const { return borrowedBooks; }
const std::vector<std::pair<Book, int>>& Account::getOverdueBooks() const { return overdueBooks; }
const std::vector<Book>& Account::getBorrowingHistory() const { return borrowingHistory; }
