#include <iostream>
#include <string>

using namespace std;

#define MAX_USERS 100
#define MAX_VEHICLES 10

enum LicenseType
{
    LEARNER,
    INTERMEDIATE,
    FULL
};

class User
{
private:
    int userID;
    string name;
    int age;
    LicenseType licenseType;
    string contactNumber;

public:
    User() : userID(0), age(0), licenseType(LEARNER), contactNumber("") {}

    void registerUser(int id, string n, int a, LicenseType l, string contact)
    {
        userID = id;
        name = n;
        age = a;
        licenseType = l;
        contactNumber = contact;
    }

    int getUserID() const { return userID; }
    string getName() const { return name; }
    LicenseType getLicenseType() const { return licenseType; }
    string getContactNumber() const { return contactNumber; }

    void updateUserInfo(string newName, int newAge, LicenseType newLicenseType, string newContactNumber)
    {
        name = newName;
        age = newAge;
        licenseType = newLicenseType;
        contactNumber = newContactNumber;
    }

    void displayUserInfo() const
    {
        string license;
        switch (licenseType)
        {
        case LEARNER:
            license = "Learner";
            break;
        case INTERMEDIATE:
            license = "Intermediate";
            break;
        case FULL:
            license = "Full";
            break;
        }
        cout << "User ID: " << userID << "\nName: " << name
             << "\nAge: " << age << "\nLicense Type: " << license
             << "\nContact: " << contactNumber << endl;
    }
};

class Vehicle
{
private:
    string model;
    float rentalPrice;
    LicenseType requiredLicenseType;

public:
    Vehicle() : model(""), rentalPrice(0.0), requiredLicenseType(LEARNER) {}

    void registerVehicle(string m, float price, LicenseType license)
    {
        model = m;
        rentalPrice = price;
        requiredLicenseType = license;
    }

    string getModel() const { return model; }
    float getRentalPrice() const { return rentalPrice; }
    LicenseType getRequiredLicenseType() const { return requiredLicenseType; }

    void displayVehicleInfo() const
    {
        string license;
        switch (requiredLicenseType)
        {
        case LEARNER:
            license = "Learner";
            break;
        case INTERMEDIATE:
            license = "Intermediate";
            break;
        case FULL:
            license = "Full";
            break;
        }
        cout << "Model: " << model << "\nRental Price: $" << rentalPrice
             << "\nRequired License: " << license << endl;
    }
};

void displayMenu()
{
    cout << "\nVehicle Rental System Menu\n";
    cout << "1. Register User\n";
    cout << "2. Update User Information\n";
    cout << "3. View Available Vehicles\n";
    cout << "4. Rent Vehicle\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    User users[MAX_USERS];
    int userCount = 0;

    Vehicle vehicles[MAX_VEHICLES];
    vehicles[0].registerVehicle("Toyota Corolla", 50.0, INTERMEDIATE);
    vehicles[1].registerVehicle("Honda Civic", 60.0, FULL);
    vehicles[2].registerVehicle("Ford Mustang", 100.0, FULL);
    vehicles[3].registerVehicle("Suzuki Swift", 40.0, LEARNER);
    int vehicleCount = 4;

    int choice;
    do
    {
        displayMenu();
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            if (userCount >= MAX_USERS)
            {
                cout << "User limit reached!" << endl;
                break;
            }
            int id, age, licenseType;
            string name, contact;
            cout << "Enter user ID: ";
            cin >> id;
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter license type (0: Learner, 1: Intermediate, 2: Full): ";
            cin >> licenseType;
            cout << "Enter contact number: ";
            cin.ignore();
            getline(cin, contact);

            users[userCount].registerUser(id, name, age, static_cast<LicenseType>(licenseType), contact);
            userCount++;
            cout << "User registered successfully!" << endl;
            break;
        }
        case 2:
        {
            int userID;
            cout << "Enter user ID to update: ";
            cin >> userID;
            bool found = false;
            for (int i = 0; i < userCount; i++)
            {
                if (users[i].getUserID() == userID)
                {
                    string newName, newContact;
                    int newAge, newLicenseType;
                    cout << "Enter new name: ";
                    cin.ignore();
                    getline(cin, newName);
                    cout << "Enter new age: ";
                    cin >> newAge;
                    cout << "Enter new license type (0: Learner, 1: Intermediate, 2: Full): ";
                    cin >> newLicenseType;
                    cout << "Enter new contact number: ";
                    cin.ignore();
                    getline(cin, newContact);
                    users[i].updateUserInfo(newName, newAge, static_cast<LicenseType>(newLicenseType), newContact);
                    cout << "User information updated successfully!" << endl;
                    users[i].displayUserInfo();
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "User not found!" << endl;
            }
            break;
        }
        case 3:
            for (int i = 0; i < vehicleCount; i++)
            {
                vehicles[i].displayVehicleInfo();
                cout << endl;
            }
            break;
        case 4:
        {
            int userID;
            cout << "Enter user ID: ";
            cin >> userID;
            bool found = false;
            LicenseType userLicense;

            for (int i = 0; i < userCount; i++)
            {
                if (users[i].getUserID() == userID)
                {
                    userLicense = users[i].getLicenseType();
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "User not found!" << endl;
                break;
            }

            cout << "Available vehicles for rental:\n";
            for (int i = 0; i < vehicleCount; i++)
            {
                cout << i + 1 << ". " << vehicles[i].getModel() << " - $" << vehicles[i].getRentalPrice() << " per day (Requires: ";
                string license;
                switch (vehicles[i].getRequiredLicenseType())
                {
                case LEARNER:
                    license = "Learner";
                    break;
                case INTERMEDIATE:
                    license = "Intermediate";
                    break;
                case FULL:
                    license = "Full";
                    break;
                }
                cout << license << " license)" << endl;
            }

            cout << "Enter the vehicle number you want to rent: ";
            int vehicleChoice;
            cin >> vehicleChoice;

            if (vehicleChoice < 1 || vehicleChoice > vehicleCount)
            {
                cout << "Invalid vehicle choice!\n";
                break;
            }

            if (userLicense < vehicles[vehicleChoice - 1].getRequiredLicenseType())
            {
                cout << "You do not have the required license to rent this vehicle.\n";
                break;
            }

            cout << "Vehicle rented successfully!\n";
            break;
        }
        case 5:
            cout << "Exiting the system." << endl;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
