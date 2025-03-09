
#include "Library.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

int main(){
    cout<<"Welcome to Library Management System\n"<<"press 1 to login \n"<<"press 0 to exit"<<endl;
    bool login;
    cin>>login;
    if(!login){
        return 0;
    }
    else{
        cout<<"Please enter user id"<<endl;
        string uid;
        cin>>uid;
        cout<<"Please enter password"<<endl;
        string upassword;
        cin>>upassword;
        int role;
        //Entering Library logic
        Library l1;
        while(!l1.authenticateUser(uid,upassword,role)){
            cout<<"Do you want to exit: (press 0) or login again: (press 1)"<<endl;
            int choice;
            cin>>choice;
            if(choice==0){
                return 0;
            }
            cout<<"Please enter user id"<<endl;
            cin>>uid;
            cout<<"Please enter password"<<endl;
            cin>>upassword;
        }
        switch(role){
            case 1: {
                cout << "Welcome Librarian" << endl;
                //Entering Librarian logic
                Librarian librarian(uid, upassword); 
                int main_menu = 1;
                while(main_menu) {
                    cout << "\n--------LIBRARIAN MENU--------\n"
                         << "1. User Management\n"
                         << "2. Book Management\n"
                         << "0. Exit\n"
                         << "Choice: ";
                    cin >> main_menu;
                    checkinput checkinput_obj;
                    if(main_menu == 1) {  // User Management
                        int user_menu = 1;
                        while(user_menu) {
                            cout << "\n--------USER MANAGEMENT--------\n"
                                 << "1. Add User\n"
                                 << "2. Delete User\n"
                                 << "3. Search User\n"
                                 << "0. Back\n"
                                 << "Choice: ";
                            cin >> user_menu;

                            string uid_input, new_uid, password;
                            
                            switch(user_menu) {

                                case 1: {
                                    int role;
                                    cout << "Enter new user ID: ";
                                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    getline(cin, uid_input);
                                    while(checkinput_obj.checkifUIDexists(uid_input)){
                                        cout<<"User ID already exists, please enter another ID"<<endl;
                                        getline(cin, uid_input);
                                    }
                                    cout << "Enter password: ";
                                    getline(cin, password);
                                    cout << "Enter role (1-Librarian, 2-Student, 3-Faculty): ";
                                    cin >> role;
                                    
                                    if(librarian.create_user(uid_input, password, role)) {
                                        cout << "User created successfully!" << endl;
                                    } else {
                                        cout << "Failed to create user! (NOTE!!! User ID has to be unique)" << endl;
                                    }
                                    break;
                                }

                                case 2: {
                                    cout << "Enter user ID to delete: ";
                                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    getline(cin, uid_input);
                                    int case_del=librarian.delete_user(uid_input);
                                    switch(case_del){
                                        case 0:{
                                            cout << "User not found!" << endl;
                                            break;
                                        }
                                        case 1:{
                                            cout << "User deleted successfully!" << endl;
                                            break;
                                        }
                                        case 2:{
                                            cout<<"User has borrowed/overdue books, cannot delete!"<<endl;
                                            break;
                                        }
                                        default:{
                                            cout<<"Unknown error!"<<endl;
                                            break;
                                        }
                                    }
                                    break;
                                }
                                
                                case 3: {
                                    cout << "Enter user ID to search: ";
                                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    getline(cin, uid_input);
                                    if(librarian.search_user(uid_input)) {
                                    } else {
                                        cout << "User not found!" << endl;
                                    }
                                    break;
                                }

                                case 0:{
                                    break;
                                }
                                default:{
                                    cout << "Invalid choice!" << endl;
                                }
                            }
                        }
                    }
                    else if(main_menu == 2) {  // Book Management
                        int book_menu = 1;
                        
                        while(book_menu) {
                            cout << "\n--------BOOK MANAGEMENT--------\n"
                                 << "1. Add Book\n"
                                 << "2. Delete Book\n"
                                 << "3. Update Book\n"
                                 << "4. Search Book\n"
                                 << "0. Back\n"
                                 << "Choice: ";
                            cin >> book_menu;
            
                            string bookID,ISBN, title, author, publisher, status,reserved;
                            int year;
                            time_t dueDate;
                            Book found_book;
                            
                            switch(book_menu) {
                                case 1: {
                                    cout<< "Enter book ID: ";
                                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    getline(cin, bookID);
                                    while(checkinput_obj.checkifbookIDexists(bookID)){
                                        cout<<"Book ID already exists! Enter a different book ID: ";
                                        getline(cin, bookID);
                                    }
                                    cout << "Enter book title: ";
                                    getline(cin, title);
                                    cout << "Enter author: ";
                                    getline(cin, author);
                                    cout << "Enter publisher: ";
                                    getline(cin, publisher);
                                    cout << "Enter publication year: ";
                                    cin>>year;
                                    cout << "Enter ISBN: ";
                                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    getline(cin, ISBN);
                                    while(!checkinput_obj.ISBN_check(ISBN)){
                                        cout<<"Enter a valid ISBN: ";
                                        getline(cin, ISBN);
                                    }
                                    checkinput_obj.ISBN_standardize(ISBN);
                                    cout << "Enter initial status (Available/Borrowed): ";
                                    getline(cin, status);
                                    while(!checkinput_obj.status_check(status)){
                                        cout<<"Enter a valid status: ";
                                        getline(cin, status);
                                    }
                                    
                                    dueDate = 0;  // Default
                                    if(status=="Borrowed") {
                                        cout << "Enter due in how many days : ";
                                        int days;
                                        cin>>days;
                                        dueDate = std::time(0) + days * 24 * 60 * 60;
                                    }
                                    
                                    if(librarian.addbook(bookID,title, author, publisher, year, ISBN, status, dueDate,"0")) {
                                        cout << "Book added successfully!" << endl;
                                    }
                                    else {
                                        cout << "Failed to add book! (NOTE!!! bookID has to be unique)" << endl;
                                    }
                                    break;
                                }
                                case 2: {
                                    cout << "Enter bookID to delete: ";
                                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    getline(cin, bookID);
                                    int case_del=librarian.deletebook(bookID);
                                    switch(case_del){
                                        case 0:{
                                            cout << "Book not found!" << endl;
                                            break;
                                        }
                                        case 1:{
                                            cout << "Book deleted successfully!" << endl;
                                            break;
                                        }
                                        case 2:{
                                            cout<<"Book is currently borrowed, cannot delete!"<<endl;
                                            break;
                                        }
                                        default:{
                                            cout<<"Unknown error!"<<endl;
                                            break;
                                        }
                                    }
                                    break;
                                }
                                case 3: {
                                    
                                    cout<<"Enter bookID to update: ";
                                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    getline(cin, bookID);
                                    if(!checkinput_obj.checkifbookIDexists(bookID)){
                                        cout<<"Book ID does not exist! "<<endl;
                                    }
                                    cout << "Enter new reserved status(0/1): ";
                                    getline(cin, reserved);
                                    
                                    if(librarian.updatebook(bookID, reserved)){
                                        cout << "Book updated successfully!" << endl;
                                    }
                                    else{
                                        cout << "Book update failed!" << endl;
                                    }
                                    break;
                                }
                                case 4: {
                                    cout << "Enter bookID to search: ";
                                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    getline(cin, bookID);
                                    if(librarian.searchbook(bookID, found_book)){
                                        cout << "Book details:\n";
                                        found_book.display();
                                    }
                                    else{
                                        cout << "Book not found!" << endl;
                                    }
                                    break;
                                }
                                case 0:{
                                    break;
                                }
                                default:{
                                    cout << "Invalid choice!" << endl;
                                }
                            }
                        }
                    }
                    else if(main_menu == 0) {
                        break;
                    }
                    else {
                        cout << "Invalid choice!" << endl;
                    }
                }
                return 0;
            }
            
            case 2:{
                cout<<"Welcome Student"<<endl;
                Student student(uid,upassword);
                cout<<"Do you want to update your credentials: (press 1) or continue: (press 0)"<<endl;
                int update;
                cin>>update;
                while(update){
                    cout<<"Enter new user id"<<endl;
                    string new_uid;
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    getline(cin, new_uid);
                    bool flag=student.setUid(new_uid);
                    if(!flag){
                        cout<<"Please provide a different userid"<<endl;
                        continue;
                    }
                    cout<<"Enter new password"<<endl;
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    string new_upassword;
                    
                    getline(cin, new_upassword);
                    
                    student.setUpassword(new_upassword);
                    update=0;
                }
                cout<<"press 1 to go to menu and 0 to exit"<<endl;
                int menu;
                cin>>menu;
                while(menu){

                    cout<<"\n--------STUDENT MENU--------\n"<<endl;
                    cout<<"press 1 to borrow book\n"<<"press 2 to return book\n"<<"press 3 to reserve book\n"<<"press 4 to pay fine\n"<<"press 5 to check fine\n"<<"press 6 to calculate fine\n"<<"press 7 to check borrowed books\n"<<"press 8 to check borrowing history\n"<<"press 9 to check overdue books\n"<<endl;
                    int choice;
                    cin>>choice;
                    switch(choice){
                        case 1:{
                            l1.displayBooks();
                            cout<<"Enter bookID of book you want to borrow"<<endl;
                            string bookID;
                            Book book;
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                            getline(cin, bookID);

                            bool flag= l1.searchBook(bookID, book);
                            if(!flag){
                                cout<<"Book not found"<<endl;
                                break;
                            }
                            else{
                                cout<<"Book found"<<endl;
                                book.display();
                            }
                            bool flag1=student.borrowBook(book);
                            if(flag1){
                                cout<<"Book borrowed successfully"<<endl;
                            }
                            else{
                                cout<<"Cannot borrow book"<<endl;
                            }
                            break;
                        }
                        case 2:{
                            cout<<"Enter bookID of book you want to return"<<endl;
                            string bookID;
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            Book book;
                            getline(cin, bookID);
                            bool flag= l1.searchBook(bookID,book);
                            if(!flag){
                                cout<<"Book not found"<<endl;
                                break;
                            }
                            else{
                                cout<<"Book found"<<endl;
                                book.display();
                            }
                            if(student.returnBook(book)){
                                cout<<"Book returned successfully"<<endl;
                            }
                            else{
                                cout<<"Book not borrowed"<<endl;
                            }
                            break;
                        }
                        case 3:{
                            l1.displayBooksforReservation();
                            cout<<"Enter bookID of book you want to reserve"<<endl;
                            string bookID;
                            Book book;
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            getline(cin, bookID);
                            bool flag= l1.searchBook(bookID,book);    
                            if(!flag){
                                cout<<"Book not found"<<endl;
                                break;
                            }
                            if(student.reserveBook(book)){
                                cout<<"Book reserved successfully"<<endl;
                            }
                            else{
                                cout<<"Book reservation failed"<<endl;
                            }
                            break;
                        }
                        case 4:{
                            cout<<"Enter amount you want to pay"<<endl;
                            float amount;
                            cin>>amount;
                            bool flag=student.payFine(amount,uid);
                            if(flag){
                                cout<<"Fine paid successfully"<<endl;
                            }
                            break;
                        }
                        case 5:{

                            cout<<"Your fine is: "<<student.getAccount().getFines()<<endl;
                            break;
                        }
                        case 6:{
                            cout<<"Enter overdue days"<<endl;
                            int days;
                            cin>>days;
                            cout<<"Your fine is: "<<student.calculateFine(days)<<endl;
                            break;
                        }
                        case 7:{
                            cout<<"Borrowed Books are: "<<endl;
                            student.getAccount();
                            const auto borrowedBooks = student.account.getBorrowedBooks();
                            for(int i=0;i<borrowedBooks.size();i++){
                                borrowedBooks[i].display();
                            }
                            break;
                        }
                        case 8:{
                            cout<<"Borrowing History is: "<<endl;
                            student.getAccount();
                            const auto borrowingHistory = student.account.getBorrowingHistory();
                            for(int i=0;i<borrowingHistory.size();i++){
                                borrowingHistory[i].display();
                            }
                            break;
                        }
                        case 9:{
                            cout<<"Overdue Books are: "<<endl;
                            student.getAccount();
                            const auto overdueBooks = student.account.getOverdueBooks();
                            for(int i=0;i<overdueBooks.size();i++){
                                overdueBooks[i].display();
                            }
                            break;
                        }
                        default:{
                            cout<<"Invalid Choice"<<endl;
                            break;
                        }
                    }
                    cout<<"press 0 to exit and 1 to continue"<<endl;
                    cin>>menu;
                }
                return 0;
            }
            case 3: {
                cout<<"Welcome Faculty"<<endl;
                Faculty faculty(uid,upassword);
                cout<<"Do you want to update your credentials: (press 1) or continue: (press 0)"<<endl;
                int update;
                cin>>update;
                while(update){
                    cout<<"Enter new user id"<<endl;
                    string new_uid;
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    getline(cin, new_uid);
                    bool flag=faculty.setUid(new_uid);
                    if(!flag){
                        cout<<"Please provide a different userid"<<endl;
                        continue;
                    }
                    cout<<"Enter new password"<<endl;
                    string new_upassword;
                    getline(cin, new_upassword);
                    
                    faculty.setUpassword(new_upassword);
                    update=0;
                }
                cout<<"press 1 to go to menu and 0 to exit"<<endl;
                int menu;
                cin>>menu;
                while(menu){

                    cout<<"\n--------FACULTY MENU--------\n"<<endl;
                    cout<<"press 1 to borrow book\n"<<"press 2 to return book\n"<<"press 3 to reserve book\n"<<"press 4 to check borrowed books\n"<<"press 5 to check borrowing history\n"<<"press 6 to check overdue books\n"<<endl;
                    int choice;
                    cin>>choice;
                    switch(choice){
                        case 1:{
                            l1.displayBooks();
                            cout<<"Enter bookID of book you want to borrow"<<endl;
                            string bookID;
                            Book book;
                            getline(cin, bookID);
                            bool flag= l1.searchBook(bookID,book);
                            if(!flag){
                                cout<<"Book not found"<<endl;
                                break;
                            }
                            else{
                                cout<<"Book found"<<endl;
                                book.display();
                            }
                            bool flag1=faculty.borrowBook(book);
                            if(flag1){
                                cout<<"Book borrowed successfully"<<endl;
                            }
                            else{
                                cout<<"Cannot borrow book"<<endl;
                            }
                            break;
                        }
                        case 2:{
                            cout<<"Enter ISBN of book you want to return"<<endl;
                            string bookID;
                            Book book;
                            getline(cin, bookID);
                            bool flag= l1.searchBook(bookID,book);
                            if(!flag){
                                cout<<"Book not found"<<endl;
                                break;
                            }
                            else{
                                cout<<"Book found"<<endl;
                                book.display();
                            }
                            if(faculty.returnBook(book)){
                                cout<<"Book returned successfully"<<endl;
                            }
                            else{
                                cout<<"Book not borrowed"<<endl;
                            }
                            break;
                        }
                        case 3:{
                            l1.displayBooksforReservation();
                            cout<<"Enter bookID of book you want to reserve"<<endl;
                            string bookID;
                            Book book;
                            getline(cin, bookID);
                            bool flag= l1.searchBook(bookID,book);    
                            if(!flag){
                                cout<<"Book not found"<<endl;
                                break;
                            }
                            if(faculty.reserveBook(book)){
                                cout<<"Book reserved successfully"<<endl;
                            }
                            else{
                                cout<<"Book not available"<<endl;
                            }
                            break;
                        }
                        
                        case 4:{
                            cout<<"Borrowed Books are: "<<endl;
                            faculty.getAccount();
                            const auto borrowedBooks = faculty.account.getBorrowedBooks();
                            for(int i=0;i<borrowedBooks.size();i++){
                                borrowedBooks[i].display();
                            }
                            break;
                        }
                        case 5:{
                            cout<<"Borrowing History is: "<<endl;
                            faculty.getAccount();
                            const auto borrowingHistory = faculty.account.getBorrowingHistory();
                            for(int i=0;i<borrowingHistory.size();i++){
                                borrowingHistory[i].display();
                            }
                            break;
                        }
                        case 6:{
                            cout<<"Overdue Books are: "<<endl;
                            faculty.getAccount();
                            const auto overdueBooks = faculty.account.getOverdueBooks();
                            for(int i=0;i<overdueBooks.size();i++){
                                overdueBooks[i].display();
                            }
                            break;
                        }
                        default:{
                            cout<<"Invalid Choice"<<endl;
                            break;
                        }
                    }
                    cout<<"press 0 to exit and 1 to continue"<<endl;
                    cin>>menu;
                }
                return 0;

            }
            default: {
                cout << "Invalid choice!" << endl;
                break;
            }
                  
        }

    }


}