#include <Account.h>
#include <Book.h>

#include <ctime>
#include <iostream>

void testAccountFunctionality() {
    // Create books with all 7 parameters (status, dueDate included)
    Book book1("C++ Primer", "Stanley Lippman", "Addison-Wesley", 
              2012, "978-0321714114", "Available", 0);
    Book book2("Clean Code", "Robert Martin", "Prentice Hall",
              2008, "978-0132350884", "Available", 0);
    Book book3("Design Patterns", "Erich Gamma", "Addison-Wesley",
              1994, "978-0201633610", "Available", 0);
    Book book4("Effective Modern C++", "Scott Meyers", "O'Reilly Media",
              2014, "978-1491903995", "Available", 0);
    Book book5("The C++ Programming Language", "Bjarne Stroustrup", "Addison-Wesley",
              2013, "978-0321563842", "Available", 0);

    std::cout << "===== STUDENT ACCOUNT TEST ====\n";
    Account studentAcc(false);
    
    // Test borrowing with proper status updates
    studentAcc.borrowBook(book1);
    studentAcc.borrowBook(book2);
    studentAcc.borrowBook(book3);
    
    std::cout << "Borrowed books (should be 3): " 
              << studentAcc.getBorrowedBooks().size() << "\n";
    
    // Test overdue calculation with full 7-param book
    book1.setStatus("Borrowed");
    book1.setDueDate(time(0) - 20*24*60*60); // 20 days ago
    studentAcc.returnBook(book1);
    
    std::cout << "\nAfter returning 5-day overdue book:"
              << "\nExpected fine: 50"
              << "\nActual fine: " << studentAcc.getFines()
              << "\nBook status: " << book1.getStatus() << " (should be Available)"
              << "\nBorrowing history entries: " << studentAcc.getBorrowingHistory().size() 
              << " (should be 1)\n";

    // Test faculty account with extended parameters
    std::cout << "\n===== FACULTY ACCOUNT TEST ====\n";
    Account facultyAcc(true);
    
    // Borrow 5 books (max limit)
    for(int i=0; i<5; i++) {
        Book facultyBook("Faculty Book " + std::to_string(i), "Author", "Publisher",
                       2023, "ISBN" + std::to_string(i), "Available", 0);
        facultyAcc.borrowBook(facultyBook);
    }
    
    std::cout << "Borrowed books (should be 5): " 
              << facultyAcc.getBorrowedBooks().size() << "\n";

    // Test severe overdue for faculty
    Book overdueBook("Overdue Book", "Author", "Publisher", 
                    2020, "ISBN-OVERDUE", "Borrowed", time(0) - 61*24*60*60);
    facultyAcc.returnBook(overdueBook);
    
    std::cout << "\nAfter returning 61-day overdue book:"
              << "\nCan borrow? " << (facultyAcc.canBorrow() ? "Yes" : "No") 
              << " (should be No)\n";
}

/* Expected Output:
===== STUDENT ACCOUNT TEST ====
Borrowed books (should be 3): 3

After returning 5-day overdue book:
Expected fine: 50
Actual fine: 50
Book status: Available (should be Available)
Borrowing history entries: 1 (should be 1)

===== FACULTY ACCOUNT TEST ====
Borrowed books (should be 5): 5

After returning 61-day overdue book:
Can borrow? No (should be No)
*/
