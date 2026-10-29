
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

// Color Codes
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

int selectedColor = 4;

// Function to display selected color
void printColor(string message)
{
    switch(selectedColor)
    {
        case 1: cout << RED; break;
        case 2: cout << GREEN; break;
        case 3: cout << YELLOW; break;
        case 4: cout << BLUE; break;
        case 5: cout << CYAN; break;
    }

    cout << message << RESET << endl;
}

// Function to change color
void changeColor()
{
    int choice;

    cout << "\n===== SELECT COLOR =====";
    cout << "\n1. Red";
    cout << "\n2. Green";
    cout << "\n3. Yellow";
    cout << "\n4. Blue";
    cout << "\n5. Cyan";
    cout << "\nEnter color choice: ";
    cin >> choice;

    if(choice >= 1 && choice <= 5)
    {
        selectedColor = choice;
        cout << GREEN << "Color changed successfully!"
             << RESET << endl;
    }
    else
    {
        cout << RED << "Invalid color choice!"
             << RESET << endl;
    }
}

// Class for color inheritance
class Color
{
public:
    void welcome()
    {
        cout << GREEN;
        cout << "\nWelcome to Airport Management System!";
        cout << RESET << endl;
    }

    void thankYou()
    {
        cout << CYAN;
        cout << "\nThank you for using Airport Management System!";
        cout << RESET << endl;
    }

    void showTitle()
    {
        printColor("===== AIRPORT MANAGEMENT =====");
    }
};

// Abstract base class
class Airport
{
public:
    virtual void display() = 0;
    virtual ~Airport() {}
};

// Base class
class Flight : public Airport, public Color
{
public:
    int id, priority, runway;
    char name[30], destination[30];

    static int count;

    // Constructor
    Flight()
    {
        id = 0;
        priority = 0;
        runway = 0;
        name[0] = '\0';
        destination[0] = '\0';

        welcome();
        count++;
    }

    // Enter flight details
    void getData()
    {
        cout << "Enter Flight ID: ";
        cin >> id;

        cout << "Enter Flight Name: ";
        cin >> name;

        cout << "Enter Destination: ";
        cin >> destination;

        cout << "Enter Priority (1 to 5): ";
        cin >> priority;

        if(priority < 1 || priority > 5)
        {
            cout << "Invalid priority. Setting priority to 5."
                 << endl;
            priority = 5;
        }
    }

    // Virtual function
    virtual void display()
    {
        printColor("Flight Details");

        cout << "Flight ID: " << id << endl;
        cout << "Flight Name: " << name << endl;
        cout << "Destination: " << destination << endl;
        cout << "Priority: " << priority << endl;
        cout << "Runway Number: " << runway << endl;
    }

    // Assign runway with default argument
    void assignRunway(int r = 1)
    {
        runway = r;
    }

    // Get flight ID
    int getID()
    {
        return id;
    }

    // Operator overloading
    bool operator < (Flight &f)
    {
        return priority < f.priority;
    }

    // Save details in file
    void saveData(ofstream &file)
    {
        file << "Flight ID: " << id << endl;
        file << "Flight Name: " << name << endl;
        file << "Destination: " << destination << endl;
        file << "Priority: " << priority << endl;
        file << "Runway Number: " << runway << endl;
        file << "------------------------" << endl;
    }

    // Static function
    static int getCount()
    {
        return count;
    }

    // Friend function
    friend void showCount();

    // Virtual destructor
    virtual ~Flight()
    {
        count--;
        thankYou();
    }
};

int Flight::count = 0;

// Passenger flight class
class PassengerFlight : public Flight
{
public:
    void display()
    {
        cout << GREEN << "\n--- Passenger Flight ---"
             << RESET << endl;

        Flight::display();
    }
};

// Cargo flight class
class CargoFlight : public Flight
{
public:
    void display()
    {
        cout << YELLOW << "\n--- Cargo Flight ---"
             << RESET << endl;

        Flight::display();
    }
};

// Emergency flight class
class EmergencyFlight : public PassengerFlight
{
public:
    void display()
    {
        cout << RED << "\n!!! EMERGENCY FLIGHT !!!"
             << RESET << endl;

        Flight::display();
    }
};

// Friend function
void showCount()
{
    cout << CYAN << "\nTotal Flights: "
         << Flight::getCount() << RESET << endl;
}

int main()
{
    Flight *f[10];

    int n = 0;
    int choice, r, id;

    do
    {
        printColor("\n===== AIRPORT MANAGEMENT =====");

        cout << "\n1. Add Passenger Flight";
        cout << "\n2. Add Cargo Flight";
        cout << "\n3. Add Emergency Flight";
        cout << "\n4. Display Flights";
        cout << "\n5. Assign Runway";
        cout << "\n6. Compare Priority";
        cout << "\n7. Save Flight Details";
        cout << "\n8. Show Flight Count";
        cout << "\n9. Change Color";
        cout << "\n10. Exit";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                if(n < 10)
                {
                    f[n] = new PassengerFlight;
                    f[n]->getData();
                    n++;
                }
                else
                    cout << "Flight limit reached!";
                break;

            case 2:
                if(n < 10)
                {
                    f[n] = new CargoFlight;
                    f[n]->getData();
                    n++;
                }
                else
                    cout << "Flight limit reached!";
                break;

            case 3:
                if(n < 10)
                {
                    f[n] = new EmergencyFlight;
                    f[n]->getData();

                    // Emergency flight gets highest priority
                    f[n]->priority = 1;

                    n++;

                    cout << RED << "Emergency priority set to 1."
                         << RESET << endl;
                }
                else
                    cout << "Flight limit reached!";
                break;

            case 4:
                if(n == 0)
                    cout << "No flights available!" << endl;

                for(int i = 0; i < n; i++)
                    f[i]->display();
                break;

            case 5:
                cout << "Enter Flight ID: ";
                cin >> id;

                cout << "Enter Runway Number (1 to 3): ";
                cin >> r;

                if(r < 1 || r > 3)
                {
                    cout << RED << "Invalid Runway Number!"
                         << RESET << endl;
                    break;
                }

                {
                    int found = 0;

                    for(int i = 0; i < n; i++)
                    {
                        if(f[i]->getID() == id)
                        {
                            f[i]->assignRunway(r);

                            cout << GREEN
                                 << "Runway assigned successfully!"
                                 << RESET << endl;

                            found = 1;
                            break;
                        }
                    }

                    if(found == 0)
                        cout << RED << "Flight not found!"
                             << RESET << endl;
                }
                break;

            case 6:
                if(n >= 2)
                {
                    if(*f[0] < *f[1])
                        cout << "Second flight has higher priority.";
                    else if(*f[1] < *f[0])
                        cout << "First flight has higher priority.";
                    else
                        cout << "Both flights have equal priority.";
                }
                else
                    cout << "Add at least two flights first.";
                break;

            case 7:
                if(n > 0)
                {
                    ofstream file("flights.txt");

                    if(!file)
                    {
                        cout << "Unable to open file!" << endl;
                        break;
                    }

                    for(int i = 0; i < n; i++)
                        f[i]->saveData(file);

                    file.close();

                    cout << GREEN
                         << "Flight details saved to flights.txt!"
                         << RESET << endl;
                }
                else
                    cout << "No flights available!";
                break;

            case 8:
                showCount();
                break;

            case 9:
                changeColor();
                break;

            case 10:
                cout << "\nExiting the system..." << endl;
                break;

            default:
                cout << RED << "Wrong choice!"
                     << RESET << endl;
        }

    } while(choice != 10);

    // Delete all flight objects
    for(int i = 0; i < n; i++)
        delete f[i];

    return 0;
}
