# Simple Bank Management System

A simple procedural C++ application for managing bank client records using file-based storage. This project demonstrates functional decomposition, menu-driven user interaction, and basic text file operations without using object-oriented programming.

## Project Description

The Simple Bank Management System allows users to manage client accounts through a console application. Client information is stored in a plain text file named `Clients.example.txt`.

The application supports viewing client records, creating new accounts, deleting clients, updating account details, searching by account number, and performing deposit/withdraw transactions.

## Features

- Show full client list
- Add new client records
- Delete existing clients
- Update client information
- Search for a client by account number
- Deposit money into a client account
- Withdraw money from a client account
- Calculate and display total balances for all clients
- Menu-driven console interface

## Technologies Used

- C++
- Standard library headers: `<iostream>`, `<fstream>`, `<string>`, `<vector>`, `<iomanip>`, `<limits>`, `<ctime>`, `<cstdlib>`, `<cctype>`
- Visual Studio C++ project format (`.vcxproj` and `.slnx`)

## Programming Concepts

- Procedural programming
- Functional decomposition with reusable functions
- File I/O using text files
- Data parsing with string splitting
- Enumerations for menu options
- Error checking for user input
- Separation of concerns across utility headers
- Text-based data storage and serialization

## Project Structure

- `Bank1_Project/Bank1_Project.cpp` - Main application logic, menu handling, and client operations
- `Bank1_Project/NexaFile.h` - File utility functions for reading, writing, deleting, and updating records
- `Bank1_Project/NexaInput.h` - User input helper functions for safe numeric and string input
- `Bank1_Project/NexaProcessing.h` - Miscellaneous helper functions and table output formatting
- `Bank1_Project/NexaString.h` - String utility functions for case conversion and splitting/joining text
- `Bank1_Project/Clients.example.txt` - Sample client data for reference and testing
- `Bank1_Project.slnx` - Visual Studio solution file
- `Bank1_Project/Bank1_Project.vcxproj` - Visual Studio C++ project file

## How to Build and Run

### Using Visual Studio

1. Open `Bank1_Project.slnx` in Visual Studio.
2. Set the build configuration to `Debug` or `Release`.
3. Build the solution.
4. Run the project from Visual Studio.


## Sample Main Menu

```text
====================================================
		Main Menu Screen
====================================================
	[1] Show Client List
	[2] Add New Client
	[3] Delete Client
	[4] Update Client Info
	[5] Find Client
	[6] TransActions
	[7] Exit
====================================================
```

### Transactions Menu

```text
====================================================
		Transactions Menu Screen
====================================================
	[1] Deposit
	[2] Withdraw
	[3] Total Balances
	[4] Main Menu
====================================================
```

## Learning Objectives

- Understand how to structure a procedural C++ program with modular functions
- Practice reading and writing structured data to a text file
- Implement a simple command-line menu system
- Work with basic data validation and user input handling
- Apply string parsing and formatting for record serialization
- Manage simple account transactions and updates without OOP

## Future Improvements

- Add support for account authentication and secure PIN handling
- Implement record validation and better error messages
- Add date/time logging for transactions
- Migrate storage to a CSV format or lightweight database
- Improve input handling and menu navigation
- Add configurable backup and restore functionality
- Refactor into an object-oriented design for scalability


