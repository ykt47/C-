#include <iostream>
#include <iomanip>  // For setting output width
#include <ctime>
#include <string>
#include <algorithm>
#include <fstream>
#include <regex>
#include <cstring>
#include <sstream>

using namespace std;

#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define BLUE    "\033[1;34m"

struct Unit {
    string unitName;
    double price;
    bool bookedDates[31] = { false }; // Each unit has its own schedule
    bool maintenanceDates[31] = { false };
};

struct Service {
    string propertyName;
    double price;
    Unit units[2];
};

struct Rental {
    string Rentalname;
    double price;
    bool bookedDates[31] = { false };
    string rentaltype;
};

struct Booking {
    string bookingID;
    string customerName;
    string unitName;
    string propertyName;
    int checkInDate;
    int nights;
    string date;  // Store date in format "YYYY-MM-DD"
    int checkoutDate;
    double price;
};

struct Customer {
    string name;
    int propertyNum;
};

bool isValidPhoneNumber(const string& phoneNumber) {
    return phoneNumber.length() == 8;
};

bool isValidGmail(const string& email) {
    string domain = "@gmail.com";
    size_t pos = email.find(domain);
    return (pos != string::npos && pos == email.length() - domain.length());
}
bool isValidExpiryDate(const string& expiryDate) {
    if (expiryDate.size() != 5 || expiryDate[2] != '/') {
        return false; // Must be in MM/YY format
    }
    int month, year;
    char slash;
    stringstream ss(expiryDate);
    ss >> month >> slash >> year;
    if (ss.fail() || slash != '/') {
        return false; // Invalid input format
    }
    if (month < 1 || month > 12) {
        return false; // Month must be between 1 and 12
    }
    return true; // Year can be any valid number
}




void startMenu(Service services[], Rental rentals[], Booking bookings[], int bookingCount, int rentalsindex, int serviceChoice);
void aboutUs(Service services[], Rental rentals[], Booking bookings[], int bookingCount, int rentalsindex, int serviceChoice);
void customerStartMenu(Service services[], Rental rentals[], Booking bookings[], int bookingCount, int rentalsindex, int serviceChoice);
void customerLogin(Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice);
void customerRegister(Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice);
void customerDetailsReg(Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice);
void custMenu(Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice);
void showPropertyRentalMenu(Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice);
void showCondoPage(Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice);
void showBungalowPage(Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice);
void showHousePage(Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice);
void askForHouse(const string& service, const string& rental, const string& experience, const string& achievements, Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice);

void displayCalendar(Rental rentals[], Service services[], int serviceChoice, int unitChoice);
void initializeData(Service services[]);
void staffLogin(Service services[], Rental rentals[], Booking bookings[], int bookingCount, int rentalsindex, int serviceChoice);
void staffAccountSelection(Service services[], Rental rentals[], Booking bookings[], int bookingCount, int rentalsindex, int serviceChoice);
void adminMenu(Service services[], Rental rentals[], Booking bookings[], int bookingCount, int rentalsindex, int serviceChoice);
void salesReport(Service services[], Rental rentals[], Booking bookings[], int bookingCount, int rentalsindex, int serviceChoice);
void readCustomerDetails(Service services[], Rental rentals[], Booking bookings[], int bookingCount, int rentalsindex, int serviceChoice);
void bookAppointment(Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int servicechoice);
void paymentPage(Service services[], Rental rentals[], Booking& booking, Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice);
void searchBookings(Service service[], Rental rentals[], Booking bookings[], int bookingCount);
void displayData(Booking bookings[], int bookingCount, const string& search);
void sortBookingsByDate(Booking bookings[], int bookingCount);
void bookingSummaryPage(const Booking& booking);
void deleteAppointment(Booking bookings[], int& bookingCount, Service services[]);
void searchAndModifyBooking(Booking bookings[], int bookingCount, Rental rentals[], Service services[], int serviceChoice);
void scheduleMaintenance(Service services[]);
void viewAndModifyMaintenance(Service services[]);
void cancelMaintenance(Service services[]);
void maintenanceMenu(Service services[], Rental rentals[], Booking bookings[], int bookingCount, int rentalsindex, int serviceChoice);
void getValidName(string& customerName);
void exitApplication();

void initializeData(Service services[]) {
    // Property 1: Skyline Residences (2 Units)
    services[0].propertyName = "Skyline Residences";
    services[0].units[0] = { "Unit A (3 Bedroom, 2 Bathroom)", 250.0 };
    services[0].units[1] = { "Unit B (5 Bedroom, 3 Bathroom)", 450.0 };

    // Property 2: Evergreen Cottage (2 Units)
    services[1].propertyName = "Evergreen Cottage";
    services[1].units[0] = { "Unit A (8 Bedroom, 6 Bathroom)", 1000.0 };
    services[1].units[1] = { "Unit B (10 Bedroom, 8 Bathroom)", 1500.0 };

    // Property 3: Amberwood Residences (2 Units)
    services[2].propertyName = "Amberwood Residences";
    services[2].units[0] = { "Unit A (6 Bedroom, 4 Bathroom)", 500.0 };
    services[2].units[1] = { "Unit B (8 Bedroom, 5 Bathroom)", 750.0 };
}
int main() {
    const int DAYS_IN_MONTH = 30;
    const int MAX_SERVICES = 3;
    const int MAX_RENTAL = 7;
    const int MAX_BOOKINGS = 100;

    Service services[MAX_SERVICES];
    Booking bookings[MAX_BOOKINGS];
    Rental rentals[MAX_RENTAL];
    int rentalsindex = 0;
    int serviceChoice = 0;
    int bookingCount = 0;
    initializeData(services);
    startMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
    return 0;
}



void startMenu(Service services[], Rental rentals[], Booking bookings[], int bookingCount, int rentalsindex, int serviceChoice) {
    int choice;
    do {
        system("cls");
        cout << CYAN "********************************************************************************\n";
        cout << "|                          PrimeStay Properties                                |\n";
        cout << "********************************************************************************" RESET "\n";
        cout << "|Welcome to our application! Hope you have a great day!                        |\n";
        cout << "|                                                                              |\n";
        cout << YELLOW "|                            1. About Us                                       |\n";
        cout << "|                            2. Customer Mode                                  |\n";
        cout << "|                            3. Staff Mode                                     |\n";
        cout << "|                            4. Exit                                           |\n" RESET;
        cout << "--------------------------------------------------------------------------------\n";


        while (true) {
            cout << "Enter your option (1 to 4): ";
            cin >> choice;
            if (cin.fail() || choice < 1 || choice > 4) {
                cout << RED "Invalid option! Please try again.\n" RESET;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                break;
            }
        }
        switch (choice) {
        case 1:
            cout << GREEN "Navigating to About Us...\n" RESET;
            aboutUs(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
            break;
        case 2:
            cout << GREEN "Navigating to Customer Mode...\n" RESET;
            customerStartMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
            break;
        case 3:
            cout << GREEN "Navigating to Staff Mode...\n" RESET;
            staffAccountSelection(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
            break;
        case 4:
            cout << GREEN "Exiting the application...\n" RESET;
            exitApplication();
            break;
        default:
            break;
        }
    } while (choice < 1 || choice > 4);
}


void aboutUs(Service services[], Rental rentals[], Booking bookings[], int bookingCount, int rentalsindex, int serviceChoice) {
    system("cls");
    cout << CYAN "********************************************************************************\n";
    cout << "|                         PrimeStay Properties                                  |\n";
    cout << "********************************************************************************" RESET "\n";

    cout << YELLOW "\nAbout Our Company\n\n";
    cout << "At PrimeStay Properties, we specialize in providing high-quality rental properties tailored to meet\n";
    cout << "the diverse needs of our clients. Whether you're looking for a cozy apartment, a spacious family home, or a\n";
    cout << "commercial space, we offer well-maintained and thoughtfully selected properties in prime locations.\n\n";
    cout << "Our mission is to create seamless and stress-free rental experiences by offering transparent leasing\n";
    cout << "terms, responsive customer service, and properties that feel like home. We take pride in helping\n";
    cout << "individuals, families, and businesses find the perfect space to live, work, and grow.\n\n";
    cout << "With a commitment to professionalism and customer satisfaction, PrimeStay Properties is your trusted\n";
    cout << "partner in property rentals.\n\n" RESET;

    cout << GREEN "Press Enter to go back to Main Menu..." RESET;
    cin.ignore();
    cin.get();
    startMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
}

void customerStartMenu(Service services[], Rental rentals[], Booking bookings[], int bookingCount, int rentalsindex, int serviceChoice) {
    int custMenuChoice = 0;
    do {
        system("cls");
        cout << CYAN "********************************************************************************\n";
        cout << "|                                PrimeStay Properties                          |\n";
        cout << "********************************************************************************" RESET "\n";

        cout << "| You are now in customer menu!                                                |\n";
        cout << "|                                                                              |\n";
        cout << YELLOW "|                             1: Login                                         |\n";
        cout << "|                             2: Register                                      |\n";
        cout << "|                             3: Back to Main Menu                             |\n" RESET;
        cout << "--------------------------------------------------------------------------------\n";

        while (true) {
            cout << "Enter your option (1 to 3): ";
            cin >> custMenuChoice;

            if (cin.fail() || custMenuChoice < 1 || custMenuChoice > 3) {
                cout << RED "Invalid option! Please try again.\n" RESET;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                break;
            }
        }
        switch (custMenuChoice) {
        case 1:
            customerLogin(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
            break;
        case 2:
            customerRegister(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
            break;
        case 3:
            startMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
            break;
        default:
            cout << RED "Invalid option! Please try again.\n" RESET;
            cout << "Enter your choice (1 to 3): ";
            cin >> custMenuChoice;
            break;
        }
    } while (custMenuChoice < 1 || custMenuChoice > 3);
}
void customerLogin(Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice) {
    int count = 0;
    string username, password, usernameInput, passwordInput, choice;

    system("cls");
    cout << CYAN "*******************************************************************************" << endl;
    cout << "                          PrimeStay Properties                                 " << endl;
    cout << "*******************************************************************************" RESET "\n" << endl;

    cout << YELLOW "You are now in Customer Login Menu! " << endl;
    cout << YELLOW << "Press B to go back or Press Other Key to continue:" << RESET;
    cin.ignore();
    getline(cin, choice);

    if (choice == "b" || choice == "B") {
        customerStartMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
        return; // Ensure function exits after going back
    }

    cout << "Enter your username: ";
    cin >> usernameInput;
    cout << "Enter your password: ";
    cin >> passwordInput;

    ifstream input("database.txt");
    while (input >> username >> password) {
        if (username == usernameInput && password == passwordInput) {
            count = 1;
        }
    }
    input.close();

    if (count == 1) {
        cout << GREEN "\nLogin Successful!" << endl;
        cout << "Greetings! " << usernameInput << RESET << endl;
        cout << "\nPress Enter to go back to the customer account menu.";
        cin.ignore();
        cin.get();
        custMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
    }
    else {
        cout << RED "\nLogin Error! Invalid username or password!" << endl;
        cout << "\nPlease register your details before you login!" << RESET << endl;
        cout << "\nPress Enter to go back to the customer account menu.";
        cin.ignore();
        cin.get();
        customerStartMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
    }
}

void customerRegister(Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice) {
    string registeredUser, registeredPass, choice;

    system("cls");
    cout << CYAN "*******************************************************************************" << endl;
    cout << "                                 PrimeStay Properties                          " << endl;
    cout << "*******************************************************************************" RESET "\n" << endl;

    cout << YELLOW "Please register to enjoy more benefits from our application!\n" RESET << endl;
    cout << YELLOW << "Press B to go back or Press Other Key to continue:" << RESET;
    cin.ignore();
    getline(cin, choice);

    if (choice == "b" || choice == "B") {
        customerStartMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
        return; // Ensure function exits after going back
    }
    cout << "Enter the username: ";
    cin >> registeredUser;
    cout << "Enter the password: ";
    cin >> registeredPass;

    ofstream reg("database.txt", ios::app);
    reg << registeredUser << ' ' << registeredPass << endl;

    cout << GREEN "\nRegistration Successful!\n";
    cout << "You will proceed to another page to fill in your personal details.\n" RESET << endl;

    cout << "Press Enter to proceed to the next page.";
    cin.ignore();
    cin.get();
    customerDetailsReg(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
}

void customerDetailsReg(Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice) {
    string fullnameUser, Useremail, phoneNumber;

    system("cls");
    cout << CYAN "*******************************************************************************" << endl;
    cout << "                         PrimeStay Properties                                  " << endl;
    cout << "*******************************************************************************" RESET "\n" << endl;

    cout << YELLOW "Please fill in your personal details.\n" RESET << endl;

    cout << "Enter your name: ";
    cin >> fullnameUser;
    cout << " " << endl;

    do {
        cout << "Enter your email: ";
        cin >> Useremail;
        if (!isValidGmail(Useremail)) {
            cout << RED "Invalid email. Please try again." RESET << endl;
        }
    } while (!isValidGmail(Useremail));
    cout << " " << endl;

    do {
        cout << "Enter phone number: ";
        cin >> phoneNumber;
        if (!isValidPhoneNumber(phoneNumber)) {
            cout << RED "Invalid phone number. Please try again." RESET << endl;
        }
    } while (!isValidPhoneNumber(phoneNumber));
    cout << " " << endl;

    ofstream reg2("UsersDatabase.txt", ios::app);
    reg2 << fullnameUser << setw(25) << Useremail << setw(25) << phoneNumber << setw(25) << endl;

    cout << GREEN "\nYour details have been successfully recorded!\n" RESET << endl;
    cout << "Please login to start enjoying our application features." << endl;
    cout << "\nPress Enter to proceed to the customer start menu for login.";

    cin.ignore();
    cin.get();
    customerStartMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
}
void custMenu(Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice) {
    int customerChoice = 0;
    do {
        system("cls");

        cout << CYAN "********************************************************************************" << endl;
        cout << "|                          PrimeStay Properties                                |" << endl;
        cout << "********************************************************************************" RESET << endl;

        cout << YELLOW "|Welcome to Customer Management Console!                                       |" << endl;
        cout << "|                                                                              |" << endl;
        cout << "|  " << GREEN "1: View Rental Property" << RESET "                                                     |" << endl;
        cout << "|  " << GREEN "2: Book Property" << RESET "                                                            |" << endl;
        cout << "|  " << GREEN "3: View Booking" << RESET "                                                             |" << endl;
        cout << "|  " << GREEN "4: Delete Booking" << RESET "                                                           |" << endl;
        cout << "|  " << GREEN "5: Modify Booking" << RESET "                                                           |" << endl;
        cout << "|  " << RED "6: Logout" << RESET "                                                                   |" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;

        while (true) {
            cout << "Enter your choice (1 to 6): ";
            cin >> customerChoice;

            if (cin.fail() || customerChoice < 1 || customerChoice > 7) {
                cout << RED "Invalid choice! Please try again!" RESET << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                break;
            }
        }
        switch (customerChoice) {
        case 1:
            showPropertyRentalMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
            break;
        case 2:
            bookAppointment(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
            break;
        case 3:
            searchBookings(services, rentals, bookings, bookingCount);
            cin.get();
            custMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
            break;
        case 4:
            deleteAppointment(bookings, rentalsindex, services);
            break;
        case 5:
            searchAndModifyBooking(bookings, bookingCount, rentals, services, serviceChoice);
            break;
        case 6:
            startMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
            break;

        }
    } while (customerChoice != 6);
}

void showPropertyRentalMenu(Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice) {
    char choiceServices;
    system("CLS");

    cout << CYAN "+--------------------------------------+" << endl;
    cout << "|      Property Rental Menu            |" << endl;
    cout << "+--------------------------------------+" RESET << endl;

    cout << YELLOW "|  [A] Condominium                     |" RESET << endl;
    cout << YELLOW "|  [B] Bungalow                        |" RESET << endl;
    cout << YELLOW "|  [C] Terrace House                   |" RESET << endl;
    cout << RED    "|  [M] Back to Main Menu               |" RESET << endl;

    cout << "+--------------------------------------+" << endl;
    cout << "Enter your choice: ";
    while (true) {
        cin >> choiceServices;
        if (choiceServices == 'm' || choiceServices == 'a' ||
            choiceServices == 'b' || choiceServices == 'c' || choiceServices == 'M' || choiceServices == 'A' ||
            choiceServices == 'B' || choiceServices == 'C') {
            break;
        }
        else {
            cout << RED << "Invalid input! Please enter again \n" << RESET;
            cout << "Enter your choice: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    switch (choiceServices) {
    case 'A': case 'a':
        showCondoPage(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
        break;
    case 'B': case 'b':
        showBungalowPage(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
        break;
    case 'C': case 'c':
        showHousePage(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
    case 'M': case 'm':
        return;
    default:
        cout << RED "Invalid choice, please try again." RESET << endl;
    }
}

void showCondoPage(Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice) {
    system("CLS");

    cout << BLUE "+----------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|                                                       Skyline Residences                                                               |" << endl;
    cout << "+----------------------------------------------------------------------------------------------------------------------------------------+" RESET << endl;

    cout << YELLOW "| Skyline Residences is a modern high-rise condominium designed for urban living, offering breathtaking city views and top-tier          | " << endl;
    cout << "|  amenities. With contemporary architecture and luxurious interiors, it provides a sophisticated lifestyle in the heart of the city.    |" RESET << endl;

    cout << GREEN "| Benefits:                                                                                                                              |" << endl;
    cout << "| 1. Prime Location – Close to business districts, shopping malls, and entertainment hubs.                                               |" << endl;
    cout << "| 2. Stunning Views – Panoramic skyline and sunset views from high-rise floors.                                                          |" << endl;
    cout << "| 3. Premium Amenities – Includes pools, gym, co-working spaces, and 24/7 security.                                                      |" << endl;
    cout << "| 4. Smart Living – Equipped with smart home technology.                                                                                 |" << endl;
    cout << "| 5. Investment Value – High rental demand and great resale potential.                                                                   |" RESET << endl;

    cout << "+----------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    askForHouse("Condominium", "Skyline Residences ", "3 Bedroom & 2 Bathroom", "Jalan Jalil 2, Bukit Jalil, Kuala Lumpur", services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
}

void showBungalowPage(Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice) {
    system("CLS");

    cout << BLUE "+----------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|                                                                       Evergreen Cottage                                                                  |" << endl;
    cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------+" RESET << endl;

    cout << YELLOW "| Evergreen Cottage is a charming bungalow that blends comfort and nature, offering a peaceful retreat for families and retirees.                          |" RESET << endl;

    cout << GREEN "| Benefits:                                                                                                                                                |" << endl;
    cout << "| 1. Serene Atmosphere – Located in a quiet, nature-filled area for relaxation.                                                                            |" << endl;
    cout << "| 2. Spacious Living – Large interiors and outdoor space for gatherings.                                                                                   |" << endl;
    cout << "| 3. Energy Efficiency – Built with eco-friendly materials and natural ventilation.                                                                        |" << endl;
    cout << "| 4. Privacy & Security – Standalone property with a gated entrance.                                                                                       |" << endl;
    cout << "| 5. Customizable Design – Freedom to renovate as per lifestyle needs.                                                                                     |" RESET << endl;

    cout << "+----------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    askForHouse("Bungalow", "Evergreen Cottage", "8 Bedroom & 6 Bathroom", "Taman Pantai Bangsar, Bangsar, Kuala Lumpur", services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
}

void showHousePage(Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice) {
    system("CLS");

    cout << BLUE "+------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "|                                                           Amberwood Residences                                                           |" << endl;
    cout << "+------------------------------------------------------------------------------------------------------------------------------------------+" RESET << endl;

    cout << YELLOW "| Amberwood Residences is a stylish terrace housing development offering modern design and a warm community environment.                   |" RESET << endl;

    cout << GREEN "| Benefits:                                                                                                                                |" << endl;
    cout << "| 1. Community Living – Encourages a friendly and connected neighborhood.                                                                  |" << endl;
    cout << "| 2. Modern & Stylish Design – Contemporary architecture with functional layouts.                                                          |" << endl;
    cout << "| 3. Convenient Accessibility – Close to schools, supermarkets, and public transport.                                                      |" << endl;
    cout << "| 4. Affordable Luxury – High-quality living at a reasonable price.                                                                        |" << endl;
    cout << "| 5. Low Maintenance – Easy upkeep compared to larger properties.                                                                          |" RESET << endl;

    cout << "+------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    askForHouse("Terrace house", "Amberwood Residences ", "6 Bedroom & 4 Bathroom", "City of Elmina, Shah Alam, Selangor", services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
}
void askForHouse(const string& service, const string& rental, const string& experience, const string& location,
    Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice) {
    char choiceproperty;

    cout << YELLOW "\nAre you interested to know more about this property? (y/n): " RESET;
    while (true) {
        cin >> choiceproperty;

        if (choiceproperty == 'y' || choiceproperty == 'Y') {
            system("CLS");

            cout << CYAN "+------------------------------------------------+" << endl;
            cout << "|          Property Details                      |" << endl;
            cout << "+------------------------------------------------+" RESET << endl;

            cout << GREEN " Property Type         : " RESET << service << endl;
            cout << GREEN " Property Name         : " RESET << rental << endl;
            cout << GREEN " Rooms & Bathrooms     : " RESET << experience << endl;
            cout << GREEN " Location              : " RESET << location << endl;

            cout << "\n" YELLOW "Press Enter to go back to the Services Menu..." RESET << endl;
            cin.ignore();
            cin.get();
            custMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
        }
        else if (choiceproperty == 'n' || choiceproperty == 'N') {
            custMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
            return;
        }
        else {
            cout << RED "Invalid input! Please enter 'y' or 'n'." RESET << endl;
            cout << YELLOW"Please Enter It again :" << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}


string generateBookingID() {
    static int bookingCounter = 0;  // Local static variable to keep track of the booking count
    bookingCounter++;
    return "BID" + to_string(bookingCounter);
}



void displayCalendar(Rental rentals[], Service services[], int serviceChoice, int unitChoice) {
    system("cls");

    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << BLUE << "                           Availability Calendar - May 2024                    " << RESET << endl;
    cout << CYAN << "*******************************************************************************\n" << RESET;

    cout << GREEN << "Property: " << RESET << services[serviceChoice].propertyName << "  ";
    cout << GREEN << "Unit: " << RESET << services[serviceChoice].units[unitChoice].unitName << endl;

    cout << "-----------------------------------------------------------\n";
    cout << "\033[1;33m  Sun   Mon   Tue   Wed   Thu   Fri   Sat \033[0m\n";
    cout << "-----------------------------------------------------------\n";

    int firstDayOffset = 2; // May 1, 2024, starts on Wednesday (Offset for alignment)

    // Print leading spaces for the first week
    for (int i = 0; i < firstDayOffset; i++) {
        cout << "      ";
    }

    // Print calendar days with booking and maintenance status
    for (int day = 1; day <= 31; day++) {
        if (services[serviceChoice].units[unitChoice].maintenanceDates[day - 1]) {
            cout << "\033[1;44m " << setw(2) << day << " M \033[0m";  // 🔵 Maintenance (Blue Background)
        }
        else if (services[serviceChoice].units[unitChoice].bookedDates[day - 1]) {
            cout << "\033[1;41m " << setw(2) << day << " X \033[0m";  // 🔴 Booked (Red Background)
        }
        else {
            cout << "\033[1;42m " << setw(2) << day << " O \033[0m";  // 🟢 Available (Green Background)
        }

        // Newline after every Saturday (7-day week)
        if ((day + firstDayOffset) % 7 == 0 || day == 31) {
            cout << endl;
        }
    }


    cout << "-----------------------------------------------------------\n";
    cout << GREEN << "Available = \033[1;42m O \033[0m   "
        << RED << " Unavailable = \033[1;41m X \033[0m   "
        << BLUE << " Maintenance = \033[1;44m M \033[0m" << endl;
}

void staffAccountSelection(Service services[], Rental rentals[], Booking bookings[], int bookingCount, int rentalsindex, int serviceChoice) {
    int staffStartChoice = 0;
    do {
        system("cls");
        cout << CYAN << "********************************************************************************" << RESET << endl;
        cout << BLUE << "|                               PrimeStay Properties                           |" << RESET << endl;
        cout << CYAN << "********************************************************************************" << RESET << endl;
        cout << GREEN << "| You are now in admin menu!                                                   |" << RESET << endl;
        cout << "|                                                                              |" << endl;
        cout << "|                             1: Admin Login                                   |" << endl;
        cout << "|                             2: Back to Main Menu                             |" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        while (true) {
            cout << "Enter your choice (1 or 2): ";
            cin >> staffStartChoice;

            if (!cin.fail() && (staffStartChoice == 1 || staffStartChoice == 2)) {
                break;
            }
            cout << RED << "Invalid option! Please try again.\n" << RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        switch (staffStartChoice) {
        case 1:
            staffLogin(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
            break;
        case 2:
            startMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
            break;
        default:
            break;
        }

    } while (staffStartChoice < 1 || staffStartChoice > 2);
}

void staffLogin(Service services[], Rental rentals[], Booking bookings[], int bookingCount, int rentalsindex, int servicechoice) {
    system("cls");
    cout << CYAN << "********************************************************************************" << RESET << endl;
    cout << BLUE << "|                               PrimeStay Properties                           |" << RESET << endl;
    cout << CYAN << "********************************************************************************" << RESET << endl;

    string adminusername = "admin123";
    string adminpassword = "pass123";
    string adminusernameInput = " ";
    string adminpasswordInput = " ";
    string choice;

    cout << YELLOW << "You are now in admin mode!\n " << RESET;
    cout << YELLOW << "Press B to go back or Press Other Key to continue:" << RESET;
    cin.ignore();
    getline(cin, choice);

    if (choice == "b" || choice == "B") {
        staffAccountSelection(services, rentals, bookings, bookingCount, rentalsindex, servicechoice);
        return; // Ensure function exits after going back
    }


    while (true) {
        cout << "Enter Admin Username: ";
        getline(cin, adminusernameInput);
        if (adminusernameInput != adminusername) {
            cout << RED << "Invalid username, please try again!\n" << RESET << endl;
        }
        else {
            break;
        }
    }

    while (true) {
        cout << "\nEnter Admin Password: ";
        cin >> adminpasswordInput;
        if (adminpasswordInput != adminpassword) {
            cout << RED << "Invalid password, please try again!\n" << RESET << endl;
        }
        else {
            adminMenu(services, rentals, bookings, bookingCount, rentalsindex, servicechoice);
            break;
        }
    }
}
//admin Menu
void adminMenu(Service services[], Rental rentals[], Booking bookings[], int bookingCount, int rentalsindex, int servicechoice) {
    int adminChoice = 0;
    do {
        system("cls");
        cout << CYAN << "********************************************************************************" << RESET << endl;
        cout << BLUE << "|                              PrimeStay Properties                            |" << RESET << endl;
        cout << CYAN << "********************************************************************************" << RESET << endl;
        cout << GREEN << "| Welcome to Admin Management Console!                                         |" << RESET << endl;
        cout << "|                                                                              |" << endl;
        cout << "|                             1: View Schedule                                 |" << endl;
        cout << "|                             2: View Customers                                |" << endl;
        cout << "|                             3: View Sales Report                             |" << endl;
        cout << "|                             4: Maintenance Menu                              |" << endl;
        cout << "|                             5: Logout                                        |" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        while (true) {
            cout << "Enter your choice (1 to 5): ";
            cin >> adminChoice;
            if (!cin.fail() && adminChoice >= 1 && adminChoice <= 5) {
                break;
            }

            cout << RED << "Invalid option! Please try again.\n" << RESET << endl;
            cin.clear();  // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Remove leftover invalid input
        }

        switch (adminChoice) {
        case 1:
            searchBookings(services, rentals, bookings, bookingCount);
            cin.get();
            adminMenu(services, rentals, bookings, bookingCount, rentalsindex, servicechoice);
            break;
        case 2:
            readCustomerDetails(services, rentals, bookings, bookingCount, rentalsindex, servicechoice);
            break;
        case 3:
            salesReport(services, rentals, bookings, bookingCount, rentalsindex, servicechoice);
            break;
        case 4:
            maintenanceMenu(services, rentals, bookings, bookingCount, rentalsindex, servicechoice);
            break;
        case 5: 
            startMenu(services, rentals, bookings, bookingCount, rentalsindex, servicechoice);
            break;

        default:
            break;
        }
    } while (adminChoice < 1 || adminChoice > 5);
}

void readCustomerDetails(Service services[], Rental rentals[], Booking bookings[], int bookingCount, int rentalsindex, int serviceChoice) {
    system("cls");
    ifstream infile;
    string fullname, Useremail;
    int phoneNumber;

    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << BLUE << "                              PrimeStay Properties                             " << RESET << endl;
    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << GREEN << "                               Customer Details                                " << RESET << endl;
    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << YELLOW << setw(25) << "Full Name" << setw(25) << "Email" << setw(25) << "Phone No." << RESET << endl;
    cout << "********************************************************************************" << endl;

    infile.open("UsersDatabase.txt");
    infile >> fullname >> Useremail >> phoneNumber;

    while (!infile.eof()) {
        cout << setw(25) << fullname << setw(25) << Useremail << setw(25) << phoneNumber << "\n";
        infile >> fullname >> Useremail >> phoneNumber;
    }
    infile.close();
    cout << "\n\nPress Enter to go back to admin menu! " << endl;
    cin.ignore();
    cin.get(); // Wait for user input
    adminMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
}
void salesReport(Service services[], Rental rentals[], Booking bookings[], int bookingCount, int rentalsindex, int serviceChoice) {
    double totalRevenue = 0.0;
    // Track the number of bookings per expert
    int rentalBookings[3][2] = { {0, 0}, {0, 0}, {0, 0} };

    system("cls");
    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << BLUE << "                                PrimeStay Properties                            " << RESET << endl;
    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << GREEN << "\nSales Report\n" << RESET;
    cout << "-------------------------------------------------------------------------------------------------------------------\n";
    cout << YELLOW << left << setw(20) << "Customer Name"
        << setw(35) << "Property Name"
        << setw(20) << "Unit Name"
        << setw(15) << "Check-In Date"
        << setw(15) << "Stay duration"
        << setw(10) << "Currency"
        << setw(10) << "Price" << RESET << "\n";


    cout << "-------------------------------------------------------------------------------------------------------------------\n";


    int totalBookings = 0;

    for (int i = 0; i < bookingCount; i++) {
        cout << left << setw(20) << bookings[i].customerName
            << setw(30) << bookings[i].propertyName
            << setw(20) << bookings[i].unitName
            << setw(15) << bookings[i].checkInDate
            << setw(15) << bookings[i].nights
            << setw(10) << fixed << setprecision(2) << bookings[i].price << "\n";

        totalRevenue += bookings[i].price;
        totalBookings++;
    }

    cout << "-------------------------------------------------------------------------------------------------------------------\n";
    cout << GREEN << "Total Bookings: " << totalBookings << "\n" << RESET;
    cout << GREEN << "Total Revenue: RM " << fixed << setprecision(2) << totalRevenue << "\n" << RESET;
    cout << "------------------------------------------------------------------------------------------------------------\n";
    // Wait for admin input
    cout << RED << "\nPress Enter to continue..." << RESET;
    cin.ignore();
    cin.get();
    adminMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
}

void bookAppointment(Service services[], Rental rentals[], Booking bookings[], int& bookingCount, int rentalsindex, int servicechoice) {
    system("cls");  // Clear previous content
    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << BLUE << "                                PrimeStay Properties                           " << RESET << endl;
    cout << CYAN << "*******************************************************************************" << RESET << endl;

    if (bookingCount >= 100) {
        cout << RED << "All bookings are full. Please try again later.\n" << RESET;
        return;
    }
    string choice;
    cout << YELLOW << "Press B to go back or Press Other Key to continue:" << RESET;
    cin.ignore();
    getline(cin, choice);

    if (choice == "b" || choice == "B") {
        custMenu(services, rentals, bookings, bookingCount, rentalsindex, servicechoice);
        return; // Ensure function exits after going back
    }

    Booking newBooking;
    newBooking.bookingID = generateBookingID();
    cout << GREEN << "Please Enter Your Name: " << RESET;
    cin.ignore();
    getValidName(newBooking.customerName);

    system("cls");
    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << BLUE << "                               PrimeStay Properties                            " << RESET << endl;
    cout << CYAN << "*******************************************************************************\n" << RESET;

    // Choose Property
    cout << GREEN << "Available Properties:\n" << RESET;
    for (int i = 0; i < 3; i++) {
        cout << YELLOW << i + 1 << ". " << services[i].propertyName << RESET << "\n";
    }

    int serviceChoice;
    while (true) {
        cout << GREEN << "Select a property (1-3): " << RESET;
        cin >> serviceChoice;

        if (serviceChoice < 1 || serviceChoice > 3) {
            cout << RED << "Invalid selection.\n" << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    serviceChoice--;

    system("cls");
    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << BLUE << "                               PrimeStay Properties                            " << RESET << endl;
    cout << CYAN << "*******************************************************************************\n" << RESET;

    // Display Units
    cout << GREEN << "Available Units for " << services[serviceChoice].propertyName << ":\n" << RESET;
    for (int i = 0; i < 2; i++) {
        cout << YELLOW << i + 1 << ". " << services[serviceChoice].units[i].unitName
            << " - RM " << services[serviceChoice].units[i].price << RESET << "\n";
    }

    int unitChoice;
    while (true) {
        cout << GREEN << "Select a unit (1-2): " << RESET;
        cin >> unitChoice;

        if (unitChoice < 1 || unitChoice > 2) {
            cout << RED << "Invalid selection.\n" << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    unitChoice--;
    system("cls");
    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << BLUE << "                               PrimeStay Properties                            " << RESET << endl;
    cout << CYAN << "*******************************************************************************\n" << RESET;
    // Display Calendar
    displayCalendar(rentals, services, serviceChoice, unitChoice);

    int checkInDay, checkoutDate;
    while (true) {
        cout << GREEN << "Enter Check-In Day (1-31): " << RESET;
        cin >> checkInDay;

        cout << GREEN << "Enter Check Out Date (1-31): " << RESET;
        cin >> checkoutDate;

        if (checkInDay < 1 || checkoutDate > 31 || checkoutDate <= checkInDay) {
            cout << RED << "Invalid booking dates.\n" << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }

    // Check availability
    bool available = true;
    for (int i = checkInDay - 1; i < checkoutDate; i++) {
        if (services[serviceChoice].units[unitChoice].bookedDates[i] ||
            services[serviceChoice].units[unitChoice].maintenanceDates[i]) { // Check maintenance
            available = false;
            break;
        }
    }

    if (!available) {
        cout << RED << "\nBooking Failed: Selected dates are unavailable due to a booking or maintenance!\n" << RESET;
        return;
    }

    // Confirm Check-In and Book Dates
    for (int i = checkInDay - 1; i < checkoutDate; i++) {
        services[serviceChoice].units[unitChoice].bookedDates[i] = true;
    }

    // Save booking
    newBooking.propertyName = services[serviceChoice].propertyName;
    newBooking.unitName = services[serviceChoice].units[unitChoice].unitName;
    newBooking.nights = checkoutDate - checkInDay;
    newBooking.checkInDate = 20250500 + checkInDay;
    newBooking.checkoutDate = 20250500 + checkoutDate;
    newBooking.price = services[serviceChoice].units[unitChoice].price * newBooking.nights;

    system("cls");

    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << BLUE << "                             PrimeStay Properties                              " << RESET << endl;
    cout << CYAN << "*******************************************************************************\n" << RESET;
    cout << YELLOW << "Please press Enter to proceed to continue." << RESET;
    cin.ignore();
    cin.get();
    double originalPrice = services[serviceChoice].units[unitChoice].price * newBooking.nights;
    double discount = 0.0;

    if (newBooking.nights >= 30) {
        discount = 0.25;
    }
    else if (newBooking.nights >= 20) {
        discount = 0.20;
    }
    else if (newBooking.nights >= 10) {
        discount = 0.10;
    }

    newBooking.price = originalPrice * (1 - discount);

    cout << GREEN << "Booking Successful!\n" << RESET;
    cout << YELLOW << "Total Nights: " << newBooking.nights << RESET << "\n";
    cout << YELLOW << "Original Price: RM " << fixed << setprecision(2) << originalPrice << RESET << "\n";
    cout << YELLOW << "Discount Applied: " << (discount * 100) << "%" << RESET << "\n";
    cout << YELLOW << "Final Price: RM " << fixed << setprecision(2) << newBooking.price << RESET << "\n";

    bookings[bookingCount++] = newBooking;

    cin.ignore();
    system("cls");

    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << BLUE << "                             PrimeStay Properties                              " << RESET << endl;
    cout << CYAN << "*******************************************************************************\n" << RESET;
    cout << YELLOW << "Please press Enter to proceed to payment." << RESET;
    cin.get();
    paymentPage(services, rentals, newBooking, bookings, bookingCount, rentalsindex, serviceChoice);
}

// Validate Card Number (must be 12 digits)
bool isValidCardNumber(const string& cardNumber) {
    if (cardNumber.length() != 12) return false;
    return all_of(cardNumber.begin(), cardNumber.end(), ::isdigit);
}

// Validate CVV (must be 3 digits)
bool isValidCVV(const string& cvv) {
    if (cvv.length() != 3) return false;
    return all_of(cvv.begin(), cvv.end(), ::isdigit);
}

void paymentPage(Service services[], Rental rentals[], Booking& booking, Booking bookings[], int& bookingCount, int rentalsindex, int serviceChoice) {
    string cardNumber, expiryDate, cvv;
    system("cls");

    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << BLUE << "                                PrimeStay Properties                           " << RESET << endl;
    cout << CYAN << "*******************************************************************************\n" << RESET;

    cout << GREEN << "Proceeding to Payment\n" << RESET;
    cout << YELLOW << "Your Booking Rental:" << booking.propertyName << RESET << "\n";
    cout << YELLOW << "Your Booking Unit:" << booking.unitName << RESET << "\n";
    cout << YELLOW << "Your Check in Date:" << booking.checkInDate << RESET << "\n";
    cout << YELLOW << "Your Staying Period(nights):" << booking.nights << RESET << "\n";
    cout << YELLOW << "Booking Price: RM " << fixed << setprecision(2) << booking.price << RESET << "\n";

    // Get Card Number
    do {
        cout << GREEN << "Enter 12-digit Card Number: " << RESET;
        cin >> cardNumber;
        if (!isValidCardNumber(cardNumber)) {
            cout << RED << "Invalid card number. Please enter exactly 12 digits.\n" << RESET;
        }
    } while (!isValidCardNumber(cardNumber));

    // Get Expiry Date

    do {
        cout << GREEN << "Enter Expiry Date (MM/YY): " << RESET;
        cin >> expiryDate;
        if (!isValidExpiryDate(expiryDate)) {
            cout << RED"Invalid Expiry Date  (MM must be 1-12 or need /)" << RESET << endl;
        }
    } while (!isValidExpiryDate(expiryDate));



    // Get CVV
    do {
        cout << GREEN << "Enter 3-digit CVV: " << RESET;
        cin >> cvv;
        if (!isValidCVV(cvv)) {
            cout << RED << "Invalid CVV. Please enter exactly 3 digits.\n" << RESET;
        }
    } while (!isValidCVV(cvv));

    cout << GREEN << "\nPayment Successful! Your booking is confirmed.\n" << RESET;
    system("cls");
    bookingSummaryPage(booking);
    cin.ignore();
    cin.get();
    cout << YELLOW << "Press Enter to return to the customer menu." << RESET;
    cin.ignore();
    cin.get();
    custMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);

}
void bookingSummaryPage(const Booking& booking) {
    cout << CYAN"*******************************************************************************" << endl;
    cout << BLUE"                            PrimeStay Properties                               " << endl;
    cout << CYAN"*******************************************************************************\n" << endl;
    cout << YELLOW"\nBooking Summary\n";
    cout << YELLOW"Booking ID: " << booking.bookingID << "\n";
    cout << YELLOW"Customer Name: " << booking.customerName << "\n";
    cout << YELLOW"Property Name: " << booking.propertyName << "\n";
    cout << YELLOW"Unit Name: " << booking.unitName << "\n";
    cout << YELLOW"Check In Date: " << booking.checkInDate << "\n";
    cout << YELLOW"Total nights:" << booking.nights << "\n";
    cout << YELLOW"Total Price: $" << booking.price << "\n";
}


void searchBookings(Service service[], Rental rentals[], Booking bookings[], int bookingCount) {
    system("cls");
    cout << CYAN "*******************************************************************************" RESET << endl;
    cout << CYAN "                                     PrimeStay Properties                      " RESET << endl;
    cout << CYAN "*******************************************************************************\n" RESET << endl;
    string search;
    cin.ignore();
    cout << YELLOW "Enter The Customer Name or the Property Name: " RESET;
    cout << "(or leave empty to display all): ";
    getline(cin, search);
    sortBookingsByDate(bookings, bookingCount);
    displayData(bookings, bookingCount, search);
    cout << YELLOW"Please Enter to go back customer main menu";
    return;
}
bool compareByDate(const Booking& a, const Booking& b) {
    return a.date < b.date; "";
}
void sortBookingsByDate(Booking bookings[], int bookingCount) {
    sort(bookings, bookings + bookingCount, compareByDate);
}
void displayData(Booking bookings[], int bookingCount, const string& search) {
    bool found = false;
    for (int i = 0; i < bookingCount; i++) {
        if (search.empty() || bookings[i].customerName == search) {
            found = true;
            cout << CYAN "------------------------------------------------\n" RESET;
            cout << YELLOW "Booking Id     : " RESET << bookings[i].bookingID << endl;
            cout << GREEN "Name           : " RESET << bookings[i].customerName << endl;
            cout << BLUE "Price          : " RESET << bookings[i].price << endl;
            cout << GREEN "Property Name  : " RESET << bookings[i].propertyName << endl;
            cout << GREEN "Unit Name      : " RESET << bookings[i].unitName << endl;
            cout << YELLOW "Check-in Date  : " RESET << bookings[i].checkInDate << endl;
            cout << GREEN "Total Nights   : " RESET << bookings[i].nights << endl;
            cout << CYAN "------------------------------------------------\n" RESET;
        }
    }

    if (!found) {
        cout << RED "No bookings found.\n" RESET;
    }
}




void deleteAppointment(Booking bookings[], int& bookingCount, Service services[]) {
    system("cls");
    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << CYAN << "                                     PrimeStay Properties                      " << RESET << endl;
    cout << CYAN << "*******************************************************************************\n" << RESET << endl;

    if (bookingCount == 0) {
        cout << RED << "No bookings to delete.\n" << RESET;
        cin.ignore();
        cin.get();
        return;
    }

    string bookingID;
    cout << GREEN << "Enter Booking ID to delete: " << RESET;
    cin >> bookingID;

    // Find the booking by its ID
    int bookingIndex = -1;
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].bookingID == bookingID) {
            bookingIndex = i;
            break;
        }
    }

    if (bookingIndex == -1) {
        cout << RED << "Booking ID not found.\n" << RESET;
        cout << RED << "Press Enter to go back.\n" << RESET;
        cin.ignore();
        cin.get();
        return;
    }

    // Find the correct property and unit
    int propertyIndex = -1, unitIndex = -1;
    for (int i = 0; i < 3; i++) {  // Assuming 3 properties
        if (services[i].propertyName == bookings[bookingIndex].propertyName) {
            propertyIndex = i;
            for (int j = 0; j < 2; j++) { // Each property has 2 units
                if (services[i].units[j].unitName == bookings[bookingIndex].unitName) {
                    unitIndex = j;
                    break;
                }
            }
            break;
        }
    }

    if (propertyIndex == -1 || unitIndex == -1) {
        cout << RED << "Error: Rental property or unit not found.\n" << RESET;
        return;
    }

    // Extract check-in and check-out days correctly
    int checkInDay = bookings[bookingIndex].checkInDate;
    int checkoutDay = bookings[bookingIndex].checkoutDate;

    // Unmark the booked dates in the correct unit
    for (int i = checkInDay - 1; i < checkoutDay; i++) {
        services[propertyIndex].units[unitIndex].bookedDates[i] = false;
    }

    // Shift bookings to remove the deleted booking
    for (int i = bookingIndex; i < bookingCount - 1; i++) {
        bookings[i] = bookings[i + 1];
    }

    bookingCount--;

    cout << GREEN << "Booking successfully deleted.\n" << RESET;
}

void getValidName(string& customerName) {
    regex alphaRegex("^[A-Za-z ]+$");  // Allows only letters and spaces

    while (true) {
        cout << GREEN << "Please Enter Your Name: " << RESET;
        getline(cin, customerName);

        if (regex_match(customerName, alphaRegex)) {
            break;
        }
        else {
            cout << RED << "Invalid name! Please enter only alphabetic characters.\n" << RESET;
        }
    }
}

void searchAndModifyBooking(Booking bookings[], int bookingCount, Rental rentals[], Service services[], int serviceChoice) {
    system("cls");
    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << BLUE << "                                PrimeStay Properties                           " << RESET << endl;
    cout << CYAN << "*******************************************************************************\n" << RESET << endl;

    string choose;
    cout << YELLOW << "Press B to go back or Press Other Key to continue:" << RESET;
    cin.ignore();
    getline(cin, choose);

    if (choose == "b" || choose == "B") {
        return; // Ensure function exits after going back
    }
    string bookingID;
    cout << GREEN << "Enter Booking ID to search: " << RESET;
    cin >> bookingID;

    int bookingIndex = -1;
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].bookingID == bookingID) {
            bookingIndex = i;
            break;
        }
    }
    if (bookingIndex == -1) {
        cout << RED << "Booking not found!\n" << RESET;
        return;
    }

    Booking& booking = bookings[bookingIndex];
    cout << YELLOW << "Booking Details:\n" << RESET;
    cout << "Property: " << booking.propertyName << "\n";
    cout << "Unit: " << booking.unitName << "\n";
    cout << "Check-in Date: " << booking.checkInDate << "\n";
    cout << "Nights: " << booking.nights << "\n";
    cout << "Total Price: RM " << fixed << setprecision(2) << booking.price << "\n";

    char choice;
    cout << GREEN << "Do you want to modify the check-in date? (y/n): " << RESET;
    cin >> choice;
    if (tolower(choice) != 'y') return;

    int newCheckInDate, newCheckoutDate;
    while (true) {
        cout << GREEN << "Enter new Check-In Day (1-31): " << RESET;
        cin >> newCheckInDate;

        cout << GREEN << "Enter new Check-Out Date (1-31): " << RESET;
        cin >> newCheckoutDate;

        if (newCheckInDate < 1 || newCheckoutDate > 31 || newCheckoutDate <= newCheckInDate) {
            cout << RED << "Invalid dates. Please enter valid check-in and check-out dates.\n" << RESET;
        }
        else {
            break;
        }
    }

    // Find the correct property and unit
    int propertyIndex = -1, unitIndex = -1;
    for (int i = 0; i < 3; i++) {
        if (services[i].propertyName == booking.propertyName) {
            propertyIndex = i;
            for (int j = 0; j < 2; j++) {
                if (services[i].units[j].unitName == booking.unitName) {
                    unitIndex = j;
                    break;
                }
            }
            break;
        }
    }

    if (propertyIndex == -1 || unitIndex == -1) {
        cout << RED << "Error: Property or Unit not found.\n" << RESET;
        return;
    }

    // Free old booking dates
    for (int i = booking.checkInDate % 100 - 1; i < booking.checkoutDate % 100; i++) {
        services[propertyIndex].units[unitIndex].bookedDates[i] = false;
    }

    // Check new date availability
    bool available = true;
    for (int i = newCheckInDate - 1; i < newCheckoutDate; i++) {
        if (services[propertyIndex].units[unitIndex].bookedDates[i]) {
            available = false;
            break;
        }
    }

    if (!available) {
        cout << RED << "New dates are unavailable!\n" << RESET;
        return;
    }

    // Apply new booking dates
    for (int i = newCheckInDate - 1; i < newCheckoutDate; i++) {
        services[propertyIndex].units[unitIndex].bookedDates[i] = true;
    }
    //calculate update price
    booking.nights = newCheckoutDate - newCheckInDate;
    double originalPrice = services[propertyIndex].units[unitIndex].price * booking.nights;
    double discount = 0.0;

    if (booking.nights >= 30) {
        discount = 0.25;  // 25% discount
    }
    else if (booking.nights >= 20) {
        discount = 0.20;  // 20% discount
    }
    else if (booking.nights >= 10) {
        discount = 0.10;  // 10% discount
    }
    // Update booking details
    booking.checkInDate = 20250500 + newCheckInDate;
    booking.checkoutDate = 20250500 + newCheckoutDate;
    booking.nights = newCheckoutDate - newCheckInDate;
    booking.price = originalPrice * (1 - discount);

    cout << GREEN << "Booking updated successfully!\n" << RESET;
    cout << YELLOW << "New Total Nights: " << booking.nights << RESET << "\n";
    cout << YELLOW << "Original Price: RM " << fixed << setprecision(2) << originalPrice << RESET << "\n";
    cout << YELLOW << "Discount Applied: " << (discount * 100) << "%" << RESET << "\n";
    cout << YELLOW << "Final Price: RM " << fixed << setprecision(2) << booking.price << RESET << "\n";
}

void scheduleMaintenance(Service services[]) {
    system("cls");
    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << BLUE << "                            Schedule Maintenance                              " << RESET << endl;
    cout << CYAN << "*******************************************************************************\n" << RESET;

    // Select property
    cout << GREEN << "Available Properties:\n" << RESET;
    for (int i = 0; i < 3; i++) {
        cout << YELLOW << i + 1 << ". " << services[i].propertyName << RESET << "\n";
    }

    int serviceChoice;
    while (true) {
        cout << GREEN << "Select a property (1-3): " << RESET;
        cin >> serviceChoice;

        if (serviceChoice < 1 || serviceChoice > 3) { // Fixed condition
            cout << RED << "Invalid selection.\n" << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    serviceChoice--;
    system("cls");
    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << BLUE << "                            Schedule Maintenance                              " << RESET << endl;
    cout << CYAN << "*******************************************************************************\n" << RESET;
    // Select unit
    cout << GREEN << "Available Units for " << services[serviceChoice].propertyName << ":\n" << RESET;
    for (int i = 0; i < 2; i++) {
        cout << YELLOW << i + 1 << ". " << services[serviceChoice].units[i].unitName << RESET << "\n";
    }

    int unitChoice;
    while (true) {
        cout << GREEN << "Select a unit (1-2): " << RESET;
        cin >> unitChoice;

        if (unitChoice < 1 || unitChoice > 2) {
            cout << RED << "Invalid selection.\n" << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    unitChoice--;
    system("cls");
    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << BLUE << "                            Schedule Maintenance                              " << RESET << endl;
    cout << CYAN << "*******************************************************************************\n" << RESET;
    // Enter maintenance dates
    int startDate, endDate;
    while (true) {
        cout << GREEN << "Enter Start Maintenance Date (1-31): " << RESET;
        cin >> startDate;
        cout << GREEN << "Enter End Maintenance Date (1-31): " << RESET;
        cin >> endDate;

        if (startDate < 1 || endDate > 31 || endDate < startDate) {
            cout << RED << "Invalid dates. Try again.\n" << RESET;
        }
        else {
            break;
        }
    }

    // Mark the unit under maintenance and block bookings
    for (int i = startDate - 1; i < endDate; i++) {
        services[serviceChoice].units[unitChoice].maintenanceDates[i] = true;
        services[serviceChoice].units[unitChoice].bookedDates[i] = true;  // Block bookings
    }

    cout << GREEN << "Maintenance scheduled successfully!\n" << RESET;
}
void viewAndModifyMaintenance(Service services[]) {
    system("cls");
    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << BLUE << "                          View & Modify Maintenance                           " << RESET << endl;
    cout << CYAN << "*******************************************************************************\n" << RESET;

    // Display available properties
    cout << GREEN << "Available Properties:\n" << RESET;
    for (int i = 0; i < 3; i++) {
        cout << YELLOW << i + 1 << ". " << services[i].propertyName << RESET << "\n";
    }

    int serviceChoice;
    while (true) {
        cout << GREEN << "Select a property (1-3): " << RESET;
        cin >> serviceChoice;

        if (serviceChoice < 1 || serviceChoice > 3 || cin.fail()) {
            cout << RED << "Invalid selection.\n" << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    serviceChoice--;

    // Select unit
    system("cls");
    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << BLUE << "                          Schedule/Modify Maintenance                         " << RESET << endl;
    cout << CYAN << "*******************************************************************************\n" << RESET;

    cout << GREEN << "Available Units for " << services[serviceChoice].propertyName << ":\n" << RESET;
    for (int i = 0; i < 2; i++) {
        cout << YELLOW << i + 1 << ". " << services[serviceChoice].units[i].unitName << RESET << "\n";
    }

    int unitChoice;
    while (true) {
        cout << GREEN << "Select a unit (1-2): " << RESET;
        cin >> unitChoice;

        if (unitChoice < 1 || unitChoice > 2 || cin.fail()) {
            cout << RED << "Invalid selection.\n" << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    unitChoice--;

    // Display current maintenance dates
    system("cls");
    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << BLUE << "                          View & Modify Maintenance                           " << RESET << endl;
    cout << CYAN << "*******************************************************************************\n" << RESET;

    cout << GREEN << "Scheduled Maintenance Dates:\n" << RESET;
    bool hasMaintenance = false;
    for (int i = 0; i < 31; i++) {
        if (services[serviceChoice].units[unitChoice].maintenanceDates[i]) {
            cout << YELLOW << "Day " << i + 1 << RESET << " ";
            hasMaintenance = true;
        }
    }
    if (!hasMaintenance) {
        cout << RED << "No maintenance scheduled for this unit.\n" << RESET;
    }
    cout << "\n\n";

    // Provide options
    cout << GREEN << "Options:\n" << RESET;
    cout << YELLOW << "1. Schedule a new maintenance date\n";
    cout << "2. Cancel a specific maintenance date\n";
    cout << "3. Clear all maintenance dates\n";
    cout << "4. Exit\n" << RESET;

    int option;
    while (true) {
        cout << GREEN << "Select an option (1-4): " << RESET;
        cin >> option;

        if (option < 1 || option > 4 || cin.fail()) {
            cout << RED << "Invalid option. Try again.\n" << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    system("cls");
    cout << CYAN << "*******************************************************************************" << RESET << endl;
    cout << BLUE << "                          View & Modify Maintenance                           " << RESET << endl;
    cout << CYAN << "*******************************************************************************\n" << RESET;

    // Handle options
    if (option == 1) {
        // Schedule maintenance
        int newDay;
        while (true) {
            cout << GREEN << "Enter the day to schedule maintenance (1-31): " << RESET;
            cin >> newDay;

            if (newDay < 1 || newDay > 31 || cin.fail()) {
                cout << RED << "Invalid day. Try again.\n" << RESET;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                break;
            }
        }
        services[serviceChoice].units[unitChoice].maintenanceDates[newDay - 1] = true;
        cout << GREEN << "Maintenance scheduled for Day " << newDay << "!\n" << RESET;

    }
    else if (option == 2) {
        // Cancel specific maintenance date
        int cancelDay;
        bool validDay = false;

        while (true) {
            cout << GREEN << "Enter the day to cancel maintenance (1-31): " << RESET;
            cin >> cancelDay;

            if (cancelDay < 1 || cancelDay > 31 || cin.fail()) {
                cout << RED << "Invalid day. Try again.\n" << RESET;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (!services[serviceChoice].units[unitChoice].maintenanceDates[cancelDay - 1]) {
                cout << RED << "No maintenance scheduled on this day.\n" << RESET;
            }
            else {
                validDay = true;
                break;
            }
        }

        if (validDay) {
            services[serviceChoice].units[unitChoice].maintenanceDates[cancelDay - 1] = false;
            services[serviceChoice].units[unitChoice].bookedDates[cancelDay - 1] = false; // Free for booking
            cout << GREEN << "Maintenance on Day " << cancelDay << " has been canceled.\n" << RESET;
        }

    }
    else if (option == 3) {
        // Clear all maintenance
        for (int i = 0; i < 31; i++) {
            services[serviceChoice].units[unitChoice].maintenanceDates[i] = false;
            services[serviceChoice].units[unitChoice].bookedDates[i] = false; // Free for booking
        }
        cout << GREEN << "All maintenance dates have been cleared!\n" << RESET;
    }

    cout << GREEN << "\nReturning to menu...\n" << RESET;
    system("pause");
}


void maintenanceMenu(Service services[],Rental rentals[],Booking bookings[],int bookingCount,int rentalsindex,int serviceChoice) {
    int adminChoice = 0;
    do {
        system("cls");
        cout << CYAN << "********************************************************************************" << RESET << endl;
        cout << BLUE << "|                              PrimeStay Properties                            |" << RESET << endl;
        cout << CYAN << "********************************************************************************" << RESET << endl;
        cout << GREEN << "| Welcome to Admin Management Console!                                         |" << RESET << endl;
        cout << "|                                                                              |" << endl;
        cout << "|                             1: Schedule Maintenance                          |" << endl;
        cout << "|                             2: View And Modify Maintenance                   |" << endl;
        cout << "|                             3: Logout                                        |" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        while (true) {
            cout << "Enter your choice (1 to 4): ";
            cin >> adminChoice;
            if (!cin.fail() && adminChoice >= 1 && adminChoice <= 5) {
                break;
            }

            cout << RED << "Invalid option! Please try again.\n" << RESET << endl;
            cin.clear();  // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Remove leftover invalid input
        }

        switch (adminChoice) {
        case 1:
            scheduleMaintenance(services);
            cin.get();
            adminMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
            break;
        case 2:
            viewAndModifyMaintenance(services);
            cin.get();
            adminMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
            break;
        case 3:
            adminMenu(services, rentals, bookings, bookingCount, rentalsindex, serviceChoice);
            break;
        default:
            break;
        }
    } while (adminChoice < 1 || adminChoice > 4);
}
void exitApplication() {
    system("cls");
    cout << BLUE << "*******************************************************************************" << endl;
    cout << "                                PrimeStay Properties                           " << endl;
    cout << "*******************************************************************************\n" << RESET << endl;
    cout << "\n\n" << GREEN << "Thank you for using our application. Hope to see you again!\n" << RESET;
    exit(0);
}
