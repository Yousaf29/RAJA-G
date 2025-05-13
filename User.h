#pragma once
#include <iostream>
#include <string>

class User {
protected:
    int ID;
    char name[20];
    char email[30];
    char password[20];

public:

    //virtual ~User() {}

    virtual void login() {
        std::cout << name << " logged in successfully." << std::endl;
    }

    /* virtual void logout() {
         std::cout << name << " logged out." << std::endl;
     }*/

    virtual void updateProfile() = 0; // Pure virtual function makes User an abstract class
};