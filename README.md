# Library Management System

This is a simple command-line library management system implemented in C++. It allows you to manage a library's collection of books and magazines and also perform operations like borrowing, returning, and managing members.

## Classes

### `Item`

`Item` is an abstract base class that represents the basic properties of any library item, such as title and ID. This class has protected data members for title and ID, a constructor, a virtual destructor, and pure virtual functions to be implemented by derived classes.

### `Book` (Derived from `Item`)

`Book` is a class that represents books in the library. It inherits from the `Item` class and adds properties like author, availability status, and borrower ID. It overrides the pure virtual functions from the base class and provides its own implementations.

### `Magazine` (Derived from `Item`)

`Magazine` is a class that represents magazines in the library. It also inherits from the `Item` class and overrides the pure virtual functions with its own implementations. Magazines are always available and do not have authors in this implementation.

### `Member`

`Member` is a class representing library members. It has a member ID and tracks items that have been borrowed and returned by the member.

### `Library`

`Library` is the main class that orchestrates the library management. It maintains collections of items (books and magazines), members, and the last member ID. It provides functions to add items, display items, borrow and return items, print library cards, and register new members. It also manages the cleanup of dynamically allocated items upon destruction.

## Main Function

The `main` function provides a simple command-line menu for interacting with the library management system. Users can select options to display items, borrow or return items, add books and magazines, register new members, print library cards, and exit the program.

## Usage

1. **Display Items:** View a tabulated list of items in the library, including their ID, title, author (for books), and availability status.

2. **Borrow Item:** Borrow an item by specifying its ID and your Member ID.

3. **Return Item:** Return a previously borrowed item by specifying its ID and your Member ID.

4. **Add Book:** Add books to the library by providing a title, author, and quantity.

5. **Add Magazine:** Add magazines to the library by providing a title and quantity.

6. **Register Member:** Register new members with an automatically assigned Member ID.

7. **Print Library Card:** View a library card for a member, displaying the items they have borrowed and returned.

8. **Exit:** Quit the program.

## Formatting

The code includes formatting for output to ensure that the tabulated information is presented neatly, even with varying lengths of titles, authors, and other details.

This library management system is a simplified representation and can be extended with more features and error handling as needed.
