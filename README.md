# ComedyDataEntry
Comedy Data Entry is a C++ program that manages a database of comedians who have appeared on the show “Kill Tony.” The program allows users to read from and append new information to an existing CSV file.

### Features
CSV Data Handling: Read data from a CSV file and display it in a user-friendly format.

Data Entry: Append new information to the CSV file, expanding the database with new comedians.

Simple CLI Interface: The program is easy to use with straightforward command-line prompts.

### Technologies Used
C++: The core logic of the program, including file handling, is implemented in C++.

CSV File: The program operates on a CSV file that stores the database of comedians.

### Usage
Reading Data:

Upon running the program, it will read and display the existing data from the comedians.csv file.
Adding Data:

The program will prompt you to enter new information about comedians. This data will be appended to the comedians.csv file.
Exiting:

After adding new data, you can exit the program, and the CSV file will be saved with the new entries.

#### Code Structure
ComedyDataEntry.cpp: Contains all the logic for reading from and writing to the CSV file.

comedians.csv: The CSV file that acts as the database for storing comedians' information.
