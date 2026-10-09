\# systemPracownikow



\## Description



My project is basically a simple employee management system. You can add, search for, modify and delete employees. Each employee has several attributes, such as name, type, salary and working hours.



\## Features

* Display all employee details
* Add employees
* Search for employees based on various criteria
* Remove employee
* Sort employees
* Modify employee details
* Count employees based on various criteria
* Find the best-performing employee
* Display employees based on various criteria
* Modify details of all employees
* Modify details of specific groups of employees
* Save employee data to a file
* Load employee data from a file
* Validate employee data loaded from a file
* Handle invalid and duplicate employee records





\## Technologies

* C++
* Object-Oriented Programming (OOP)
* Polymorphism
* Smart pointers
* STL
* File I/O ('fstream')
* Structs
* Enum classes
* Templates
* Lambda Expressions
* Input and Data Validation





\## Project Structure

* &#x20;`Pracownik` - responsible for the employee's core structure and behaviour
* &#x20;`Pracownicy` - manages the collection of employees and provides operations for working with them
* &#x20;`Menu` - handles interaction with the user
* &#x20;`Parser` - parses and validates data loaded from a file
* &#x20;`Input` - handles and validates user input
* `TypPracownika` - defines the available employee types





\## Data Storage

* &#x20;Employee data is stored in a `.txt` file.
* &#x20;Each employee's data is stored in a predefined order, with individual fields separated by `|`.
* &#x20;The first line of the file represents the highest ID ever used, allowing the application to generate unique IDs.
* &#x20;Invalid data is detected while loading the file and stored in a separate container of invalid records.



\## How to Run



1\. Open the project in a C++ IDE.

2\. Build the project.

3\. Run the application.



\## What i Learned



While working on this project, I learned the principles of object-oriented programming (OOP) and how to work with smart pointers, raw pointers, and iterators. The most important takeaway was understanding what the development process of a project should look like, from start to finish. I also learned how important debugging and testing are when developing a larger application.



\## Author



Kamil Sojkowski

