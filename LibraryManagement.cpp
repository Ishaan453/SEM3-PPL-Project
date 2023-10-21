#include <iostream>
#include <vector>
#include <ctime>
#include <limits>
#include <algorithm>
#include <iomanip>

class Item {
    protected:
        std::string title;
        int id;
    public:
        Item(const std::string& title, int id) : title(title), id(id) {}
        virtual ~Item() {} 
        virtual const std::string& getTitle() const = 0;
        virtual int getId() const = 0;
        virtual void displayInfo() const = 0;
};

class Book : public Item {
private:
    std::string author;
    bool isAvailable;
    int borrowerId;

public:
    Book(const std::string& title, int id, const std::string& author)
        : Item(title, id), author(author), isAvailable(true), borrowerId(-1) {}

    const std::string& getTitle() const override {
        return title;
    }

    int getId() const override {
        return id;
    }

    void displayInfo() const override {
        std::cout << "| " << std::setw(4) << id << " | " << std::setw(25) << title.substr(0, 23) << " | " << std::setw(25) << author.substr(0, 23) << " | " << std::setw(12) << (isAvailable ? "Yes" : "No") << " |\n";
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

class Magazine : public Item {

public:
    Magazine(const std::string& title, int id) : Item(title, id) {}

    const std::string& getTitle() const override {
        return title;
    }

    int getId() const override {
        return id;
    }

    void displayInfo() const override {
        std::cout << "| " << std::setw(4) << id << " | " << std::setw(25) << title.substr(0, 23) << " | "<<std::setw(25)<<"N/A" << " | " << std::setw(12) << "Yes" << " |\n";
    }
};

class Member {
private:
    int memberId;
    std::vector<int> borrowedItems;
    std::vector<int> returnedItems;

public:
    Member(int memberId) : memberId(memberId) {}

    int getMemberId() const {
        return memberId;
    }

    const std::vector<int>& getBorrowedItems() const {
        return borrowedItems;
    }

    const std::vector<int>& getReturnedItems() const {
        return returnedItems;
    }

    void borrowItem(int itemId) {
        borrowedItems.push_back(itemId);
    }

    void returnItem(int itemId) {
        returnedItems.push_back(itemId);
    }
};

class Library {
private:
    std::vector<Item*> items;
    std::vector<Member> members;
    int lastMemberId;

public:
    Library() : lastMemberId(1000) {}

    ~Library() {
        for (Item* item : items) {
            delete item;
        }
    }

    void addBook(const std::string& title, const std::string& author, int quantity) {
        for (int i = 0; i < quantity; ++i) {
            int id = generateItemId();
            Book* newBook = new Book(title, id, author);
            items.push_back(newBook);
            std::cout << "Book added successfully. ID: " << id << "\n";
        }
    }

    void addMagazine(const std::string& title, int quantity) {
        for (int i = 0; i < quantity; ++i) {
            int id = generateItemId();
            Magazine* newMagazine = new Magazine(title, id);
            items.push_back(newMagazine);
            std::cout << "Magazine added successfully. ID: " << id << "\n";
        }
    }

    void displayItems() {
        if (items.empty()) {
            std::cout << "No items available in the library.\n";
            return;
        }

        std::cout << "Library Items:\n";
        std::cout << "-------------------------------------------------------------------------------\n";
        std::cout << "| " << std::setw(4) << "ID" << " | " << std::setw(13) << "Title" << std::setw(15) << " | " << std::setw(13) << "Author" << std::setw(15) << " | " << "Availability" << " |\n";
        std::cout << "-------------------------------------------------------------------------------\n";
        for (const auto& item : items) {
            item->displayInfo();
        }
        std::cout << "-------------------------------------------------------------------------------\n";
    }

    int generateItemId() {
        return items.size() + 1;
    }

    void borrowItem(int itemId, int memberId) {
        for (Item* item : items) {
            if (item->getId() == itemId) {
                if (auto book = dynamic_cast<Book*>(item)) {
                    if (book->getIsAvailable()) {
                        book->setAvailability(false);
                        book->setBorrower(memberId);
                        members[memberId - 1001].borrowItem(itemId);
                        std::cout << "Item with ID " << itemId << " borrowed successfully by Member ID " << memberId << ".\n";
                        return;
                    } else {
                        std::cout << "Item with ID " << itemId << " is not available for borrowing.\n";
                    }
                } else if (dynamic_cast<Magazine*>(item)) {
                    std::cout << "Magazines cannot be borrowed.\n";
                }
                return;
            }
        }
        std::cout << "Item with ID " << itemId << " not found.\n";
    }

    void returnItem(int itemId, int memberId) {
        for (Item* item : items) {
            if (item->getId() == itemId) {
                if (auto book = dynamic_cast<Book*>(item)) {
                    if (!book->getIsAvailable() && book->getBorrowerId() == memberId) {
                        book->setAvailability(true);
                        book->setBorrower(-1);
                        members[memberId - 1001].returnItem(itemId);
                        std::cout << "Item with ID " << itemId << " returned successfully by Member ID " << memberId << ".\n";
                        return;
                    } else {
                        std::cout << "Item with ID " << itemId << " is not borrowed by Member ID " << memberId << ".\n";
                    }
                } else if (dynamic_cast<Magazine*>(item)) {
                    std::cout << "Magazines cannot be returned.\n";
                }
                return;
            }
        }
        std::cout << "Item with ID " << itemId << " not found.\n";
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

            const std::vector<int>& borrowedItems = member.getBorrowedItems();
            const std::vector<int>& returnedItems = member.getReturnedItems();

            if (!borrowedItems.empty() || !returnedItems.empty()) {
                std::cout << "Borrowed Items:\n";
                std::cout << "-----------------\n";
                std::cout << "|  ID  |   Title   |\n";
                std::cout << "-----------------\n";
                for (const auto& itemId : borrowedItems) {
                    for (const auto& item : items) {
                        if (item->getId() == itemId) {
                            std::cout << "| " << std::setw(4) << item->getId() << " | " << std::setw(10) << item->getTitle().substr(0, 10) << " |\n";
                        }
                    }
                }
                for (const auto& itemId : returnedItems) {
                    for (const auto& item : items) {
                        if (item->getId() == itemId) {
                            std::cout << "| " << std::setw(4) << item->getId() << " | " << std::setw(10) << item->getTitle().substr(0, 10) << " |\n";
                        }
                    }
                }
                std::cout << "-----------------\n";
            } else {
                std::cout << "No items borrowed or returned.\n";
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
        std::cout << "1. Display Items\n";
        std::cout << "2. Borrow Item\n";
        std::cout << "3. Return Item\n";
        std::cout << "4. Add Book\n";
        std::cout << "5. Add Magazine\n";
        std::cout << "6. Register Member\n";
        std::cout << "7. Print Library Card\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                library.displayItems();
                break;
            case 2: {
                int itemId, memberId;
                std::cout << "Enter the ID of the item you want to borrow: ";
                std::cin >> itemId;
                std::cout << "Enter your Member ID: ";
                std::cin >> memberId;
                library.borrowItem(itemId, memberId);
                break;
            }
            case 3: {
                int itemId, memberId;
                std::cout << "Enter the ID of the item you want to return: ";
                std::cin >> itemId;
                std::cout << "Enter your Member ID: ";
                std::cin >> memberId;
                library.returnItem(itemId, memberId);
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
            case 5: {
                std::string title;
                int quantity;
                std::cout << "Enter magazine title: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, title);
                std::cout << "Enter quantity: ";
                std::cin >> quantity;
                library.addMagazine(title, quantity);
                break;
            }
            case 6:
                library.registerMember();
                break;
            case 7: {
                int memberId;
                std::cout << "Enter Member ID to print library card: ";
                std::cin >> memberId;
                library.printLibraryCard(memberId);
                break;
            }
            case 8:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}
