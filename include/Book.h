#pragma once
#include <string>
#include <ctime>
#include <fstream>

class Book {
private:
    std::string bookID;
    std::string title;
    std::string author;
    std::string publisher;
    int year;
    std::string ISBN;
    std::string status;
    std::time_t dueDate;
    std::string reserved;

public:
    // Constructor with CSV-compatible parameters
    Book(std::string bID = "", std::string t = "", std::string a = "", std::string p = "", 
         int y = 0, std::string i = "", std::string s = "available", 
         std::time_t d = 0);

    // Accessors
    std::string getBookID() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getPublisher() const;
    int getYear() const;
    std::string getISBN() const;
    std::string getStatus() const;
    std::time_t getDueDate() const;
    std::string getReserved() const;
    
    // CSV File operations
    void saveToCSV(std::ostream& os) const;
    void loadFromCSV(std::istream& is); // Changed to std::istream&
    
    // Mutators
    void setStatus(std::string s);
    void setDueDate(int days);
    void setReserved(std::string r);
    
    // Status check
    bool isOverdue() const;
    
    // Display method
    void display() const;
};