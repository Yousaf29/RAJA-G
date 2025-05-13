#pragma once


#include <iostream>
#include <string>

class NutritionLog {
public:
    char mealType[30];
    int calories;
    bool weightLoss;
    bool muscles;
    bool health;
    int goal;

public:
    NutritionLog() {

    }
    NutritionLog(const char* typeInput, int calories, int goal)
        : calories(calories), weightLoss(false), muscles(false), health(false), goal(goal) {

        strncpy_s(mealType, typeInput, sizeof(mealType) - 1);
        mealType[sizeof(mealType) - 1] = '\0';  // Ensure null-termination
    }

    void logMeal() {
        if (goal == 1) {
            weightLoss = true;
        }
        else if (goal == 2) {
            muscles = true;
        }
        else {
            health = true;
        }


        ofstream custome("MealLog.bin", ios::binary | ios::app);
        custome.write((char*)this, sizeof(*this));
        cout << "Details successfully entered!" << endl;
        custome.close();
        cout << "Meal logged: " << mealType << ", Calories: " << calories << endl;
    }


    void displayMeals() {
        NutritionLog meal;
        ifstream infile("MealLog.bin", ios::binary);
        if (!infile) {
            cerr << "Error opening file for reading!" << endl;
            return;
        }

        cout << "Stored Meals:" << endl;
        while (infile.read((char*)&meal, sizeof(meal))) {
            cout << "Meal Type: " << meal.mealType
                << ", Calories: " << meal.calories
                << ", weightLoss" << meal.mealType
                << ", muscles" << meal.muscles
                << ", health" << meal.health
                << ", goal" << meal.goal << endl;
        }

        infile.close();
    }
};


