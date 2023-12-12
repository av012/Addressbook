# Contact Management System

This is a simple command-line contact management system written in C++. It allows users to add contacts, search for contacts by mobile number, search for contacts by name, and exit the program. Contacts are stored in a fixed location on the system, persisting across different program sessions.

## Features

- **Add Contact:** Users can add a new contact by providing details such as first name, last name, address, and mobile number.

- **Search by Mobile Number:** Users can search for a contact by entering the mobile number.

- **Search by Name:** Users can search for a contact by entering the first name and last name.

- **Persistence:** Contacts are stored in a dedicated directory, ensuring that they persist across different program sessions.

## How to Use

1. **Compile the Code:**
   - Compile the code using a C++ compiler (e.g., g++).
   ```bash
   g++ -std=c++17 -o addressbook main.cpp
   
2. **Run the Executable::**
   - Run the compiled executable.
   ```bash
   ./addressbook

3. **Use the Contact Management System::**
   - Follow the on-screen instructions to perform actions such as adding contacts, searching by mobile number, searching by name, and exiting the program.

## Dependencies
- C++ Standard Library
- '<filesystem>' header for filesystem operations
  
