
#include "Book.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>

// Constructor
Book::Book(std::string t, std::string a, std::string p, 
         int y, std::string i, std::string s, std::time_t d)
    : title(t), author(a), publisher(p), year(y), 
      ISBN(i), status(s), dueDate(d) {}

// Accessors
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
std::string Book::getPublisher() const { return publisher; }
int Book::getYear() const { return year; }
std::string Book::getISBN() const { return ISBN; }
std::string Book::getStatus() const { return status; }
std::time_t Book::getDueDate() const { return dueDate; }

// Mutators
void Book::setStatus(std::string s) { status = s; }
void Book::setDueDate(int days) { 
    if(days == 0) {
        dueDate = 0;
    } else {
        dueDate = std::time(0) + days * 24 * 60 * 60; 
    }
}

bool Book::isOverdue() const { 
    return std::time(0) > dueDate; 
}

void Book::display() const {
    std::cout << "\n--------BOOK INFORMATION--------\n"
              << "Title: " << title << "\n"
              << "Author: " << author << "\n"
              << "Publisher: " << publisher << "\n"
              << "Year: " << year << "\n"
              << "ISBN: " << ISBN << "\n"
              << "Status: " << status << "\n";
}

//CSV File operations

void Book::saveToCSV(std::ostream& os) const {
    os << title << "," << author << "," << publisher << ","
       << year << "," << ISBN << "," << status << ","
       << dueDate<<"\n";
}

void Book::loadFromCSV(std::istream& is) {
    std::string temp;
    
    std::getline(is, title, ',');
    std::getline(is, author, ',');
    std::getline(is, publisher, ',');
    
    std::getline(is, temp, ',');
    year = std::stoi(temp);
    
    std::getline(is, ISBN, ',');
    std::getline(is, status, ',');

    if (std::getline(is, temp)) {
        dueDate = std::stol(temp);
    } else {
        dueDate = 0; // Default value if missing
    }
}
