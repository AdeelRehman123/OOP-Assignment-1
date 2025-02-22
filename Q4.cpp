#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    int studentID;
    string name;
    bool paymentStatus;

public:
    Student(int id = 0, string studentName = "") : studentID(id), name(studentName), paymentStatus(false) {}

    void registerStudent() {
        cout << name << " has been registered for the transportation service." << endl;
    }

    void makePayment() {
        paymentStatus = true;
        cout << name << " has successfully made the payment." << endl;
    }

    bool checkPayment() const {
        return paymentStatus;
    }

    int getStudentID() const {
        return studentID;
    }

    string getName() const {
        return name;
    }
};

class Route {
private:
    int routeID;
    string startLocation;
    string endLocation;
    string stops[10]; 
    int stopCount;

public:
    Route(int id = 0, string start = "", string end = "") : routeID(id), startLocation(start), endLocation(end), stopCount(0) {}

    void addStop(const string& stop) {
        if (stopCount < 10) {
            stops[stopCount++] = stop;
        } else {
            cout << "Cannot add more stops, limit reached." << endl;
        }
    }

    void displayRoute() const {
        cout << "Route: " << startLocation << " to " << endLocation << endl;
    }

    int getRouteID() const {
        return routeID;
    }
};

class Bus {
private:
    int busID;
    Route route;
    int seatsAvailable;
    Student studentsOnBoard[30]; 
    int studentCount;

public:
    Bus(int id = 0, Route r = Route()) : busID(id), route(r), seatsAvailable(30), studentCount(0) {}

    void addStudent(const Student& student) {
        if (studentCount < 30) {
            studentsOnBoard[studentCount++] = student;
            seatsAvailable--;
            cout << student.getName() << " added to bus " << busID << endl;
        } else {
            cout << "No seats available on bus " << busID << endl;
        }
    }

    void displayBusDetails() const {
        cout << "Bus ID: " << busID << endl;
        route.displayRoute();
        cout << "Seats available: " << seatsAvailable << endl;
        cout << "Students on board: ";
        for (int i = 0; i < studentCount; i++) {
            cout << studentsOnBoard[i].getName() << " ";
        }
        cout << endl;
    }

    int getBusID() const {
        return busID;
    }
};

class TransportationSystem {
private:
    Student students[100];
    Bus buses[20];
    Route routes[20];
    int studentCount;
    int busCount;
    int routeCount;

public:
    TransportationSystem() : studentCount(0), busCount(0), routeCount(0) {}

    void registerStudent() {
        int id;
        string name;
        cout << "Enter student ID: ";
        cin >> id;
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);
        students[studentCount++] = Student(id, name);
        students[studentCount - 1].registerStudent();
    }

    void makePayment() {
        int studentID;
        cout << "Enter student ID to make payment: ";
        cin >> studentID;
        for (int i = 0; i < studentCount; i++) {
            if (students[i].getStudentID() == studentID) {
                students[i].makePayment();
                return;
            }
        }
        cout << "Student not found!" << endl;
    }

    void addRoute() {
        int id;
        string start, end;
        cout << "Enter route ID: ";
        cin >> id;
        cout << "Enter start location: ";
        cin.ignore();
        getline(cin, start);
        cout << "Enter end location: ";
        getline(cin, end);
        routes[routeCount] = Route(id, start, end);
        int numStops;
        cout << "Enter number of stops: ";
        cin >> numStops;
        cin.ignore();
        for (int i = 0; i < numStops; i++) {
            string stop;
            cout << "Enter stop " << i + 1 << ": ";
            getline(cin, stop);
            routes[routeCount].addStop(stop);
        }
        routeCount++;
        cout << "Route added successfully!" << endl;
    }

    void addBus() {
        int busID, routeID;
        cout << "Enter bus ID: ";
        cin >> busID;
        cout << "Enter route ID for this bus: ";
        cin >> routeID;
        for (int i = 0; i < routeCount; i++) {
            if (routes[i].getRouteID() == routeID) {
                buses[busCount++] = Bus(busID, routes[i]);
                cout << "Bus added successfully!" << endl;
                return;
            }
        }
        cout << "Route not found!" << endl;
    }

    void assignStudentToBus() {
        int studentID, busID;
        cout << "Enter student ID: ";
        cin >> studentID;
        cout << "Enter bus ID: ";
        cin >> busID;
        for (int i = 0; i < studentCount; i++) {
            if (students[i].getStudentID() == studentID) {
                if (!students[i].checkPayment()) {
                    cout << "Payment pending. Student cannot board the bus." << endl;
                    return;
                }
                for (int j = 0; j < busCount; j++) {
                    if (buses[j].getBusID() == busID) {
                        buses[j].addStudent(students[i]);
                        return;
                    }
                }
                cout << "Bus not found!" << endl;
                return;
            }
        }
        cout << "Student not found!" << endl;
    }

    void displayAllBuses() {
        if (busCount == 0) {
            cout << "No buses available." << endl;
            return;
        }
        for (int i = 0; i < busCount; i++) {
            buses[i].displayBusDetails();
        }
    }
};

int main() {
    TransportationSystem ts;
    int choice;
    while (true) {
        cout << "\n1. Register Student\n2. Make Payment\n3. Add Route\n4. Add Bus\n5. Assign Student to Bus\n6. Display All Buses\n7. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: ts.registerStudent(); break;
            case 2: ts.makePayment(); break;
            case 3: ts.addRoute(); break;
            case 4: ts.addBus(); break;
            case 5: ts.assignStudentToBus(); break;
            case 6: ts.displayAllBuses(); break;
            case 7: return 0;
            default: cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}
