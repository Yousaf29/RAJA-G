#pragma once

#include "User.h"
#include <string>
#include<fstream>
#include"Validation.h"
using namespace std;

bool checkExistingTrainer(char* p);



class Trainer : public User {
public:

	char qualifications[30];
	char successStories[40];
	double pricing;

	void login() override {
		system("CLS");
		bool loginsuccessful = 0;
		string name;
		string password;
		cout << "Enter the username: " << endl;
		cin >> name;
		cout << "Enter the password: " << endl;
		cin >> password;
		Trainer t;
		ifstream custom("Trainer.bin", ios::binary);
		while (!custom.eof()) {
			custom.read((char*)&t, sizeof(t));
			if (t.getName() == name && t.getpassword() == password) {
				cout << "Login successfully!" << endl;
				loginsuccessful = true;
				break;
			}
			else {
				if (t.getpassword() != password) {
					cout << "Incorrect password, enter again!" << endl;
				}
				loginsuccessful = false;
				cout << "Login Insuccessfully!" << endl;

			}


		}
		if (loginsuccessful == 1) {
			cout << "Trainer logged in successfully" << endl;
			t.loginAsTrainer();
			
		}


	}
	Trainer() {

	}
	~Trainer() {

	}
	Trainer(string name, string password, string contact,
		string qualifications, string successStories, double pricing) {

	}
	void updateProfile()override {

	}
	char* getName() {
		return name;
	}
	char* getpassword() {
		return password;
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


	void loginAsTrainer() {
		int choice;
		bool running = true;
		bool exitmenu = false;
		while (!exitmenu) {
			system("CLS");
			cout << "Logged in as Trainer - " << getName() << endl;
			cout << "1. Manage Sessions\n";
			cout << "2. Track Payments\n";
			cout << "3. Handle Requests\n";
			cout << "4. Update Profile\n";
			cout << "5. Logout\n";
			cout << "Enter your choice: ";
			cin >> choice;


			switch (choice) {
			case 1:
				this->manageSessions();
				break;
			case 2:
				this->trackPayments();
				break;
			case 3:
				this->handleRequests();
				break;
			case 4:
				updateProfile();
				break;
			case 5:
				exitmenu = true;
				break;
			default:
				cout << "Invalid choice, please try again.\n";
				break;
			}
			if (!exitmenu) {
				cout << "Press any key to continue..." << endl;
				cin.ignore();
				cin.get();  // Pause the console to allow the admin to read the information
			}
		}

	}

	void manageSessions() {
		cout << "Managing sessions for trainer: " << name << endl;
		// Simulate session management
		cout << "Current sessions: \n";
		cout << "1. Yoga Session at 10 AM\n";
		cout << "2. Pilates Session at 2 PM\n";
		// Example of modifying a session
		cout << "Rescheduling Pilates Session to 3 PM...\n";
		cout << "Updated sessions:\n";
		cout << "1. Yoga Session at 10 AM\n";
		cout << "2. Pilates Session at 3 PM\n";
	}

	void trackPayments() {
		cout << "Tracking payments for trainer: " << name << endl;
		// Simulate tracking of payments
		cout << "Payments received:\n";
		cout << "$50 for Yoga Session\n";
		cout << "$75 for Pilates Session\n";
		// Example of a missing payment
		cout << "Outstanding payment: $75 for Personal Training Session\n";
	}

	void handleRequests() {
		cout << "Handling requests for trainer: " << name << endl;
		// Simulate handling of user requests
		cout << "Received request for Personal Training availability.\n";
		cout << "Responding to request: 'Available slots - Wednesday 3 PM, Friday 5 PM'\n";
		cout << "Booking confirmed for Wednesday 3 PM\n";
	}


	void registerTrainer() {
		char name[20];
		char password[10];
		int id;
		string qualifications, successStories;
		double yogaPricing, pilatesPricing, personalTrainingPricing;
		bool truePassword;
		bool existingUser;

		cout << "Enter the username: ";
		cin >> name;
		cout << "Enter the password: ";
		cin >> password;
		cout << "Enter your qualifications: ";
		cin.ignore();
		getline(cin, qualifications);
		cout << "Enter your success stories: ";
		getline(cin, successStories);
		cout << "Enter the pricing for Yoga session: ";
		cin >> yogaPricing;
		cout << "Enter the pricing for Pilates session: ";
		cin >> pilatesPricing;
		cout << "Enter the pricing for Personal Training session: ";
		cin >> personalTrainingPricing;

		Validation v;
		truePassword = v.Password(password);
		if (!truePassword) {
			while (!truePassword) {
				cin.ignore();
				cout << "Enter the password again: ";
				cin >> password;
				truePassword = v.Password(password);
			}
		}
		if (truePassword) {
			cout << "Password entered successfully! " << endl;
		}

		existingUser = checkExistingTrainer(name);
		if (existingUser) {
			cout << "Username already exists, kindly login!" << endl;
			login();
		}
		else {
			Trainer t;
			t.setUserName(name);
			t.setPassword(password);
			// Assuming email is also provided somewhere in the flow
			ofstream custom("Trainer.bin", ios::binary | ios::app);
			custom.write((char*)&t, sizeof(t));
			cout << "Details successfully entered!" << endl;
			custom.close();
		}



	}

};
bool checkExistingTrainer(char* name) {
	Trainer temp;
	bool exists = false;  // Default is that the trainer does not exist

	ifstream myFile("Trainer.bin", ios::binary);
	if (!myFile) {
		cout << "Error opening file. Please check if the file exists and is not in use!" << endl;
		return false;
	}

	while (myFile.read((char*)&temp, sizeof(temp))) {
		if (!strcmp(temp.getName(), name)) {
			exists = true;
			break;  // If found, no need to continue the loop
		}
	}
	myFile.close();

	return exists;
}

