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
    dueDate = std::time(0) + days * 24 * 60 * 60; 
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
       << dueDate;
}

void Book::loadFromCSV(std::istream& is) {
    std::string line;
    std::getline(is, line);
    std::stringstream ss(line);
    
    std::getline(ss, title, ',');
    std::getline(ss, author, ',');
    std::getline(ss, publisher, ',');
    
    std::string temp;
    std::getline(ss, temp, ',');
    year = std::stoi(temp);
    
    std::getline(ss, ISBN, ',');
    std::getline(ss, status, ',');
    
    std::getline(ss, temp);
    dueDate = std::stol(temp);
}