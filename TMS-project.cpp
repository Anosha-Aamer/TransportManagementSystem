#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

class Name
{
private:
    char* fName;
    char* lName;

public:
    Name() : fName(nullptr), lName(nullptr) {}
    Name(const char* fN, const char* lN)
    {
        if (fN != nullptr)
        {
            fName = new char[strlen(fN) + 1];
            strcpy_s(fName, strlen(fN) + 1, fN);

        }
        else
        {
            fName = nullptr; // Handle null case
        }
        if (lN != nullptr)
        {
            lName = new char[strlen(lN) + 1];
            strcpy_s(lName, strlen(lN) + 1, lN);

        }
        else
        {
            lName = nullptr; // Handle null case
        }
    }

    Name(const Name& other)
    {
        fName = other.fName ? new char[strlen(other.fName) + 1] : nullptr;
        if (fName)
            strcpy_s(fName, strlen(other.fName) + 1, other.fName);


        lName = other.lName ? new char[strlen(other.lName) + 1] : nullptr;
        if (lName)
            strcpy_s(lName, strlen(other.lName) + 1, other.lName);

    }

    Name& operator=(const Name& other)
    {
        if (this != &other)
        {
            delete[] fName; // Free existing memory
            delete[] lName; // Free existing memory

            fName = other.fName ? new char[strlen(other.fName) + 1] : nullptr;
            if (fName)
                strcpy_s(fName, strlen(other.fName) + 1, other.fName);


            lName = other.lName ? new char[strlen(other.lName) + 1] : nullptr;
            if (lName)
                strcpy_s(lName, strlen(other.lName) + 1, other.lName);

        }
        return *this;
    }

    ~Name()
    {
        delete[] fName;
        delete[] lName;
    }

    void setFirstName(const char* fN)
    {
        delete[] fName;
        fName = new char[strlen(fN) + 1];
        strcpy_s(fName, strlen(fN) + 1, fN);

    }

    void setLastName(const char* lN)
    {
        delete[] lName;
        lName = new char[strlen(lN) + 1];
        strcpy_s(lName, strlen(lN) + 1, lN);

    }

    char* getFirstName() const { return fName; }
    char* getLastName() const { return lName; }

    friend ostream& operator<<(ostream& out, const Name& n)
    {
        out << n.fName << " " << n.lName;
        return out;
    }
};

class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date() : day(0), month(0), year(0) {}
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    void setDate(int d, int m, int y)
    {
        day = d;
        month = m;
        year = y;
    }

    void getDate(int& d, int& m, int& y) const
    {
        d = day;
        m = month;
        y = year;
    }

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    friend ostream& operator<<(ostream& out, const Date& d)
    {
        out << d.day << "/" << d.month << "/" << d.year;
        return out;
    }
};

class mTime
{
private:
    int hour;
    int min;
    int sec;

public:
    mTime() : hour(0), min(0), sec(0) {}
    mTime(int h, int m, int s) : hour(h), min(m), sec(s) {}

    void setTime(int h, int m, int s)
    {
        hour = h;
        min = m;
        sec = s;
    }

    void getTime(int& h, int& m, int& s) const
    {
        h = hour;
        m = min;
        s = sec;
    }

    friend ostream& operator<<(ostream& out, const mTime& t)
    {
        out << t.hour << ":" << t.min << ":" << t.sec;
        return out;
    }
};

class Person
{
protected:
    Name pName;
    Date DOB;
    int age;
    int Nid; // National ID

public:
    Person() : pName(), DOB(), age(0), Nid(0) {}

    Person(const char* fName, const char* lName, int day, int month, int year, int nid, int a)
        : pName(fName, lName), DOB(day, month, year), Nid(nid), age(a) {}

    void setName(const char* fName, const char* lName) { pName = Name(fName, lName); }
    void setDOB(int day, int month, int year) { DOB.setDate(day, month, year); }
    void setAge(int a) { age = a; }
    void setNid(int nid) { Nid = nid; }

    const Name& getName() const { return pName; }
    const Date& getDOB() const { return DOB; }
    int getAge() const { return age; }
    int getNid() const { return Nid; }

    virtual void displayDetails() const
    {
        cout << "Name: " << pName << ", DOB: " << DOB << ", Age: " << age << ", National ID: " << Nid << endl;
    }
};

class Service {
protected:
    char* source;
    char* destination;
    float distance;    // in km
    Date bookingDate;  // Assume Date class exists with setDate method
    mTime bookingTime; // Assume mTime class exists
    bool status;       // false for pending, true if complete
    float fuelRate;
    int cId; // Customer Id who booked the ride
    int dId; // Driver Id
    int vId; // Vehicle Id
    int id;  // Combined ID (defined dynamically)

    void calculateId() {
        id = (cId * 10000) + (vId * 100) + dId; // Unique formula for ID
    }

public:
    // Default Constructor
    Service()
        : source(nullptr), destination(nullptr), distance(0), status(false),
        fuelRate(0), cId(-1), dId(-1), vId(-1), id(-1) {}

    // Parameterized Constructor
    Service(const char* src, const char* dest, float dist, float fuel, int customerId, int day, int month, int year)
        : distance(dist), fuelRate(fuel), cId(customerId), dId(-1), vId(-1), status(false) {
        source = src ? new char[strlen(src) + 1] : nullptr;
        if (source) strcpy_s(source, strlen(src) + 1, src);

        destination = dest ? new char[strlen(dest) + 1] : nullptr;
        if (destination) strcpy_s(destination, strlen(dest) + 1, dest);

        bookingDate.setDate(day, month, year);
        calculateId(); // Initialize the ID
    }

    // Copy Constructor
    Service(const Service& other)
        : distance(other.distance), fuelRate(other.fuelRate), cId(other.cId),
        dId(other.dId), vId(other.vId), status(other.status), bookingDate(other.bookingDate) {
        source = other.source ? new char[strlen(other.source) + 1] : nullptr;
        if (source) strcpy_s(source, strlen(other.source) + 1, other.source);

        destination = other.destination ? new char[strlen(other.destination) + 1] : nullptr;
        if (destination) strcpy_s(destination, strlen(other.destination) + 1, other.destination);

        id = other.id;
    }

    // Assignment Operator
    Service& operator=(const Service& other) {
        if (this != &other) {
            delete[] source;
            delete[] destination;

            distance = other.distance;
            fuelRate = other.fuelRate;
            cId = other.cId;
            dId = other.dId;
            vId = other.vId;
            status = other.status;
            id = other.id;
            bookingDate = other.bookingDate;

            source = other.source ? new char[strlen(other.source) + 1] : nullptr;
            if (source) strcpy_s(source, strlen(other.source) + 1, other.source);

            destination = other.destination ? new char[strlen(other.destination) + 1] : nullptr;
            if (destination) strcpy_s(destination, strlen(other.destination) + 1, other.destination);
        }
        return *this;
    }

    // Destructor
    ~Service() {
        delete[] source;
        delete[] destination;
    }

    // Setters
    void setBookingDate(int day, int month, int year) {
        bookingDate.setDate(day, month, year);
    }
    void setStatus(bool stat) { status = stat; }
    void setDriverId(int id) { dId = id; calculateId(); }
    void setVehicleId(int id) { vId = id; calculateId(); }

    // Getters
    bool getStatus() const { return status; }
    int getCustomerId() const { return cId; }
    int getDriverId() const { return dId; }
    int getVehicleId() const { return vId; }
    const char* getSource() const { return source; }
    const char* getDestination() const { return destination; }
    float getDistance() const { return distance; }
    float getFuelRate() const { return fuelRate; }
    const Date& getBookingDate() const { return bookingDate; }
    int getId() const { return id; }

    // Display Details
    virtual void displayServiceDetails() const {
        cout << "Source: " << (source ? source : "N/A")
            << ", Destination: " << (destination ? destination : "N/A")
            << ", Distance: " << distance << " km, Status: " << (status ? "Complete" : "Pending")
            << ", Booking Date: " << bookingDate << endl; //  Date has an appropriate operator<<
    }

    // Stream Output Operator
    friend ostream& operator<<(ostream& out, const Service& service) {
        out << "Service from " << (service.source ? service.source : "N/A")
            << " to " << (service.destination ? service.destination : "N/A")
            << ", Distance: " << service.distance << " km, Status: " << (service.status ? "Complete" : "Pending")
            << ", Booking Date: " << service.bookingDate; // Date has an appropriate operator<<
        return out;
    }
};

class Ride : public Service
{
private:
    int noofPassengers;   // Number of passengers
    char* rideType;       // Ride type (e.g., intercity, intracity)
    float driverRanking;  // Driver ranking (0 to 5 scale)
    float vehicleRanking; // Vehicle ranking (0 to 5 scale)

public:
    // Constructor
    Ride(const char* src, const char* dest, float dist, int passengers, const char* type,
        float fuel, int customerId, int day, int month, int year, float driverRank, float vehicleRank)
        : Service(src, dest, dist, fuel, customerId, day, month, year),
        noofPassengers(passengers),
        driverRanking(driverRank),
        vehicleRanking(vehicleRank)
    {
        if (type != nullptr)
        {
            rideType = new char[strlen(type) + 1];
            strcpy_s(rideType, strlen(type) + 1, type);

        }
        else
        {
            rideType = nullptr; // Handle null case
        }
    }

    // Copy Constructor
    Ride(const Ride& other) : Service(other),
        noofPassengers(other.noofPassengers),
        driverRanking(other.driverRanking),
        vehicleRanking(other.vehicleRanking)
    {
        rideType = other.rideType ? new char[strlen(other.rideType) + 1] : nullptr;
        if (rideType)
            strcpy_s(rideType, strlen(other.rideType) + 1, other.rideType);

    }

    // Assignment Operator
    Ride& operator=(const Ride& other)
    {
        if (this != &other)
        {
            Service::operator=(other); // Call base class assignment
            delete[] rideType;         // Free existing memory
            rideType = other.rideType ? new char[strlen(other.rideType) + 1] : nullptr;
            if (rideType)
                strcpy_s(rideType, strlen(other.rideType) + 1, other.rideType);

            noofPassengers = other.noofPassengers;
            driverRanking = other.driverRanking;
            vehicleRanking = other.vehicleRanking;
        }
        return *this;
    }

    // Getters for rankings
    float getDriverRanking() const { return driverRanking; }
    float getVehicleRanking() const { return vehicleRanking; }

    // Destructor
    ~Ride()
    {
        delete[] rideType;
    }

    // Display Service Details
    void displayServiceDetails() const override
    {
        Service::displayServiceDetails();
        cout << "Ride Type: " << (rideType ? rideType : "N/A")
            << ", Passengers: " << noofPassengers
            << ", Driver Ranking: " << driverRanking
            << ", Vehicle Ranking: " << vehicleRanking << endl;
    }
};

class Delivery : public Service
{
private:
    float goodsWeight; // Weight of goods
    char* goodsType;   // Type of goods

public:
    Delivery(const char* src, const char* dest, float dist, float weight, const char* type, float fuel, int customerId, int day, int month, int year)
        : Service(src, dest, dist, fuel, customerId, day, month, year), goodsWeight(weight)
    {
        if (type != nullptr)
        {
            goodsType = new char[strlen(type) + 1];
            strcpy_s(goodsType, strlen(type) + 1, type);

        }
        else
        {
            goodsType = nullptr; // Handle null case
        }
    }

    Delivery(const Delivery& other) : Service(other), goodsWeight(other.goodsWeight)
    {
        goodsType = other.goodsType ? new char[strlen(other.goodsType) + 1] : nullptr;
        if (goodsType)
            goodsType = new char[strlen(other.goodsType) + 1];

    }

    Delivery& operator=(const Delivery& other)
    {
        if (this != &other)
        {
            Service::operator=(other); // Call base class assignment
            delete[] goodsType;        // Free existing memory
            goodsType = other.goodsType ? new char[strlen(other.goodsType) + 1] : nullptr;
            if (goodsType)
                strcpy_s(goodsType, strlen(other.goodsType) + 1, other.goodsType);

            goodsWeight = other.goodsWeight;
        }
        return *this;
    }

    ~Delivery()
    {
        delete[] goodsType;
    }

    void displayServiceDetails() const override
    {
        Service::displayServiceDetails();
        cout << "Goods Type: " << goodsType << ", Weight: " << goodsWeight << " kg" << endl;
    }
};

class Customer : public Person
{
private:
    int cId;                          // Unique ID for the customer
    vector<Service*> bookingHistory; // Maintain history of services

public:
    Customer(const char* fName, const char* lName, int day, int month, int year, int nid, int a, int id)
        : Person(fName, lName, day, month, year, nid, a), cId(id) {}

    void addBooking(Service* service)
    {
        bookingHistory.push_back(service);
    }

    void displayDetails() const override
    {
        Person::displayDetails();
        cout << "Customer ID: " << cId << endl;
        cout << "Booking History: " << bookingHistory.size() << " services booked." << endl;
        for (const auto& service : bookingHistory)
        {
            service->displayServiceDetails();
        }
    }

    int getId() const { return cId; }
    const vector<Service*>& getServices() const { return bookingHistory; }
};

class Driver : public Person
{
private:
    int dId;                          // Unique ID for the driver
    char** LicencesList;              // List of licenses
    int noofLicences;                 // Number of licenses
    float overallRanking;             // Overall ranking of the driver
    float salary;                     // Salary of the driver
    int experience;                   // Years of experience
    int status;                       // 1 for free, 2 if booked, 3 if canceled
    vector<Service*> serviceHistory; // Vector of services for tracking complete information

public:
    Driver(const char* fName, const char* lName, int day, int month, int year, int nid, int a, int id)
        : Person(fName, lName, day, month, year, nid, a), dId(id), noofLicences(0), overallRanking(0.0), salary(0.0), experience(0), status(1)
    {
        LicencesList = nullptr; // Initialize LicencesList
    }

    ~Driver()
    {
        for (int i = 0; i < noofLicences; ++i)
        {
            delete[] LicencesList[i]; // Delete each license
        }
        delete[] LicencesList; // Delete the license list

    }
    void setRanking(float ranking) { overallRanking = ranking; }
    void addLicense(const char* license)
    {
        if (license == nullptr)
            return; // Check for null license
        char** newLicencesList = new char* [noofLicences + 1];
        for (int i = 0; i < noofLicences; ++i)
        {
            newLicencesList[i] = LicencesList[i]; // Copy old licenses
        }
        newLicencesList[noofLicences] = new char[strlen(license) + 1];
        strcpy_s(newLicencesList[noofLicences], strlen(license) + 1, license); // Add new license
        delete[] LicencesList;                          // Delete old list
        LicencesList = newLicencesList;                 // Update to new list
        noofLicences++;                                 // Increment license count
    }

    void addService(Service* service)
    {
        serviceHistory.push_back(service); // Add new service to vector
    }

    void displayDetails() const override
    {
        Person::displayDetails();
        cout << "Driver ID: " << dId << ", Overall Ranking: " << overallRanking
            << ", Salary: " << salary << ", Experience: " << experience
            << ", Status: " << (status == 1 ? "Free" : (status == 2 ? "Booked" : "Canceled")) << endl;
        cout << "Licenses: ";
        for (int i = 0; i < noofLicences; ++i)
        {
            cout << LicencesList[i] << " ";
        }
        cout << endl;

        cout << "Service History: " << serviceHistory.size() << " services." << endl;
        for (const auto& service : serviceHistory)
        {
            service->displayServiceDetails(); // Display each service in history
        }
    }

    int getId() const { return dId; }
    float getOverallRanking() const { return overallRanking; }
    int getNumberOfLicenses() const { return noofLicences; }
    int getStatus() const { return status; }
    char** getLicencesList() const
    {
        return LicencesList; // Return the pointer to the list of licenses
    }
    void setStatus(int newStatus) { status = newStatus; }
    void setOverallRanking(float ranking) { overallRanking = ranking; }
    void setSalary(float sal) { salary = sal; }
    void setExperience(int exp) { experience = exp; }
};
class Feature
{
private:
    int fId;
    char* description;
    float cost;

public:
    Feature(int id, const char* desc, float c) : fId(id), cost(c)
    {
        description = new char[strlen(desc) + 1];
        strcpy_s(description, strlen(desc) + 1, desc);
    }

    ~Feature()
    {
        delete[] description;
    }

    void displayFeature() const
    {
        cout << "Feature ID: " << fId << ", Description: " << description << ", Cost: " << cost << endl;
    }
};


class Vehicle
{
private:
    int vId;                               // Vehicle ID
    int registrationNo;                    // Registration number
    float avgMileage;                      // Average mileage
    char* licenseType;                     // License required for driving the vehicle
    bool status;                           // false for free, true if booked
    char* fuelType;                        // Fuel type
    float overallRanking;                  // Overall ranking of the vehicle
    Date manufacturingDate;                // Manufacturing date
    std::vector<Feature*> features;       // Vector for features
    std::vector<Service*> serviceHistory; // Vector for service history

public:
    Vehicle(int id, int regNo, float mileage, const char* lType, const char* fType, const Date& mDate)
        : vId(id), registrationNo(regNo), avgMileage(mileage), status(false), overallRanking(0.0),
        manufacturingDate(mDate)
    {
        licenseType = new char[strlen(lType) + 1];
        strcpy_s(licenseType, strlen(lType) + 1, lType);
        fuelType = new char[strlen(fType) + 1];
        strcpy_s(fuelType, strlen(fType) + 1, fType);
    }

    int getRegistrationNo() const
    {
        return registrationNo;
    }

    // Getter for Average Mileage
    float getAvgMileage() const
    {
        return avgMileage;
    }

    // Getter for License Type
    const char* getLicenseType() const
    {
        return licenseType;
    }

    // Getter for Fuel Type
    const char* getFuelType() const
    {
        return fuelType;
    }

    // Getter for Manufacturing Date
    const Date& getManufacturingDate() const
    {
        return manufacturingDate;
    }

    void addFeature(Feature* feature)
    {
        features.push_back(feature); // Add feature to vector
    }

    void addService(Service* service)
    {
        serviceHistory.push_back(service); // Add service to vector
    }

    void displayDetails() const
    {
        cout << "Vehicle ID: " << vId << ", Registration No: " << registrationNo
            << ", Mileage: " << avgMileage << ", License Type: " << licenseType
            << ", Fuel Type: " << fuelType << ", Status: " << (status ? "Booked" : "Available") << endl;
        cout << "Manufacturing Date: " << manufacturingDate << endl;

        cout << "Features: " << features.size() << endl;
        for (const auto& feature : features)
        {
            feature->displayFeature(); // Display each feature
        }

        cout << "Service History: " << serviceHistory.size() << " services." << endl;
        for (const auto& service : serviceHistory)
        {
            service->displayServiceDetails(); // Display each service in history
        }
    }

    int getId() const { return vId; }

    // Getter for Overall Ranking
    float getOverallRanking() const
    {
        return overallRanking;
    }

    // Setter for Overall Ranking
    void setOverallRanking(float ranking)
    {
        overallRanking = ranking;
    }

    ~Vehicle()
    {
        delete[] licenseType; // Delete the license type
        delete[] fuelType;    // Delete the fuel type

        // Delete features
        for (auto feature : features)
        {
            delete feature; // Delete each feature
        }

        // Delete service history
        for (auto service : serviceHistory)
        {
            delete service; // Delete each service in history
        }
    }
};

class TMS
{
private:
    vector<Customer*> customers;
    vector<Driver*> drivers;
    vector<Vehicle*> vehicles;
    vector<Service*> services;

public:
    TMS() {}

    void loadCustomers(const string& filename)
    {
        ifstream infile(filename);
        if (!infile)
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        char fName[50], lName[50];
        int day, month, year, nid, age, cId;
        while (infile >> fName >> lName >> day >> month >> year >> nid >> age >> cId)
        {
            Customer* newCustomer = new Customer(fName, lName, day, month, year, nid, age, cId);
            addCustomer(newCustomer);
        }
        infile.close();
        cout << "Customers loaded successfully from " << filename << endl;
    }

    void saveCustomers(const string& filename)
    {
        ofstream outfile(filename);
        if (!outfile)
        {
            cerr << "Error opening file for saving customers: " << filename << endl;
            return;
        }

        for (const auto& customer : customers)
        {
            outfile << customer->getName().getFirstName() << " "
                << customer->getName().getLastName() << " "
                << customer->getDOB().getDay() << " "
                << customer->getDOB().getMonth() << " "
                << customer->getDOB().getYear() << " "
                << customer->getNid() << " "
                << customer->getAge() << " "
                << customer->getId() << endl;
        }
        outfile.close();
        cout << "Customers saved successfully to " << filename << endl;
    }

    void loadServices(const std::string& filename)
    {
        std::ifstream infile(filename);
        if (!infile)
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        int serviceId, customerId, driverId, vehicleId, day, month, year;
        std::string source, destination; // Use std::string
        float distance, fuelRate;
        bool status;

        while (infile >> serviceId >> distance >> fuelRate >> customerId >> day >> month >> year >> driverId >> vehicleId >> status)
        {
            getline(infile, source);  // Read the entire source line
            getline(infile, destination);  // Read the entire destination line

            Service* newService = new Service(source.c_str(), destination.c_str(), distance, fuelRate, customerId, day, month, year);
            newService->setDriverId(driverId);
            newService->setVehicleId(vehicleId);
            newService->setStatus(status);
            services.push_back(newService);
        }

        infile.close();
        cout << "Services loaded successfully from " << filename << endl;
    }


    void saveServices(const string& filename)
    {
        ofstream outfile(filename);
        if (!outfile)
        {
            std::cerr << "Error opening file for saving services: " << filename << endl;
            return;
        }

        for (const auto& service : services)
        {
            // Assuming Service has appropriate getter methods
            outfile << service->getId() << " "
                << service->getSource() << " "
                << service->getDestination() << " "
                << service->getDistance() << " "
                << service->getFuelRate() << " "
                << service->getCustomerId() << " "
                << service->getDriverId() << " "
                << service->getVehicleId() << " "
                << service->getStatus() << endl;
        }

        outfile.close();
        cout << "Services saved successfully to " << filename << endl;
    }

    void addCustomer(Customer* customer)
    {
        customers.push_back(customer);
    }

    void addDriver(Driver* driver)
    {
        drivers.push_back(driver);
    }

    void addVehicle(Vehicle* vehicle)
    {
        vehicles.push_back(vehicle);
    }

    void addServiceRequest(int customerId, int driverId, int vehicleId)
    {
        char serviceType;
        cout << "Enter 'R' for Ride or 'D' for Delivery: ";
        cin >> serviceType;

        if (serviceType == 'R' || serviceType == 'r')
        {
            char source[100], destination[100], rideType[50];
            float distance, fuelRate;
            int passengers;

            float driverRanking = 0.0;
            for (Driver* driver : drivers)
            {
                if (driver->getId() == driverId)
                {
                    driverRanking = driver->getOverallRanking();
                    break;
                }
            }

            float vehicleRanking = 0.0;
            for (Vehicle* vehicle : vehicles)
            {
                if (vehicle->getId() == vehicleId)
                {
                    vehicleRanking = vehicle->getOverallRanking();
                    break;
                }
            }
            int day, month, year = 0;

            cout << "Enter Source: ";
            cin >> source;
            cout << "Enter Destination: ";
            cin >> destination;
            cout << "Enter Distance (in km): ";
            cin >> distance;
            cout << "Enter Fuel Rate: ";
            cin >> fuelRate;
            cout << "Enter Number of Passengers: ";
            cin >> passengers;
            cout << "Enter Ride Type: ";
            cin >> rideType;
            cout << "Enter date of delivery (day month year): ";
            cin >> day >> month >> year;

            Ride* newRide = new Ride(source, destination, distance, passengers, rideType, fuelRate, customerId, day, month, year, driverRanking, vehicleRanking);
            if (day < 1 || day > 31 || month < 1 || month > 12 || year < 2023)
            {
                cout << "Invalid date entered. Please try again." << endl;
                delete newRide; // Clean up if invalid
                return;             // Exit the function or loop
            }
            newRide->setDriverId(driverId);
            newRide->setVehicleId(vehicleId);
            services.push_back(newRide); // Add to services vector
            for (Customer* customer : customers)
            {
                if (customer->getId() == customerId)
                {
                    customer->addBooking(newRide);
                    break;
                }
            }
            for (Driver* driver : drivers)
            {
                if (driver->getId() == driverId)
                {
                    driver->addService(newRide);
                    break;
                }
            }
            for (Vehicle* vehicle : vehicles)
            {
                if (vehicle->getId() == vehicleId)
                {
                    vehicle->addService(newRide);
                    break;
                }
            }

            cout << "Ride service request added successfully!" << endl;
        }
        else if (serviceType == 'D' || serviceType == 'd')
        {
            // Collect Delivery-specific details
            char source[100], destination[100], goodsType[50];
            float distance, fuelRate, weight;

            cout << "Enter Source: ";
            cin >> source;
            cout << "Enter Destination: ";
            cin >> destination;
            cout << "Enter Distance (in km): ";
            cin >> distance;
            cout << "Enter Fuel Rate: ";
            cin >> fuelRate;
            cout << "Enter Weight of Goods: ";
            cin >> weight;
            cout << "Enter Goods Type: ";
            cin >> goodsType;

            int day, month, year;

            cout << "Enter date of delivery (day month year): ";
            cin >> day >> month >> year;
            // Create a new Delivery object
            Delivery* newDelivery = new Delivery(source, destination, distance, weight, goodsType, fuelRate, customerId, day, month, year);

            cout << "Enter Booking Date (day month year): ";
            cin >> day >> month >> year;

            if (day < 1 || day > 31 || month < 1 || month > 12 || year < 2023)
            {
                cout << "Invalid date entered. Please try again." << endl;
                delete newDelivery; // Clean up if invalid
                return;             // Exit the function or loop
            }

            newDelivery->setDriverId(driverId);
            newDelivery->setVehicleId(vehicleId);
            services.push_back(newDelivery); // Add to services vector
            for (Customer* customer : customers)
            {
                if (customer->getId() == customerId)
                {
                    customer->addBooking(newDelivery);
                    break;
                }
            }
            for (Driver* driver : drivers)
            {
                if (driver->getId() == driverId)
                {
                    driver->addService(newDelivery);
                    break;
                }
            }
            for (Vehicle* vehicle : vehicles)
            {
                if (vehicle->getId() == vehicleId)
                {
                    vehicle->addService(newDelivery);
                    break;
                }
            }

            cout << "Delivery service request added successfully!" << endl;
        }
        else
        {
            cout << "Invalid service type selected." << endl;
        }
    }

    void displayAllCustomers()
    {
        if (customers.empty())
        {
            cout << "No customers found." << endl;
            return;
        }
        for (Customer* customer : customers) 
        {
            customer->displayDetails();
        }
    }

    void displayAllDrivers()
    {
        if (drivers.empty())
        {
            cout << "No drivers found." << endl;
            return;
        }
        for (Driver* driver : drivers) //range-based for loop
        {
            driver->displayDetails();
        }
    }

    void displayAllVehicles()
    {
        if (vehicles.empty())
        {
            cout << "No vehicles found." << endl;
            return;
        }
        for (Vehicle* vehicle : vehicles)
        {
            vehicle->displayDetails();
        }
    }

    void displayVehicleDetails(int vehicleId)
    {
        for (Vehicle* vehicle : vehicles)
        {
            if (vehicle->getId() == vehicleId)
            {
                vehicle->displayDetails();
                return;
            }
        }
        cout << "Vehicle not found." << endl;
    }

    void displayCustomerHistory(int customerId)
    {
        for (Customer* customer : customers)
        {
            if (customer->getId() == customerId)
            {
                cout << "Customer History:" << endl;
                const auto& services = customer->getServices();
                if (services.empty())
                {
                    cout << "No services found for this customer." << endl;
                }
                else
                {
                    for (Service* service : services)
                    {
                        service->displayServiceDetails();
                    }
                }
                return;
            }
        }
        cout << "Customer not found." << endl;
    }

    void displayDriverHistory(int driverId)
    {
        cout << "Driver History for Driver ID " << driverId << ":" << endl;
        bool found = false;
        for (Service* service : services)
        {
            if (service->getDriverId() == driverId)
            {
                service->displayServiceDetails();
                found = true;
            }
        }
        if (!found)
        {
            cout << "No services found for Driver ID " << driverId << "." << endl;
        }
    }

    void displayTopDrivers(float threshold)
    {
        cout << "Top Drivers (Ranking above " << threshold << "):" << endl;
        for (Driver* driver : drivers)
        {
            if (driver->getOverallRanking() > threshold)
            {
                driver->displayDetails();
            }
        }
    }

    void displayDriversWithMultipleLicenses()
    {
        cout << "Drivers with Multiple Licenses:" << endl;
        for (Driver* driver : drivers)
        {
            if (driver->getNumberOfLicenses() > 1)
            {
                driver->displayDetails();
            }
        }
    }

    void displayUpdatedSalaries()
    {
        cout << "Updated Salaries of Drivers:" << endl;
        for (Driver* driver : drivers)
        {
            // Assuming a method to calculate updated salary exists
            float updatedSalary = driver->getOverallRanking() * 1000; // Placeholder logic
            cout << "Driver ID: " << driver->getId() << ", Updated Salary: " << updatedSalary << endl;
        }
    }

    void cancelBooking(int serviceId, int customerId)
    {
        for (Service* service : services)
        {
            if (service->getVehicleId() == serviceId)
            {
                service->setStatus(false); // Mark as canceled
                // Update customer and driver records accordingly
                cout << "Booking canceled. Customer ID: " << customerId << endl;
                return;
            }
        }
        cout << "Service not found." << endl;
    }

    void printCustomersUsingSameVehicle(int vehicleId)
    {
        cout << "Customers who used Vehicle ID " << vehicleId << ":" << endl;
        for (Customer* customer : customers)
        {
            for (Service* service : customer->getServices())
            {
                if (service->getVehicleId() == vehicleId)
                {
                    customer->displayDetails();
                    break;
                }
            }
        }
    }

    void printDriversCompletedDeliverySameDays()
    {
        map<string, set<int>> deliveryDays; // Maps date to a set of driver IDs
        //The map is used to store dates as keys, and for each date, a set of unique driver IDs is maintained as the value.
        //A set is chosen to automatically handle duplicates, ensuring no driver ID is added more than once for a specific date.

        for (Service* service : services)
        {
            if (Delivery* delivery = dynamic_cast<Delivery*>(service))//no method design in service class so i used dynamic_cast 
            {
                // Assuming you have a method to get the booking date as a string or formatted date
                string dateKey = to_string(delivery->getBookingDate().getDay()) + "/" + to_string(delivery->getBookingDate().getMonth()) + "/" + to_string(delivery->getBookingDate().getYear());
                deliveryDays[dateKey].insert(delivery->getDriverId());//fuction of set ,add element to the set
                //which ensures that therir is not duplication
            }
        }

        for (const auto& entry : deliveryDays)
        {
            cout << "Date: " << entry.first << " - Drivers: ";
            for (int driverId : entry.second)
            {
                cout << driverId << " ";
            }
            cout << endl;
        }
    }

    void printPendingServicesOnDate(int day, int month, int year)
    {
        cout << "Pending Services on " << day << "/" << month << "/" << year << ":" << endl;
        for (Service* service : services)
        {
            if (!service->getStatus())
            {
                // Assuming you have a method to check the date
                if (service->getBookingDate().getDay() == day && service->getBookingDate().getMonth() == month && service->getBookingDate().getYear() == year)
                {
                    cout << *service << endl; // operator<< is overloaded for Service
                }
            }
        }
    }

    void printPendingServicesOfDriver(int driverId)
    {
        cout << "Pending Services for Driver ID " << driverId << ":" << endl;
        for (Service* service : services)
        {
            if (!service->getStatus() && service->getDriverId() == driverId)
            {
                cout << *service << endl;
            }
        }
    }

    void printCanceledServicesByCustomer(int customerId)
    {
        cout << "Canceled Services for Customer ID " << customerId << ":" << endl;
        for (Service* service : services)
        {
            if (!service->getStatus() && service->getCustomerId() == customerId)
            {
                cout << *service << endl;
            }
        }
    }

    void completeService(int serviceId)
    {
        Service* ser = nullptr;
        for (Service* service : services)
        {
            if (service->getId() == serviceId)
            {
                ser = service;
                service->setStatus(true); // Mark as complete
                cout << "Service ID " << serviceId << " has been marked as complete." << endl;
                cout << "Give Rank to the Driver: ";
                float rank;
                cin >> rank;
                for (Driver* driver : drivers)
                {
                    if (driver->getId() == service->getDriverId())
                    {
                        driver->setRanking(rank);
                        break;
                    }
                }
                return;
            }
        }

        cout << "Service ID " << serviceId << " not found." << endl;
    }

    void loadDrivers(const string& filename)
    {
        ifstream infile(filename);
        if (!infile)
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        char fName[50], lName[50], license[50];
        int day, month, year, nid, age, dId;
        while (infile >> fName >> lName >> day >> month >> year >> nid >> age >> dId)
        {
            Driver* newDriver = new Driver(fName, lName, day, month, year, nid, age, dId);
            // Load licenses for the driver
            while (infile >> license && strcmp(license, "done") != 0)
            {
                newDriver->addLicense(license);
            }
            addDriver(newDriver);
        }
        infile.close();
        cout << "Drivers loaded successfully from " << filename << endl;
    }

    void saveDrivers(const string& filename)
    {
        ofstream outfile(filename);
        if (!outfile)
        {
            cerr << "Error opening file for saving drivers: " << filename << endl;
            return;
        }

        for (const auto& driver : drivers)
        {
            outfile << driver->getName().getFirstName() << " "
                << driver->getName().getLastName() << " "
                << driver->getDOB().getDay() << " "
                << driver->getDOB().getMonth() << " "
                << driver->getDOB().getYear() << " "
                << driver->getNid() << " "
                << driver->getAge() << " "
                << driver->getId() << endl;
            // Save licenses
            for (int i = 0; i < driver->getNumberOfLicenses(); ++i)
            {
                outfile << driver->getLicencesList()[i] << " "; // Assuming you have a method to get licenses
            }
            outfile << "done" << endl; // Indicate the end of licenses for this driver
        }
        outfile.close();
        cout << "Drivers saved successfully to " << filename << endl;
    }

    void loadVehicles(const string& filename)
    {
        ifstream infile(filename);
        if (!infile)
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        int vId, regNo;
        float mileage;
        char lType[50], fType[50];
        int day, month, year;

        while (infile >> vId >> regNo >> mileage >> lType >> fType >> day >> month >> year)
        {
            Vehicle* newVehicle = new Vehicle(vId, regNo, mileage, lType, fType, Date(day, month, year));
            addVehicle(newVehicle);
        }
        infile.close();
        cout << "Vehicles loaded successfully from " << filename << endl;
    }
    void getServicesPrinted()
    {
        cout << "ServiceId" << "\t" << "Source" << "\t" << "Destination" << "\t" << "Distance" << "\t" << "FuelRate" << "\t" << "CustomerId" << "\t" << "DriverId" << "\t" << "VehicleId" << "\t" << "Status" << endl;
        for (const auto& service : services)
        {
            cout << service->getId() << "\t"
                << service->getSource() << "\t"
                << service->getDestination() << "\t"
                << service->getDistance() << "\t"
                << service->getFuelRate() << "\t"
                << service->getCustomerId() << "\t"
                << service->getDriverId() << "\t"
                << service->getVehicleId() << "\t"
                << service->getStatus() << endl;
        }
    }

    void saveVehicles(const string& filename)
    {
        ofstream outfile(filename);
        if (!outfile)
        {
            cerr << "Error opening file for saving vehicles: " << filename << endl;
            return;
        }

        for (const auto& vehicle : vehicles)
        {
            outfile << vehicle->getId() << " "
                << vehicle->getRegistrationNo() << " "
                << vehicle->getAvgMileage() << " "
                << vehicle->getLicenseType() << " "
                << vehicle->getFuelType() << " "
                << vehicle->getManufacturingDate().getDay() << " "
                << vehicle->getManufacturingDate().getMonth() << " "
                << vehicle->getManufacturingDate().getYear() << endl;
        }
        outfile.close();
        cout << "Vehicles saved successfully to " << filename << endl;
    }

    ~TMS()
    {
        for (Customer* customer : customers)
            delete customer;
        for (Driver* driver : drivers)
            delete driver;
        for (Vehicle* vehicle : vehicles)
            delete vehicle;
        for (Service* service : services)
            delete service;
    }
};

int main()
{
    TMS tms;
    tms.loadCustomers("customers.txt"); // Load customers from file
    tms.loadDrivers("drivers.txt");     // Load drivers from file
    tms.loadVehicles("vehicles.txt");   // Load vehicles from file
    tms.loadServices("services.txt");   // Load services from file

    int choice;

    do
    {
        cout << "\n--- Transport Management System Menu ---\n";
        cout << "1. Add a New Customer\n";
        cout << "2. Add a Driver\n";
        cout << "3. Add a Vehicle\n";
        cout << "4. Print List of All Customers\n";
        cout << "5. Print List of All Drivers\n";
        cout << "6. Print Complete List of Vehicles\n";
        cout << "7. Print Complete Details of a Particular Vehicle\n";
        cout << "8. Print Complete History of a Particular Customer\n";
        cout << "9. Print Complete History of a Driver\n";
        cout << "10. Print List of All Drivers Who Have Ranking Above 4.5\n";
        cout << "11. Print List of All Drivers with Multiple Licenses\n";
        cout << "12. Print Updated Salary of All Drivers Based on Updated Ranking\n";
        cout << "13. Add a Service Request (Ride or Delivery)\n";
        cout << "14. Cancel a Booking\n";
        cout << "15. Complete a Service\n";
        cout << "16. Print Details of All Customers Who Used the Same Vehicle on Different Dates\n";
        cout << "17. Print List of All Drivers Who Completed Delivery Services on Same Days\n";
        cout << "18. Print Details of All Pending Services on a Particular Date\n";
        cout << "19. Print Details of All Pending Services of a Particular Driver\n";
        cout << "20. Print Details of All Canceled Services by a Customer\n";
        cout << "21. Load Services from File\n";
        cout << "22. Save Services to File\n";
        cout << "23. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();                                         // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number between 1 and 23." << endl;
            continue; // Restart the loop
        }

        switch (choice)
        {
        case 1:
        {
            // Add a New Customer
            char fName[50], lName[50];
            int day, month, year, nid, age, cId;
            cout << "Enter First Name: ";
            cin >> fName;
            cout << "Enter Last Name: ";
            cin >> lName;
            cout << "Enter Date of Birth (day month year): ";
            cin >> day >> month >> year;

            if (cin.fail() || day < 1 || day > 31 || month < 1 || month > 12 || year < 1900)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid date format. Please try again." << endl;
                continue;
            }
            cout << "Enter National ID: ";
            cin >> nid;
            cout << "Enter Age: ";
            cin >> age;
            if (cin.fail() || age < 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid age. Please enter a valid number." << endl;
                continue;
            }
            cout << "Enter Customer ID: ";
            cin >> cId;
            if (cId < 0)
            {
                cout << "Driver ID must be non-negative." << endl;
                continue;
            }
            Customer* newCustomer = new Customer(fName, lName, day, month, year, nid, age, cId);
            tms.addCustomer(newCustomer);
            cout << "Customer added successfully.\n";
            break;
        }
        case 2:
        {
            // Add a Driver
            char fName[50], lName[50];
            int day, month, year, nid, age, dId;
            cout << "Enter First Name: ";
            cin >> fName;
            cout << "Enter Last Name: ";
            cin >> lName;
            cout << "Enter Date of Birth (day month year): ";
            cin >> day >> month >> year;
            if (cin.fail() || day < 1 || day > 31 || month < 1 || month > 12 || year < 1900)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid date format. Please try again." << endl;
                continue;
            }
            cout << "Enter National ID: ";
            cin >> nid;
            cout << "Enter Age: ";
            cin >> age;
            if (cin.fail() || age < 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid age. Please enter a valid number." << endl;
                continue;
            }
            cout << "Enter Driver ID: ";
            cin >> dId;
            if (dId < 0)
            {
                cout << "Driver ID must be non-negative." << endl;
                continue;
            }
            Driver* newDriver = new Driver(fName, lName, day, month, year, nid, age, dId);
            char license[50];
            char addMore;
            do
            {
                cout << "Enter License Type (or 'done' to finish): ";
                cin >> license;
                if (strcmp(license, "done") != 0)
                {
                    newDriver->addLicense(license);
                }
                cout << "Add more licenses? (y/n): ";
                cin >> addMore;
            } while (addMore == 'y');

            tms.addDriver(newDriver);
            cout << "Driver added successfully.\n";
            break;
        }

        case 3:
        {
            // Add a Vehicle
            int vId, regNo;
            float mileage;
            char lType[50], fType[50];
            int day, month, year;

            cout << "Enter Vehicle ID: ";
            cin >> vId;
            if (cin.fail() || vId < 0)
            {
                cin.clear();                                         // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid Vehicle ID. Please enter a non-negative integer." << endl;
                continue; // Restart the loop
            }

            cout << "Enter Registration Number: ";
            cin >> regNo;
            if (cin.fail() || regNo < 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Registration Number. Please enter a non-negative integer." << endl;
                continue; // Restart the loop
            }

            cout << "Enter Average Mileage: ";
            cin >> mileage;
            if (cin.fail() || mileage < 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid mileage. Please enter a valid number." << endl;
                continue; // Restart the loop
            }

            cout << "Enter License Type: ";
            cin >> lType;
            cout << "Enter Fuel Type: ";
            cin >> fType;
            cout << "Enter Manufacturing Date (day month year): ";
            cin >> day >> month >> year;
            if (cin.fail() || day < 1 || day > 31 || month < 1 || month > 12 || year < 1900)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid date format. Please try again." << endl;
                continue; // Restart the loop
            }

            Vehicle* newVehicle = new Vehicle(vId, regNo, mileage, lType, fType, Date(day, month, year));
            tms.addVehicle(newVehicle);
            cout << "Vehicle added successfully.\n";
            break;
        }
        case 4:
        {
            // Print List of All Customers
            tms.displayAllCustomers();
            break;
        }
        case 5:
        {
            // Print List of All Drivers
            tms.displayAllDrivers();
            break;
        }
        case 6:
        {
            // Print Complete List of Vehicles
            tms.displayAllVehicles();
            break;
        }
        case 7:
        {
            // Print Complete Details of a Particular Vehicle
            int vehicleId;
            cout << "Enter Vehicle ID: ";
            cin >> vehicleId;
            tms.displayVehicleDetails(vehicleId);
            break;
        }
        case 8:
        {
            // Print Complete History of a Particular Customer
            int customerId;
            cout << "Enter Customer ID: ";
            cin >> customerId;
            tms.displayCustomerHistory(customerId);
            break;
        }
        case 9:
        {
            // Print Complete History of a Driver
            int driverId;
            cout << "Enter Driver ID: ";
            cin >> driverId;
            tms.displayDriverHistory(driverId);
            break;
        }
        case 10:
        {
            // Print List of All Drivers Who Have Ranking Above 4.5
            tms.displayTopDrivers(4.5);
            break;
        }
        case 11:
        {
            // Print List of All Drivers with Multiple Licenses
            tms.displayDriversWithMultipleLicenses();
            break;
        }
        case 12:
        {
            // Print Updated Salary of All Drivers Based on Updated Ranking
            tms.displayUpdatedSalaries();
            break;
        }
        case 13:
        {
            // Add a Service Request (Ride or Delivery)
            int customerId, driverId, vehicleId;
            cout << "Enter Customer ID: ";
            cin >> customerId;
            cout << "Enter Driver ID: ";
            cin >> driverId;
            cout << "Enter Vehicle ID: ";
            cin >> vehicleId;
            if (customerId < 0 || driverId < 0 || vehicleId < 0)
            {
                cout << "Customer ID, Driver ID, and Vehicle ID must be non-negative." << endl;
                continue;
            }
            tms.addServiceRequest(customerId, driverId, vehicleId);
            break;
        }
        case 14:
        {
            // Cancel a Booking
            int serviceId, customerId;
            cout << "Enter Service ID: ";
            cin >> serviceId;
            cout << "Enter Customer ID: ";
            cin >> customerId;
            if (serviceId < 0 || customerId < 0)
            {
                cout << "Service ID and Customer ID must be non-negative." << endl;
                continue;
            }
            tms.cancelBooking(serviceId, customerId);
            break;
        }
        case 15:
        {
            tms.getServicesPrinted();

            int serviceId;
            cout << "Enter Service ID: ";
            cin >> serviceId;
            if (serviceId < 0)
            {
                cout << "Service ID must be non-negative." << endl;
                continue;
            }
            tms.completeService(serviceId);
            break;
        }
        case 16:
        {
            // Print Details of All Customers Who Used the Same Vehicle on Different Dates
            int vehicleId;
            cout << "Enter Vehicle ID: ";
            cin >> vehicleId;
            tms.printCustomersUsingSameVehicle(vehicleId);
            break;
        }
        case 17:
        {
            // Print List of All Drivers Who Completed Delivery Services on Same Days
            tms.printDriversCompletedDeliverySameDays();
            break;
        }
        case 18:
        {
            // Print Details of All Pending Services on a Particular Date
            int day, month, year;
            cout << "Enter Date (day month year): ";
            cin >> day >> month >> year;
            if (cin.fail() || day < 1 || day > 31 || month < 1 || month > 12 || year < 1900)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid date format. Please try again." << endl;
                continue;
            }
            tms.printPendingServicesOnDate(day, month, year);
            break;
        }
        case 19:
        {
            // Print Details of All Pending Services of a Particular Driver
            int driverId;
            cout << "Enter Driver ID: ";
            cin >> driverId;
            if (driverId < 0)
            {
                cout << "Driver ID must be non-negative." << endl;
                continue;
            }
            tms.printPendingServicesOfDriver(driverId);
            break;
        }
        case 20:
        {
            // Print Details of All Canceled Services by a Customer
            int customerId;
            cout << "Enter Customer ID: ";
            cin >> customerId;
            tms.printCanceledServicesByCustomer(customerId);
            break;
        }
        case 21:
        {
            // Load Services from File
            tms.loadServices("services.txt");
            // cout << "Services loaded successfully.\n";
            break;
        }
        case 22:
        {
            // Save Services to File
            tms.saveServices("services.txt");
            cout << "Services saved successfully.\n";
            break;
        }
        case 23:
        {
            cout << "Exiting the program.\n";
            break;
        }
        default:
        {
            cout << "Invalid choice. Please try again.\n";
            break;
        }
        }
    } while (choice != 23);

    cout << endl;
    tms.saveCustomers("customers.txt");
    tms.saveDrivers("drivers.txt");
    tms.saveVehicles("vehicles.txt");
    tms.saveServices("services.txt");
    return 0;
}