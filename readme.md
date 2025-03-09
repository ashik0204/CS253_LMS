# Library Management System

This program developed as part of the CS253 course cpp assignment implements a simple **Library Management System** that allows users (Librarians, Students, and Faculty) to interact with the system after authentication and basically manages the library.

For administrator access while logging in the user can use the administrator id and password (for testing purposes)(admin123,adminhere)

## Key Features
>note: the program features are primarily implemented based on the assignment document uploaded for the course

- **User Authentication**: Secure login for users (Librarian, Student, Faculty) with unique User IDs.
- **Role-Based Access**:
    - Access is granted based on roles stored and updated in the `users.csv`
- **Book Management**:
    - Add, delete, update, and search books.
    - Borrow, return, and reserve books.
- **Fine Management**:
  #### Students

  - Students can view and pay fines.
  - Students can view overdue books.

  #### Faculty

  - Faculty can view overdue books.
- **User Facilities**
    >We assume each user has a unique user id and each book has a unique book id
    - Student
        - Can borrow, return and reserve books
        - Can view, pay and calculate fines from the number of days overdue
        - Can view borrowing history, overdue books and borrowed books
    - Faculty
        - Can borrow, return and reserve books
        - Can view borrowing history, overdue books and borrowed books
    - Librarian
        - Can manage both users and books
        - Can add, remove and search users by user id
        - Can add, remove, update and search books by book id

- **Borrowing History & Overdue Books**:
  - Users can view their borrowing history and overdue books.

## File Structure

```
CS253_LMS
|---bin
|   |---lms.exe
|---data
|   |---accounts.csv
|   |---books.csv
|   |---users.csv
|---include
|   |---Account.h
|   |---Book.h
|   |---checkinput.h
|   |---Faculty.h
|   |---Librarian.h
|   |---Library.h
|   |---Student.h
|   |---User.h
|---src
|   |---Account.cpp
|   |---Book.cpp
|   |---checkinput.cpp
|   |---Faculty.cpp
|   |---Librarian.cpp
|   |---Library.cpp
|   |---Student.cpp
|   |---User.cpp
|---readme.md


```

## Data Storage

- **Books**: 
    - Stored in `books.csv` 
    - Fields : `BookID`, `Title`, `Author`, `Publisher`, `Year`, `ISBN`, `Status`, `DueDate`, `Reserved`. 
- **Users**: 
    - Stored in `users.csv` 
    - Fields: `UserID`, `User Password`, `Role`.
- **Accounts**: 
    - Stored in `accounts.csv`
    - Fields: `User id`, `isFaculty`, `fines`, `borrowedBooks`, `overdueBooks`, `borrowingHistory`.
    

## Compilation & Execution

To compile the program using `MSVC `, navigate to the `root/` directory and run:

```sh
cl /I include /I other_include src\*.cpp /Fe:bin\lms.exe /EHsc
```

To run the compiled program again navigate to the `root/` director

```sh
bin\lms.exe
```
## User Manual
A user ( student/faculty/librarian) will have to log into the system to use the LMS. 

After logging in according to the role (student/faculty/librarian) the available action set varies.

>the user will also have an option to update their credentials after logging in

After logging in depending on this action set the user will get a set of options showing the possible operations that can be executed.

Depending on the users' choice here the corresponding operation will be executed.
After each operation the user will get a prompt asking whether to continue running the program or to terminate it (exit)

## For testing purposes
Sample login credentials: (uid,upassword)
- Student: studentX, studentX
- Faculty: new_fac, new_fac
- Librarian/administrator: admin123, adminhere
