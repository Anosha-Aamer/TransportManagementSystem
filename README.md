# Transport Management System (TMS)

A robust Transport Management System implemented in C++ that manages Customers, Drivers, Vehicles, and Services (Rides & Deliveries). This project demonstrates advanced object-oriented programming concepts, dynamic memory management, and file I/O in C++. It provides an interactive console-menu interface allowing users to manage transport operations effectively.

---

## Features

- Manage Customers, Drivers, Vehicles, and their associated Services.
- Add new customers, drivers, and vehicles dynamically.
- Track booking histories for customers and drivers.
- Handle different types of services: Ride and Delivery.
- Maintain driver licenses, experience, ranking, and salary.
- Support service lifecycle: booking, completion, cancellation.
- Search and filter:
  - Drivers by ranking and license count.
  - Pending and canceled services.
  - Customers who used the same vehicle on different dates.
  - Delivery drivers completing deliveries on the same days.
- Persist data to files and load from files (`customers.txt`, `drivers.txt`, `vehicles.txt`, `services.txt`).
- Interactive console menu for ease of use.

---

## Project Structure

- **Person, Name, Date, Time Classes**: Basic classes for handling personal info and date/time records.
- **Customer, Driver, Vehicle Classes**: Represent entities with details and history.
- **Service Class and Subclasses (Ride, Delivery)**: Abstract and concrete service types with specific attributes.
- **TMS Class**: Core manager handling collections of customers, drivers, vehicles and services, plus file operations and business logic.
- **Main Function**: Provides a console menu to interact with the TMS.

---

## Usage

On running the program, you will see a menu with options such as:

1. Add a New Customer  
2. Add a Driver  
3. Add a Vehicle  
4. Print List of All Customers  
5. Print List of All Drivers  
6. Print Complete List of Vehicles  
7. Print Complete Details of a Particular Vehicle  
8. Print Complete History of a Particular Customer  
9. Print Complete History of a Driver  
10. Print List of All Drivers Who Have Ranking Above 4.5  
11. Print List of All Drivers with Multiple Licenses  
12. Print Updated Salary of All Drivers Based on Updated Ranking  
13. Add a Service Request (Ride or Delivery)  
14. Cancel a Booking  
15. Complete a Service  
16. Print Details of All Customers Who Used the Same Vehicle on Different Dates  
17. Print List of All Drivers Who Completed Delivery Services on Same Days  
18. Print Details of All Pending Services on a Particular Date  
19. Print Details of All Pending Services of a Particular Driver  
20. Print Details of All Canceled Services by a Customer  
21. Load Services from File  
22. Save Services to File  
23. Exit

- Simply enter the corresponding number to perform the action.
- Follow on-screen prompts to enter any required information.

---

## Author

Developed by Anosha Aamer

---

## Acknowledgments

- Inspired by standard transport management problems and object-oriented design principles.
- Incorporates practices for dynamic memory management and polymorphism in C++.


