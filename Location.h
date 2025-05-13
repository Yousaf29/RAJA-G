#pragma once

#include <iostream>
#include <cstring>

using namespace std;

class Location {
public:
    char name[100];
    float latitude;
    float longitude;
    char nearbyFitnessFacilities[100];
    char runningRoutes[100];
    char cyclingRoutes[100];

public:

    Location() {


    }
    // Constructor
    Location(const char* n, float lat, float lon)
        : latitude(lat), longitude(lon) {
        strcpy_s(name, n);
    }

    void writeToFile() {
        ofstream custome("Location.bin", ios::binary | ios::app);
        custome.write((char*)this, sizeof(*this));
        cout << "Details successfully entered!" << endl;
        custome.close();

    }

    // Getter methods
    const char* getName() { return name; }
    float getLatitude() { return latitude; }
    float getLongitude() { return longitude; }

    // Method to set nearby fitness facility
    void setFitnessFacilities(char* facilities) {
        strcpy_s(nearbyFitnessFacilities, facilities);
        this->writeToFile();

    }

    // Method to set running route
    void setRunningRoutes(char* routes) {
        strcpy_s(runningRoutes, routes);
        this->writeToFile();
    }

    // Method to set cycling route
    void setCyclingRoutes(char* routes) {
        strcpy_s(cyclingRoutes, routes);
        this->writeToFile();
    }

    // Method to display nearby fitness facilities
    void displayFitnessFacilities() {
        cout << "Nearby Fitness Facilities: " << nearbyFitnessFacilities << endl;

    }

    // Method to display running routes
    void displayRunningRoutes() {
        cout << "Running Routes: " << runningRoutes << endl;
    }

    // Method to display cycling routes
    void displayCyclingRoutes() {
        cout << "Cycling Routes: " << cyclingRoutes << endl;
    }
};


