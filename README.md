# Library Management System

## Introduction

This C++ program simulates a Library Management System, allowing librarians to manage books and library members. It offers functionalities such as adding books, borrowing and returning books, displaying available books, registering new members, and printing library cards.

## Classes

### `Item`

- `Item` is the base class for books and provides attributes like `title` and `id`.
- It includes a constructor to initialize these attributes and accessor methods to get the title and ID.

### `Book` (Inherits from `Item`)

- `Book` is a derived class from `Item` and represents individual books in the library.
- It includes additional attributes such as `author`, `isAvailable`, and `borrowerId`.
- A constructor initializes these attributes, and accessor methods allow access to book details.
- Additionally, `Book` provides methods to set book availability and borrower information.

### `Member`

- `Member` class represents library members and stores information about the books they have borrowed and returned.
- The constructor initializes a member with a unique `memberId`.
- Accessor methods allow access to member details, borrowed books, and returned books.
- Methods like `borrowBook` and `returnBook` add book IDs to the respective lists when books are borrowed or returned.

### `Library`

- `Library` manages the library's collection of books, members, and provides various functionalities.
- It includes attributes for storing books, members, and the last assigned member ID.
- The `addBook` function allows librarians to add books to the library, generating unique book IDs for each.
- `displayBooks` presents a well-formatted table of available books.
- `generateBookId` calculates a unique book ID.
- `borrowBook` lets members borrow available books and updates the book's status and borrower's records.
- `returnBook` allows members to return books, updating availability and recording the transaction.
- `printLibraryCard` prints a library card for a specific member, displaying their borrowed and returned books.
- `registerMember` adds new members to the library and generates unique member IDs.

## Main Function

- The `main` function serves as the program's entry point.
- Users interact with the program through a menu offering options to display books, borrow books, return books, add books, register members, print library cards, or exit.
- A `do-while` loop ensures that the program continues running until the user chooses to exit.

---

This program demonstrates a basic library management system with an intuitive command-line interface. It provides essential functions for managing books and members, making it useful for small libraries or educational purposes.
