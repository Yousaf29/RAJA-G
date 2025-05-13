#pragma once


#include <iostream>
#include <string>
using namespace std;
class Workout {
public:
    char type[20];
    int duration; 
    int intensity;
    int caloriesBurned;
    bool goalReached;
public:
    Workout() {

        caloriesBurned = 0;
        goalReached = false;
    }

    Workout(const char* typeInput, int duration, int intensity)
        : duration(duration), intensity(intensity), caloriesBurned(0), goalReached(false) {

        strncpy_s(type, typeInput, sizeof(type) - 1);
        type[sizeof(type) - 1] = '\0';  // Ensure null-termination
    }



    void logWorkout() {
        if (intensity > 5) {
            caloriesBurned = 10;
            goalReached = true;
        }
        else {
            caloriesBurned = 5;
            goalReached = false;
        }
        ofstream custome("Workout.bin", ios::binary | ios::app);
        custome.write((char*)this, sizeof(*this));
        cout << "Details successfully entered!" << endl;
        custome.close();



        cout << "Workout logged: " << type << ", Duration: " << duration << " mins, Intensity: " << intensity << "with calories burned: " << caloriesBurned << endl;
    }
    static void displayWorkouts() {
        Workout wk;
        ifstream infile("Workout.bin", ios::binary);
        if (!infile) {
            cerr << "Error opening file for reading!" << endl;
            return;
        }

        cout << "Stored Workouts:" << endl;
        while (infile.read((char*)&wk, sizeof(wk))) {
            cout << "Type: " << wk.type
                << ", Duration: " << wk.duration << " mins"
                << ", Intensity: " << wk.intensity
                << ", Calories burned: " << wk.caloriesBurned
                << (wk.goalReached ? ", Goal reached!" : ", Goal not reached.") << endl;
        }

        infile.close();
    }
};


