#pragma once

#include "User.h"  // Assuming User is the base class for all user types
#include "RegularUser.h"

#include"Location.h"
#include <iostream>
#include <string>

bool checkExistingAdmin(char* p);

class Admin : public User {
private:
    int MAX_USERS = 100;  // Maximum number of users
    int MAX_TRAINERS = 50;  // Maximum number of trainers
    char adminLevel[30];

     Location l;
    
public:
    // Constructor
    Admin(std::string id, std::string name, std::string password) {

    }
    Admin() {

    }

    // Destructor to clean up pointers
    ~Admin() {

    }


    char* getName() {
        return name;
    }
    char* getpassword() {
        return password;
    }

    // Dashboard display methods
    void displayAllUsers() {
         RegularUser p[2];
         std::ifstream inFile("RegularUser.bin", std::ios::binary);
         if (!inFile) {
             std::cout << "Failed to open the file." << std::endl;
             return;
         }

         std::cout << "Displaying All Users:" << std::endl;
         while (!inFile.eof()) {
             inFile.read((char*)&p, sizeof(p));
         }
         for (int i = 0; i < 2; i++) {
             cout << p[i].getName() << endl;
         }
         inFile.close();





    }
    //void displayTrainerFeedback();
    void setAdminLevel(char* level) {
        strncpy_s(adminLevel, level, sizeof(adminLevel) - 1);
        adminLevel[sizeof(adminLevel) - 1] = '\0';
    }

    // Overridden methods from User
    void login() override {
        system("CLS");
        string name;
        string password;
        cout << "Enter admin username: ";
        cin >> name;
        cout << "Enter password: ";
        cin >> password;

        Admin t;
        ifstream inFile("Admins.bin", ios::binary);
        bool loginSuccessful = false;
        while (!inFile.eof()) {
            inFile.read((char*)&t, sizeof(t));
            cout << t.getName() << endl;
            if (t.getName() == name && t.getpassword() == password) {
                cout << "Login successful!" << endl;
                loginSuccessful = true;
                break;
            }
        }
        inFile.close();
        if (!loginSuccessful) {
            cout << "Invalid username or password. Please try again." << endl;
        }
        if (loginSuccessful == 1) {
            cout << "Login successful" << endl;
            loggedInAsAdmin();
        }
    }
    void loggedInAsAdmin() {
        int choice = 0;
        bool exitMenu = false;

        while (!exitMenu) {
            system("CLS");  // Clear the screen
            cout << "Admin Dashboard" << endl;
            cout << "1. Display All Users" << endl;
            cout << "2. Display Trainer Feedback" << endl;
            cout << "3. Update Profile" << endl;
            cout << "4.Set Gym Facilities" << endl;
            cout << "5.Set Cycling Routes" << endl;
            cout << "6.Set Running Routes" << endl;
            cout << "7. Logout" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                displayAllUsers();
                break;
            case 2:
                //displayTrainerFeedback();
                break;

            case 3:
                updateProfile();
                break;
            case 4:

                      this->setLocationFacilities();
                      break;
            case 5:
                      this->setCyclingRoutes();
                      break;
            case 6:
                      this->setRunningRoutes();
                      break;
            case 7:
                cout << "Logging out..." << endl;
                exitMenu = true;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
            }

            if (!exitMenu) {
                cout << "Press any key to continue..." << endl;
                cin.ignore();
                cin.get();  // Pause the console to allow the admin to read the information
            }
        }



    }
    void registerAdmin() {
        char name[20], password[10], level[30];
        int id;
        cout << "Enter admin username: ";
        cin >> name;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter admin level: ";
        cin >> level;
        cout << "Enter ID: ";
        cin >> id;

        ID = id;
        setUserName(name);
        setPassword(password);
        setAdminLevel(level);


        // Check for existing admin
        if (checkExistingAdmin(name)) {
            cout << "Admin username already exists, please login!" << endl;
            login();
        }
        else {
            Admin a;
            a.setUserName(name);
            a.setPassword(password);
            ofstream outFile("Admins.bin", ios::binary | ios::app);
            outFile.write((char*)&a, sizeof(a));
            cout << "Admin registered successfully!" << endl;
            outFile.close();
        }

    }
    void updateProfile()override {
        char name[30];
        cout << "Enter the name:" << endl;
        cin >> name;
        this->setUserName(name);
        cout << "Name change successfully!" << endl;


    }
    void setUserName(char* s) {
        for (int i = 0; i < 20; i++) {
            name[i] = s[i];
        }
    }
    void setPassword(char p1[]) {
        int k = 0;
        while (p1[k] != '\0') {
            password[k] = p1[k];
            k++;
        }
        password[9] = '\0';

    }
    void setLocationFacilities() {
        char gymFacilities[30];
        cout << "Enter gym facilities" << endl;
        cin >> gymFacilities;
        l.setFitnessFacilities(gymFacilities);
    }
    void setRunningRoutes() {
        cout << "Enter running routes" << endl;
        char ru[30];
        cin >> ru;
        l.setRunningRoutes(ru);
    }
    void setCyclingRoutes() {
        cout << "Enter cycling routes" << endl;
        char cy[30];
        cin >> cy;
        l.setCyclingRoutes(cy);
    }




};

bool checkExistingAdmin(char* name) {
    std::ifstream inFile("Admins.bin", std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open Admins.bin for reading." << std::endl;
        return false;  // Early return if file opening fails
    }

    Admin temp;
    while (inFile.read((char*)&temp, sizeof(temp))) {
        if (strcmp(temp.getName(), name) == 0) {
            return true;
        }
    }

    if (inFile.eof()) {
        std::cout << "End of file reached." << std::endl;
    }
    else if (inFile.fail()) {
        std::cerr << "Read failed before reaching end of file." << std::endl;
    }

    inFile.close();
    return false;
}


