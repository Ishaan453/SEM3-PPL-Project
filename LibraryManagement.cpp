#include <iostream>
#include <vector>
#include <ctime>
#include <limits>
#include <algorithm>

class Item {
public:
    std::string title;
    int id;
};

class Book : public Item {
public:
    std::string author;
    bool isAvailable;
    int borrowerId;
    std::time_t dueDate;
};

class Member {
public:
    int memberId;
    std::vector<int> currentlyBorrowedBooks;
    std::vector<std::pair<int, std::time_t>> borrowingHistory;
};

class Library {
private:
    std::vector<Book> books;
    std::vector<Member> members;
    int lastMemberId;
    float lateFeePerDay;  

    bool isMemberValid(int memberId) {
        auto it = std::find_if(members.begin(), members.end(),
            [memberId](const Member& member) {
                return member.memberId == memberId;
            });

        return it != members.end();
    }

public:
    Library(float lateFeeRate) : lastMemberId(1000), lateFeePerDay(lateFeeRate) {}

    void addBook(std::string title, std::string author, int quantity) {
        for (int i = 0; i < quantity; ++i) {
            int id = generateBookId();
            Book newBook = {title, id, author, true, -1, 0};
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
        for (const auto& book : books) {
            std::cout << "Title: " << book.title << ", Author: " << book.author
                      << ", ID: " << book.id << ", Available: " << (book.isAvailable ? "Yes" : "No");
            if (!book.isAvailable)
                std::cout << ", Borrower ID: " << book.borrowerId << ", Due Date: " << std::ctime(&book.dueDate);
            std::cout << "\n";
        }
    }

    int generateBookId() {
        return books.size() + 1;
    }

    void borrowBook(int bookId, int memberId) {
        if (!isMemberValid(memberId)) {
            std::cout << "Invalid Member ID. Please try again.\n";
            return;
        }

        for (auto& book : books) {
            if (book.id == bookId) {
                if (book.isAvailable) {
                    book.isAvailable = false;
                    book.borrowerId = memberId;
                    std::time_t now = std::time(0);
                    book.dueDate = now + 7 * 24 * 60 * 60;  // 7 days
                    std::cout << "Book with ID " << bookId << " borrowed successfully by Member ID " << memberId << ".\n";

                    for (auto& member : members) {
                        if (member.memberId == memberId) {
                            member.currentlyBorrowedBooks.push_back(bookId);
                            member.borrowingHistory.push_back({bookId, now});
                            return;
                        }
                    }
                } else {
                    std::cout << "Book with ID " << bookId << " is not available for borrowing.\n";
                }
                return;
            }
        }
        std::cout << "Book with ID " << bookId << " not found.\n";
    }

    void returnBook(int bookId, int memberId) {
        if (!isMemberValid(memberId)) {
            std::cout << "Invalid Member ID. Please try again.\n";
            return;
        }

        for (auto& book : books) {
            if (book.id == bookId) {
                if (!book.isAvailable && book.borrowerId == memberId) {
                    book.isAvailable = true;
                    book.borrowerId = -1;
                    std::time_t now = std::time(0);
                    float lateFee = calculateLateFee(book.dueDate, now);
                    if (lateFee > 0) {
                        std::cout << "Late Fee for Book with ID " << bookId << ": $" << lateFee << "\n";
                    }
                    std::cout << "Book with ID " << bookId << " returned successfully by Member ID " << memberId << ".\n";

                    for (auto& member : members) {
                        if (member.memberId == memberId) {
                            auto& currentlyBorrowed = member.currentlyBorrowedBooks;
                            auto it = std::find(currentlyBorrowed.begin(), currentlyBorrowed.end(), bookId);
                            if (it != currentlyBorrowed.end())
                                currentlyBorrowed.erase(it);

                            auto& history = member.borrowingHistory;
                            history.push_back({bookId, now});

                            return;
                        }
                    }
                } else {
                    std::cout << "Book with ID " << bookId << " is not borrowed by Member ID " << memberId << ".\n";
                }
                return;
            }
        }
        std::cout << "Book with ID " << bookId << " not found.\n";
    }

    float calculateLateFee(std::time_t dueDate, std::time_t returnDate) {
        if (returnDate > dueDate) {
            double diffSeconds = std::difftime(returnDate, dueDate);
            double diffDays = diffSeconds / (60 * 60 * 24);
            return static_cast<float>(diffDays) * lateFeePerDay;
        }
        return 0.0;
    }
    
void printLibraryCard(int memberId) {
    if (!isMemberValid(memberId)) {
        std::cout << "Invalid Member ID. Please try again.\n";
        return;
    }

    for (const auto& member : members) {
        if (member.memberId == memberId) {
            std::cout << "Library Card for Member ID " << memberId << ":\n";
            std::cout << "Currently Borrowed Books:\n";
            for (const auto& bookId : member.currentlyBorrowedBooks) {
                for (const auto& book : books) {
                    if (book.id == bookId) {
                        std::cout << "Title: " << book.title << ", Author: " << book.author
                                  << ", ID: " << book.id << ", Due Date: " << std::ctime(&book.dueDate) << "\n";
                    }
                }
            }

            std::cout << "\nBorrowing History:\n";
            for (const auto& entry : member.borrowingHistory) {
                for (const auto& book : books) {
                    if (book.id == entry.first) {
                        std::cout << "Title: " << book.title << ", Author: " << book.author
                                  << ", ID: " << book.id;

                        if (book.isAvailable)
                            std::cout << ", Borrowed On: " << std::ctime(&entry.second) << " (Not Returned)\n";
                        else
                            std::cout << ", Returned On: " << std::ctime(&entry.second) << "\n";
                    }
                }
            }

            return;
        }
    }
    std::cout << "Member with ID " << memberId << " not found.\n";
}

    void registerMember() {
        int memberId = ++lastMemberId;
        Member newMember = {memberId, {}, {}};
        members.push_back(newMember);
        std::cout << "Member registered successfully. Member ID: " << memberId << "\n";
    }
};

int main() {
    float lateFeeRate = 0.1;  // Example late fee rate: $0.1 per day
    Library library(lateFeeRate);

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
