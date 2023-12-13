# Contact Management System

This is a simple command-line contact management system written in C++. It allows users to add contacts, search for contacts by mobile number, search for contacts by name, and exit the program. Contacts are stored in a fixed location on the system, persisting across different program sessions.

## Features

- **Add Contact:** Users can add a new contact by providing details such as first name, last name, address, and mobile number.

- **Search by Mobile Number:** Users can search for a contact by entering the mobile number.

- **Search by Name:** Users can search for a contact by entering the first name and last name.

- **Persistence:** Contacts are stored in a dedicated directory, ensuring that they persist across different program sessions.



## Assumptions

- **While adding Contacts the username should be unique along with the phone number** 

- **Mobile number must be exactly 10 digits only**

- **First Name and Last Name should not be more than 8 characters**

- **Address should not be an empty string**


## How to Use

1. **Install XCode IDE:**
   - Compile the code using XCode.
   ```bash
      xcode-select-install

2. **Build & run the Code:**
   - Open the 'xcodeproj' file in Xcode and Run the application. (cmd + R).

   ```bash
   Addressbook.xcodeproj
   
3. **Use the Contact Management System::**
   - Follow the on-screen instructions & assumptions to perform actions such as adding contacts, searching by mobile number, searching by name, and exiting the program.

## Dependencies
- C++ Standard Library
- Headers for filesystem operations
  
