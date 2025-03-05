#include "Library.h"
#include <iostream>
#include <fstream>
#include <sstream>
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
        Library l1;
        while(!l1.authenticateUser(uid,upassword)){
            cout<<"Do you want to exit: (press 0) or login again: (press 1)"<<endl;
            int choice;
            cin>>choice;
            if(choice==0){
                return 0;
            }
            cout<<"Please enter user id"<<endl;
            string uid;
            cin>>uid;
            cout<<"Please enter password"<<endl;
            string upassword;
            cin>>upassword;
        }

        cout<<"Please enter User Role "<<endl;
        cout<<"press 1 for Librarian\n"<<"press 2 for Student\n"<<"press 3 for Faculty"<<endl;
        int role;
        cin>>role;

        switch(role){
            case 1:
                cout<<"Welcome Librarian"<<endl;
                cout<<"\n--------LIBRARIAN MENU--------\n"<<endl;
                cout<<"press 1 to go to menu and 0 to exit"<<endl;
                int menu;
                cin>>menu;
                while(menu){
                    cout<<"press 1 to go to user menu\n"<<"press 2 to go to book menu\n"<<endl;
                    int choice;
                    cin>>choice;
                    if(choice==1){  
                        cout<<"\n--------USER MENU--------\n"<<endl;
                        cout<<"press 1 to add user\n"<<"press 2 to delete user\n"<<"press 3 to update user\n"<<"press 4 to search user"<<endl;
                        cout<<"press 0 to exit and 1 to continue"<<endl;
                        cin>>menu;
                    }
                    else if(choice==2){
                        cout<<"\n--------BOOK MENU--------\n"<<endl;
                        cout<<"press 1 to add book\n"<<"press 2 to delete book\n"<<"press 3 to update book\n"<<"press 4 to search book"<<endl;
                        cout<<"press 0 to exit and 1 to continue"<<endl;
                        cin>>menu;
                    }
                    else{
                        cout<<"Invalid Choice"<<endl;
                        return 0;
                        cout<<"press 0 to exit and 1 to go to menu"<<endl;
                        cin>>menu;
                    }
                }
                return 0;
            case 2:
                cout<<"Welcome Student"<<endl;
                Student student(uid,upassword);
                cout<<"press 1 to go to menu and 0 to exit"<<endl;
                int menu;
                cin>>menu;
                while(menu){

                    cout<<"\n--------STUDENT MENU--------\n"<<endl;
                    cout<<"press 1 to borrow book\n"<<"press 2 to return book\n"<<"press 3 to reserve book\n"<<"press 4 to pay fine\n"<<"press 5 to check fine\n"<<"press 6 to check borrowed books\n"<<"press 7 to check borrowing history\n"<<endl;
                    int choice;
                    cin>>choice;
                    string ISBN;
                    Book book;
                    switch(choice){
                        case 1:
                            cout<<"Enter ISBN of book you want to borrow"<<endl;
                            cin>>ISBN;
                            bool flag= l1.searchBook(ISBN,book);
                            if(!flag){
                                cout<<"Book not found"<<endl;
                                break;
                            }
                            if(student.borrowBook(book)){
                                cout<<"Book borrowed successfully"<<endl;
                            }
                            else{
                                cout<<"Book not available"<<endl;
                            }
                            break;
                        case 2:
                            cout<<"Enter ISBN of book you want to return"<<endl;
                            cin>>ISBN;
                            bool flag= l1.searchBook(ISBN,book);
                            if(!flag){
                                cout<<"Book not found"<<endl;
                                break;
                            }
                            if(student.returnBook(book)){
                                cout<<"Book returned successfully"<<endl;
                            }
                            else{
                                cout<<"Book not borrowed"<<endl;
                            }
                            break;
                        case 3:
                            cout<<"Enter ISBN of book you want to reserve"<<endl;
                            cin>>ISBN;
                            bool flag= l1.searchBook(ISBN,book);    
                            if(!flag){
                                cout<<"Book not found"<<endl;
                                break;
                            }
                            if(student.reserveBook(book)){
                                cout<<"Book reserved successfully"<<endl;
                            }
                            else{
                                cout<<"Book not available"<<endl;
                            }
                        case 4:
                            cout<<"Enter amount you want to pay"<<endl;
                            float amount;
                            cin>>amount;
                            student.payFine(amount);
                            cout<<"Fine paid successfully"<<endl;
                            break;
                        case 5:
                            cout<<"Your fine is: "<<student.getAccount().getFines()<<endl;
                            break;
                        case 6:
                            cout<<"Borrowed Books are: "<<endl;
                            for(auto book: student.getAccount().getBorrowedBooks()){
                                book.display();
                            }
                            break;
                        case 7:
                            cout<<"Borrowing History is: "<<endl;
                            for(auto book: student.getAccount().getBorrowingHistory()){
                                book.display();
                            }
                            break;
                        default:
                            cout<<"Invalid Choice"<<endl;
                            break;
                    }
                    cout<<"press 0 to exit and 1 to continue"<<endl;
                    cin>>menu;
                }
                return 0;
            case 3:
                cout<<"Welcome Faculty"<<endl;
                cout<<"press 1 to go to menu and 0 to exit"<<endl;
                int menu;   
                cin>>menu;
                while(menu){
                    cout<<"\n--------FACULTY MENU--------\n"<<endl;
                    cout<<"press 1 to borrow book\n"<<"press 2 to return book\n"<<"press 3 to pay fine\n"<<"press 4 to check fine\n"<<"press 5 to check borrowed books\n"<<"press 6 to check borrowing history\n"<<endl;               
                    cout<<"press 0 to exit"<<endl;
                    cin>>menu;
                }
                return 0;
            default:
                cout<<"Invalid User Role"<<endl;
                return 0;        
        }

    }


}