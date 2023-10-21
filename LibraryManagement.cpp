#include <iostream>
#include <vector>
#include <ctime>
#include <limits>
#include <algorithm>
#include <iomanip>

class Item {
private:
    std::string title;
    int id;

public:
    Item(const std::string& title, int id) : title(title), id(id) {}

    const std::string& getTitle() const {
        return title;
    }

    int getId() const {
        return id;
    }
};

class Book : public Item {
private:
    std::string author;
    bool isAvailable;
    int borrowerId;

public:
    Book(const std::string& title, int id, const std::string& author)
        : Item(title, id), author(author), isAvailable(true), borrowerId(-1) {}

    const std::string& getAuthor() const {
        return author;
    }

    bool getIsAvailable() const {
        return isAvailable;
    }

    int getBorrowerId() const {
        return borrowerId;
    }

    void setAvailability(bool available) {
        isAvailable = available;
    }

    void setBorrower(int memberId) {
        borrowerId = memberId;
    }
};

class Member {
private:
    int memberId;
    std::vector<int> borrowedBooks;
    std::vector<int> returnedBooks;

public:
    Member(int memberId) : memberId(memberId) {}

    int getMemberId() const {
        return memberId;
    }

    const std::vector<int>& getBorrowedBooks() const {
        return borrowedBooks;
    }

    const std::vector<int>& getReturnedBooks() const {
        return returnedBooks;
    }

    void borrowBook(int bookId) {
        borrowedBooks.push_back(bookId);
    }

    void returnBook(int bookId) {
        returnedBooks.push_back(bookId);
    }
};

class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;
    int lastMemberId;

public:
    Library() : lastMemberId(1000) {}

    void addBook(const std::string& title, const std::string& author, int quantity) {
        for (int i = 0; i < quantity; ++i) {
            int id = generateBookId();
            Book newBook(title, id, author);
            books.push_back(newBook);
            std::cout << "Book added successfully. ID: " << id << "\n";
        }
    }

    void displayBooks() {
        if (books.empty()) {
            std::cout << "No books available in the library.\n";
            return;
        }

        std::cout << "Library Books:\n";
        std::cout << "---------------------------------------------------------\n";
        std::cout << "|  ID  |          Title          |        Author        |  Availability  |\n";
        std::cout << "---------------------------------------------------------\n";
        for (const auto& book : books) {
            std::cout << "| " << std::setw(4) << book.getId() << " | " << std::setw(23) << book.getTitle().substr(0, 20) << " | " 
                      << std::setw(20) << book.getAuthor().substr(0, 20) << " | " << std::setw(13);
            if (book.getIsAvailable()) {
                std::cout << "Yes |\n";
            } else {
                std::cout << "No  |\n";
            }
        }
        std::cout << "---------------------------------------------------------\n";
    }

    int generateBookId() {
        return books.size() + 1;
    }

    void borrowBook(int bookId, int memberId) {
        for (auto& book : books) {
            if (book.getId() == bookId) {
                if (book.getIsAvailable()) {
                    book.setAvailability(false);
                    book.setBorrower(memberId);
                    members[memberId - 1001].borrowBook(bookId); // Adjust index
                    std::cout << "Book with ID " << bookId << " borrowed successfully by Member ID " << memberId << ".\n";
                    return;
                } else {
                    std::cout << "Book with ID " << bookId << " is not available for borrowing.\n";
                }
                return;
            }
        }
        std::cout << "Book with ID " << bookId << " not found.\n";
    }

    void returnBook(int bookId, int memberId) {
        for (auto& book : books) {
            if (book.getId() == bookId) {
                if (!book.getIsAvailable() && book.getBorrowerId() == memberId) {
                    book.setAvailability(true);
                    book.setBorrower(-1);
                    members[memberId - 1001].returnBook(bookId); // Adjust index
                    std::cout << "Book with ID " << bookId << " returned successfully by Member ID " << memberId << ".\n";
                    return;
                } else {
                    std::cout << "Book with ID " << bookId << " is not borrowed by Member ID " << memberId << ".\n";
                }
                return;
            }
        }
        std::cout << "Book with ID " << bookId << " not found.\n";
    }

    void printLibraryCard(int memberId) {
        if (memberId < 1001 || memberId > lastMemberId) {
            std::cout << "Invalid Member ID. Please try again.\n";
            return;
        }

        int memberIndex = memberId - 1001; // Adjust index
        if (memberIndex >= 0 && memberIndex < members.size()) {
            const Member& member = members[memberIndex];
            std::cout << "Library Card for Member ID " << memberId << ":\n";
            
            const std::vector<int>& borrowedBooks = member.getBorrowedBooks();
            const std::vector<int>& returnedBooks = member.getReturnedBooks();
            
            if (!borrowedBooks.empty()) {
                std::cout << "Borrowed Books:\n";
                std::cout << "-----------------\n";
                std::cout << "|  ID  |   Title   |\n";
                std::cout << "-----------------\n";
                for (const auto& bookId : borrowedBooks) {
                    for (const auto& book : books) {
                        if (book.getId() == bookId) {
                            std::cout << "| " << std::setw(4) << book.getId() << " | " << std::setw(10) << book.getTitle().substr(0, 10) << " |\n";
                        }
                    }
                }
                std::cout << "-----------------\n";
            }
            
            if (!returnedBooks.empty()) {
                std::cout << "Returned Books:\n";
                std::cout << "-----------------\n";
                std::cout << "|  ID  |   Title   |\n";
                std::cout << "-----------------\n";
                for (const auto& bookId : returnedBooks) {
                    for (const auto& book : books) {
                        if (book.getId() == bookId) {
                            std::cout << "| " << std::setw(4) << book.getId() << " | " << std::setw(10) << book.getTitle().substr(0, 10) << " |\n";
                        }
                    }
                }
                std::cout << "-----------------\n";
            }
            return;
        }
        std::cout << "Member with ID " << memberId << " not found.\n";
    }

    void registerMember() {
        int memberId = lastMemberId + 1;
        Member newMember(memberId);
        members.push_back(newMember);
        lastMemberId = memberId;
        std::cout << "Member registered successfully. Member ID: " << memberId << "\n";
    }
};

int main() {
    Library library;

    int choice;
    do {
        std::cout << "\nLibrary Management System Menu:\n";
        std::cout << "1. Display Books\n";
        std::cout << "2. Borrow Book\n";
        std::cout << "3. Return Book\n";
        std::cout << "4. Add Book\n";
        std::cout << "5. Register Member\n";
        std::cout << "6. Print Library Card\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                library.displayBooks();
                break;
            case 2: {
                int bookId, memberId;
                std::cout << "Enter the ID of the book you want to borrow: ";
                std::cin >> bookId;
                std::cout << "Enter your Member ID: ";
                std::cin >> memberId;
                library.borrowBook(bookId, memberId);
                break;
            }
            case 3: {
                int bookId, memberId;
                std::cout << "Enter the ID of the book you want to return: ";
                std::cin >> bookId;
                std::cout << "Enter your Member ID: ";
                std::cin >> memberId;
                library.returnBook(bookId, memberId);
                break;
            }
            case 4: {
                std::string title, author;
                int quantity;
                std::cout << "Enter book title: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, title);

                std::cout << "Enter book author: ";
                std::getline(std::cin, author);

                std::cout << "Enter quantity: ";
                std::cin >> quantity;

                library.addBook(title, author, quantity);
                break;
            }
            case 5:
                library.registerMember();
                break;
            case 6: {
                int memberId;
                std::cout << "Enter Member ID to print library card: ";
                std::cin >> memberId;
                library.printLibraryCard(memberId);
                break;
            }
            case 7:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
