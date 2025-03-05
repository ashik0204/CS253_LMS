#pragma once
#include <string>
#include <ctime>

class Book {
private:
    std::string title;
    std::string author;
    std::string publisher;
    int year;
    std::string ISBN;
    std::string status;
    std::time_t dueDate;

public:
    // Constructor with CSV-compatible parameters
    Book(std::string t = "", std::string a = "", std::string p = "", 
        int y = 0, std::string i = "", std::string s = "Available", 
        std::time_t d = 0);

    // Accessors
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getPublisher() const;
    int getYear() const;
    std::string getISBN() const;
    std::string getStatus() const;
    std::time_t getDueDate() const;
    void saveToCSV(std::ostream& os) const{};
    void loadFromCSV(std::istream& is){};
    // Mutators
    void setStatus(std::string s);
    void setDueDate(int days);
    
    // Status check
    bool isOverdue() const;
    
    // Display method
    void display() const;
    
    // CSV File operations
    void saveToFile(std::ofstream& file) const;
    void loadFromFile(std::ifstream& file);
};
