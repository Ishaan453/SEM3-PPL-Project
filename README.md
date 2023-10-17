# Library Management System

## Overview
The **Library Management System** is a C++ program that simulates the operations of a library. It allows for the management of books, library members, book borrowing, and late fee calculation.

## Classes

### `Item`
- Base class for library items.
- Attributes:
  - `title` (string): The title of the item.
  - `id` (int): Unique identifier for the item.

### `Book`
- Derived from the `Item` class.
- Additional attributes:
  - `author` (string): The author of the book.
  - `isAvailable` (bool): Availability status of the book.
  - `borrowerId` (int): ID of the member who borrowed the book.
  - `dueDate` (std::time_t): Due date for the borrowed book.

### `Member`
- Represents library members.
- Attributes:
  - `memberId` (int): Unique member identifier.
  - `currentlyBorrowedBooks` (vector of ints): IDs of books currently borrowed.
  - `borrowingHistory` (vector of pairs): Borrowing history with book IDs and timestamps.

### `Library`
- Core component of the system.
- Manages books, members, and library operations.
- Constructor initializes the late fee rate.
- Methods include adding books, displaying books, borrowing books, returning books, calculating late fees, printing library cards, and registering members.

## Initialization
- The program begins by setting a late fee rate, e.g., $0.10 per day.
- An instance of the `Library` class is created with the provided late fee rate.

## Menu System
- The main function presents a menu system, allowing users to choose from various library-related operations.

## Menu Options
1. **Display Books**: Shows a list of all available books in the library.
2. **Borrow Book**: Allows a member to borrow a book, updating book availability and member records.
3. **Return Book**: Allows a member to return a book, calculating late fees if applicable.
4. **Add Book**: Lets the librarian add new books to the library.
5. **Register Member**: Allows the librarian to register new members.
6. **Print Library Card**: Generates a library card for a member, displaying their currently borrowed books and borrowing history.
7. **Exit**: Exits the program.

## Functionality
- **Adding Books**: The `addBook` function adds books to the library, specifying the title, author, and quantity. It generates unique book IDs for each book.
- **Borrowing Books**: The `borrowBook` function allows a member to borrow a book by providing the book ID and their member ID. It updates book availability, borrower information, and due dates.
- **Returning Books**: The `returnBook` function enables members to return books. It calculates late fees for overdue books and updates the library records.
- **Late Fee Calculation**: The `calculateLateFee` function calculates late fees based on the difference between the due date and the return date.
- **Printing Library Card**: The `printLibraryCard` function generates a library card for a member, displaying their currently borrowed books and borrowing history.
- **Registering Members**: The `registerMember` function allows the librarian to register new members, assigning them unique member IDs.

## Usage
- Users can select menu options by entering the corresponding numeric choice.

## Exit
- The program continues to run until the user selects the "Exit" option.

## Error Handling
- The program provides error messages for various scenarios, such as invalid member IDs or unavailable books.

## Dependencies
- The code uses C++ standard libraries for data structures and time handling.

## Notes
- The code uses Unix timestamps to represent time. This may need adjustment for specific time zone considerations.

---

This documentation provides an overview of the structure and functionality of the Library Management System. Users can follow the menu system to interact with the library, managing books and members.
