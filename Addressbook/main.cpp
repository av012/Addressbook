//
//  main.cpp
//  Addressbook
//
//  Created by Avinash Sai Sriramoju on 12/12/23.
//
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cctype>

namespace fs = std::filesystem;

struct Contact {
    std::string firstName;
    std::string lastName;
    std::string address;
    std::string mobileNumber;
};

class ContactManager {
public:
    const size_t maxNameLength = 8;

    void addContact(const Contact& contact) {
        
        if (isValidMobileNumber(contact.mobileNumber) &&
            isValidAlphaString(contact.firstName) &&
            isValidAlphaString(contact.lastName) &&
            isValidString(contact.address) &&
            isValidLength(contact.firstName, maxNameLength) &&
            isValidLength(contact.lastName, maxNameLength)) {

            std::string contactPathByNumber = createContactPath(contact.mobileNumber);
            std::string contactPathByName = createContactPathByName(contact.firstName + contact.lastName);

            std::ofstream fileByNumber(contactPathByNumber + "/contact.json");
            std::ofstream fileByName(contactPathByName + "/contact.json");

            if (fileByNumber.is_open() && fileByName.is_open()) {
                writeContactToFile(fileByNumber, contact);
                writeContactToFile(fileByName, contact);
                std::cout << "Contact added successfully!\n";
            } else {
                std::cerr << "Error creating contact files.\n";
            }
        } else {
            std::cerr << "Invalid input. Please ensure that mobile number is valid, and first name, last name, and address are not empty, contain only letters, and are limited to 8 characters.\n";
        }
    }

    void searchContact(const std::string& mobileNumber) {
        if (isValidMobileNumber(mobileNumber)) {
            std::string contactPath = createContactPath(mobileNumber) + "/contact.json";
            if (fs::exists(contactPath)) {
                std::ifstream file(contactPath);
                if (file.is_open()) {
                    std::cout << "Contact found:\n";
                    std::cout << file.rdbuf();
                } else {
                    std::cerr << "Error reading contact file.\n";
                }
            } else {
                std::cout << "Contact not found for mobile number: " << mobileNumber << "\n";
            }
        } else {
            std::cerr << "Invalid mobile number. Please enter a 10-digit number not starting with 0.\n";
        }
    }

    void searchContactByName(const std::string& firstName, const std::string& lastName) {
        
        if (isValidAlphaString(firstName) && isValidAlphaString(lastName)) {
                   std::string combinedName = firstName + lastName;
                   std::string contactPath = createContactPathByName(combinedName) + "/contact.json";

                   if (fs::exists(contactPath)) {
                       std::ifstream file(contactPath);
                       if (file.is_open()) {
                           std::cout << "Contact found:\n";
                           std::cout << file.rdbuf();
                       } else {
                           std::cerr << "Error reading contact file.\n";
                       }
                   } else {
                       std::cout << "Contact not found for name: " << combinedName << "\n";
                   }
               } else {
                   std::cerr << "Invalid names. Please ensure that first name and last name contain only letters.\n";
               }
    }

    bool isValidMobileNumber(const std::string& mobileNumber) const {
        return mobileNumber.length() == 10 && mobileNumber[0] != '0';
    }

    bool isValidAlphaString(const std::string& str) const {
        if (str.empty()) {
            return false;
        }
        for (char ch : str) {
            if (!std::isalpha(static_cast<unsigned char>(ch))) {
                return false;
            }
        }
        return true;
    }

    bool isValidLength(const std::string& str, size_t maxLength) const {
        return str.length() <= maxLength;
    }

    bool isValidString(const std::string& str) const {
        return !str.empty();
    }

private:
    
    void writeContactToFile(std::ofstream& file, const Contact& contact) const {
        file << "{\n";
        file << "  \"firstName\": \"" << contact.firstName << "\",\n";
        file << "  \"lastName\": \"" << contact.lastName << "\",\n";
        file << "  \"address\": \"" << contact.address << "\",\n";
        file << "  \"mobileNumber\": \"" << contact.mobileNumber << "\"\n";
        file << "}\n";
    }
    
    std::string createContactPath(const std::string& mobileNumber) const {
        std::string contactPath = baseDirectory;
        for (char digit : mobileNumber) {
            contactPath += "/" + std::string(1, digit);
        }
        return contactPath;
    }

    std::string createContactPathByName(const std::string& combinedName) const {
        std::string contactPathByName = baseDirectory;
        for (char ch : combinedName) {
            contactPathByName += "/" + std::string(1, std::tolower(ch));
        }
        return contactPathByName;
    }

private:
    const std::string baseDirectory = "contacts";
};

int main() {
    ContactManager contactManager;

    while (true) {
        std::cout << "\n1. Add Contact\n";
        std::cout << "2. Search Contact by Mobile Number\n";
        std::cout << "3. Search Contact by Name\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();  // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
            std::cout << "Invalid input. Please enter a number.\n";
            continue;  // Restart the loop
        }

        switch (choice) {
            case 1: {
                Contact newContact;
                do {
                    std::cout << "Enter First Name (up to 8 characters): ";
                    std::cin >> newContact.firstName;
                } while (!contactManager.isValidAlphaString(newContact.firstName) || !contactManager.isValidLength(newContact.firstName, contactManager.maxNameLength));

                do {
                    std::cout << "Enter Last Name (up to 8 characters): ";
                    std::cin >> newContact.lastName;
                } while (!contactManager.isValidAlphaString(newContact.lastName) || !contactManager.isValidLength(newContact.lastName, contactManager.maxNameLength));

                do {
                    std::cout << "Enter Address: ";
                    std::cin.ignore();  // to consume the newline character
                    std::getline(std::cin, newContact.address);
                } while (!contactManager.isValidString(newContact.address));

                std::string mobileNumber;
                do {
                    std::cout << "Enter Mobile Number (10 digits, not starting with 0): ";
                    std::cin >> mobileNumber;
                } while (!contactManager.isValidMobileNumber(mobileNumber));

                newContact.mobileNumber = mobileNumber;

                contactManager.addContact(newContact);
                break;
            }
            case 2: {
                std::string mobileNumber;
                do {
                    std::cout << "Enter Mobile Number to search (10 digits, not starting with 0): ";
                    std::cin >> mobileNumber;
                } while (!contactManager.isValidMobileNumber(mobileNumber));

                contactManager.searchContact(mobileNumber);
                break;
            }
            case 3: {
                Contact searchContact;
                std::cout << "Enter First Name: ";
                std::cin >> searchContact.firstName;

                std::cout << "Enter Last Name: ";
                std::cin >> searchContact.lastName;

                contactManager.searchContactByName(searchContact.firstName, searchContact.lastName);
                break;
            }
            case 4:
                std::cout << "Exiting the program. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

