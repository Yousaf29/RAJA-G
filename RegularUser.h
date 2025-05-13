#pragma once
#include <chrono>
#include <iomanip>
#include <sstream>

#include "User.h"
#include "Workout.h"
#include "NutrititonLog.h"
#include "SocialInteraction.h"
#include "ProgressAnalysis.h"
#include "Validation.h"
#include"Location.h"

using namespace std;

bool checkexisitingCustomer(char* m);
struct Challenge {
	char title[100];
	char description[256];
};

class RegularUser : public User {
private:
	static const int MAX_WORKOUTS = 10;
	static const int MAX_MEALS = 10;
	
	Workout workouts[MAX_WORKOUTS]; // Aggregation
	int workoutCount;
	NutritionLog nutritionLogs[MAX_MEALS]; // Aggregation
	int mealCount;
	Challenge challenges;
	//int challengeCount;
	
	SocialInteraction socialInteraction; // Composition
	ProgressAnalysis p; // Composition
	char facilities[30];
public:
	RegularUser() {
		workoutCount = 0;
		mealCount = 0;

	}
	~RegularUser() {

	}
	void setChallenge() {
		

		cout << "Enter challenge title: ";
		cin.ignore(); // Clear the input buffer
		cin.getline(challenges.title, 100);

		cout << "Enter challenge description: ";
		cin.getline(challenges.description, 256);

		
		cout << "Challenge set successfully!" << endl;
	}

	
	void viewChallenges() {
		

		cout << "Listing all challenges:" << endl;
		cout << challenges.title << endl;
		cout << challenges.description << endl;
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
	void setID(int id) {
		ID = id;
	}
	char* getName() {
		return name;
	}
	char* getpassword() {
		return password;
	}

	void login() override {
		system("CLS");
		bool loginSuccessful = false;
		string name, password;

		cout << "Enter the username: " << endl;
		cin >> name;
		cout << "Enter the password: " << endl;
		cin >> password;

		ifstream custom("RegularUser.bin", ios::binary);
		if (!custom) {
			cerr << "Failed to open file for reading. Please check that the file exists and is readable." << endl;
			return;  // Exit function if file can't be opened
		}

		RegularUser t;
		while (custom.read((char*)&t, sizeof(t))) {
			if (t.getName() == name && t.getpassword() == password) {
				cout << "Login successfully!" << endl;
				loginSuccessful = true;
				break;
			}
			else {
				cout << "Incorrect password. Please try again." << endl;
				
				break;
			}
		}

		if (!loginSuccessful) {
			cout << "Login unsuccessfully! Please check your username and password." << endl;
		}
		else {
			cout << "Regular User logged in successfully." << endl;
			t.loginAsRegularUser();
			return;
		}

		custom.close();  



	}
	void loginAsRegularUser() {
		int choice;
		cout << "Welcome, " << name << "!" << endl;
		cout << "1. Log Workout" << endl;
		cout << "2. View Workout History" << endl;
		cout << "3. Log Meal" << endl;
		cout << "4. View Nutrition History" << endl;
		cout << "5. Post Update" << endl;
		cout << "6. View Social Feed" << endl;
		cout << "7. View Progress Reports" << endl;
		cout << "8. Update Profile" << endl;
		cout << "9. Change Password" << endl;
		cout << "10 Participate in challenge" << endl;
		cout << "11 View Challenges" << endl;
		cout << "12. Discover Nearby Fitness Facilities" << endl;
		cout << "13. Explore Running Routes" << endl; 
		cout << "14. Explore Cycling Routes" << endl; 
		cout << "15. LogOut" << endl;


		cin >> choice;
		switch (choice) {
		case 1:
			this->logWorkout();  // Function to log workout details
			break;
		case 2:
			this->viewWorkoutHistory();  // Display past workout data
			break;
		case 3:
			this->logMeal();  // Function to log meal details
			break;
		case 4:
			this->viewMealHistory();  // Show past nutrition logs
			break;
		case 5:
			this->postUpdate();  // Share an update to social feed
			break;
		case 6:
			this->viewSocialFeed();  // Display posts from other users
			break;
		case 7:
			this->viewProgressReport();  // Show progress reports and graphs
			break;
		case 8:
			updateProfile();  
			break;
		case 9:
			changePassword(); 
			break;

		case 10:
			this->setChallenge();
			break;
		case 11:
			this->viewChallenges();
			break;
		case 12:
			this->discoverFitnessFacilities();
			break;
		case 13:
			this->exploreRunningRoutes();
			break;
		case 14:
			this->exploreCyclingRoutes();
			break;
		case 15:
			return;
		default:
			cout << "Invalid option. Please try again." << endl;
			break;
		}
		loginAsRegularUser();



	}



	void registerRegularCustomer() {
		char name[20];
		//char CNIC[14];
		char password[10];
		char gender;
		int id;
		char email[15];
		bool truepassword;
		bool existingUser;
		cout << "Enter the username: ";
		cin >> name;

		cout << "Enter the password: ";
		cin >> password;
		cout << "Enter the id: ";
		cin >> id;
		ID = id;

		Validation v;
		truepassword = v.Password(password);
		if (truepassword == 0) {
			while (!truepassword) {
				cin.ignore();
				cout << "Enter the password again: ";
				cin >> password;
				truepassword = v.Password(password);

			}
		}
		if (truepassword == 1) {
			cout << "Password entered successfully! " << endl;
		}




		existingUser = checkexisitingCustomer(name);
		if (existingUser == 1) {
			cout << "UserName already exist, kindly login!" << endl;
			login();
		}
		else {
			RegularUser c;
			c.setUserName(name);
			c.setPassword(password);


			ofstream custome("RegularUser.bin", ios::binary | ios::app);
			custome.write((char*)&c, sizeof(c));
			cout << "Details successfully entered!" << endl;
			custome.close();
		}



	}
	void viewProgressReport() {
		if (workoutCount == 0 && mealCount == 0) {
			cout << "No workouts or meals logged yet." << endl;
			return;
		}

		// Display workout summary
		if (workoutCount > 0) {
			cout << "Workout Summary:" << endl;
			for (int i = 0; i < workoutCount; ++i) {
				cout << "Workout " << i + 1 << ": Type = " << workouts[i].type
					<< ", Duration = " << workouts[i].duration
					<< " minutes, Intensity = " << workouts[i].intensity << "/10" << endl;
			}
		}

		// Display meal summary
		if (mealCount > 0) {
			cout << "Meal Summary:" << endl;
			for (int i = 0; i < mealCount; ++i) {
				cout << "Meal " << i + 1 << ": Type = " << nutritionLogs[i].mealType
					<< ", Calories = " << nutritionLogs[i].calories
					<< ", Goal = " << nutritionLogs[i].goal << endl;
			}
		}

		// Optionally, analyze and display some statistics or summaries
		cout << "Total Workouts Logged: " << workoutCount << endl;
		cout << "Total Meals Logged: " << mealCount << endl;
	}


	void logWorkout() {
		cout << this->workoutCount << endl;
		if (workoutCount >= MAX_WORKOUTS) {
			cout << "Maximum number of workouts reached. Cannot log more workouts." << endl;
			return;
		}
		char type[20];
		int duration;
		int intesity;


		cout << "Enter workout type, duration (in minutes), and intensity (scale of 1 to 10): ";
		cin >> type >> duration >> intesity;

		workouts[workoutCount] = Workout(type, duration, intesity);
		workouts[workoutCount].logWorkout();
		workoutCount++;
		cout << "Workout logged successfully!" << endl;
	}

	void logMeal() {
		if (mealCount >= MAX_MEALS) {
			cout << "Maximum number of meals reached. Cannot log more meals." << endl;
			return;
		}
		string goal;
		int a = 0;
		cout << "What's your goal?" << endl;
		cin >> goal;
		if (goal == "weightloss") {
			a = 1;
		}
		else if (goal == "muscles") {
			a = 2;
		}
		else {
			a = 3;
		}
		char mealType[20];
		int calories;
		cout << "Enter meal type and calories: ";
		cin >> mealType >> calories;

		nutritionLogs[mealCount] = NutritionLog(mealType, calories, a);
		nutritionLogs[mealCount].logMeal();
		mealCount++;
		cout << "Meal logged successfully!" << endl;
	}

	void postUpdate() {
		char content[256];
		cout << "What's on your mind today? ";
		cin.ignore(); // Clearing buffer before getline
		cin >> content;
		socialInteraction.createPost(content);
	}

	void updateProfile() {
		char newName[20];

		cout << "Enter new name and email: ";
		cin >> newName;
		this->setUserName(newName);  // Assumes setter exists in User class
		// Assumes setter exists in User class
		cout << "Profile updated successfully!" << endl;
	}

	void changePassword() {
		char newPassword[30];
		cout << "Enter new password: ";
		cin >> newPassword;
		setPassword(newPassword);  // Assumes setter exists in User class
		cout << "Password changed successfully!" << endl;
	}
	void viewWorkoutHistory() {
		if (workoutCount == 0) {
			cout << "No workouts logged." << endl;
			return;
		}
		cout << "Workout History:" << endl;
		for (int i = 0; i < workoutCount; ++i) {
			workouts[i].displayWorkouts();
		}
	}

	void viewMealHistory() {
		if (mealCount == 0) {
			cout << "No meals logged." << endl;
			return;
		}
		cout << "Meal History:" << endl;
		for (int i = 0; i < mealCount; ++i) {
			nutritionLogs[i].displayMeals();
		}
	}
	void viewSocialFeed() {
		socialInteraction.displayPosts(); // Use the displayPosts method from SocialInteraction
	}
	void discoverFitnessFacilities() {
		Location l;
		ifstream inFile("Location.bin", ios::binary);
		if (!inFile) {
			cout << "Failed to open the file." << endl;
			return;
		}

		cout << "Displaying All Facilitis:" << endl;
		while (!inFile.eof()) {
			inFile.read((char*)&l, sizeof(l));
		}
		inFile.close();
		l.displayFitnessFacilities();


	}
	void exploreRunningRoutes() {
		
		Location l;
		ifstream inFile("Location.bin", ios::binary);
		if (!inFile) {
			cout << "Failed to open the file." << endl;
			return;
		}

		cout << "Displaying All Running routes:" << endl;
		while (!inFile.eof()) {
			inFile.read((char*)&l, sizeof(l));
		}
		inFile.close();
		l.displayRunningRoutes();
		
	}

	
	void exploreCyclingRoutes() {
		Location l;
		ifstream inFile("Location.bin", ios::binary);
		if (!inFile) {
			cout << "Failed to open the file." << endl;
			return;
		}

		cout << "Displaying All Cycling routes:" << endl;
		while (!inFile.eof()) {
			inFile.read((char*)&l, sizeof(l));
		}
		inFile.close();
		l.displayCyclingRoutes();

		
	}

	



};

bool checkexisitingCustomer(char* m) {
	RegularUser temp1;
	bool b;

	ifstream myFile("RegularUser.bin", ios::binary | ios::app);
	while (!myFile.eof())
	{
		myFile.read((char*)&temp1, sizeof(temp1));
		if (!strcmp(temp1.getName(), m)) {
			b = true;
		}
		else {
			b = false;
			break;
		}
	}
	myFile.close();

	if (b == 1) {
		return 1;
	}
	else {
		return 0;
	}






};
