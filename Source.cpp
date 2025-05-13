#include<fstream>
#include"User.h"
#include"RegularUser.h"
#include"Trainer.h"
#include<string>
#include"Admin.h"

int main() {
	int choice, signupchoice, loginchoice;
	string name;
	char l;
	User* p = NULL;

	cout << "\t\t\t\t\t" << "WELCOME TO FITCONNECT Application System!" << endl;
	cout << "\t\t\t\t\tHere is the menu of our Application:" << endl;
	cout << endl;
	cout << endl;
	do {
		cout << "\t\t\t\t\tPress 1 for Signup!" << endl;
		cout << "\t\t\t\t\tPress 2 for Login!" << endl;

		cin >> choice;
		if (choice == 1) {
			cout << "You have choosen the opton to SIGNUP:)" << endl;
			cout << "Press the any of following number to continue the registration! " << endl;
			cout << "1)Sign up as Regular User" << endl;
			cout << "2)Sign up as Admin" << endl;
			cout << "3)Sign up as Trainer" << endl;
			cin >> signupchoice;
			if (signupchoice == 1) {
				RegularUser c;
				c.registerRegularCustomer();
				c.login();
			}
			else if (signupchoice == 2) {
				Admin a;
				a.registerAdmin();
				a.login();
			}
			else if (signupchoice == 3) {
				Trainer t;
				t.registerTrainer();
				t.login();
			}

		}
		else if (choice == 2) {
			cout << "You have choosen option to login in the system: " << endl;
			cout << "Press 1 to login as Regular User: " << endl;
			cout << "Press 2 to login as Admin: " << endl;
			cout << "Press 3 to login as Trainer:" << endl;
			cin >> loginchoice;
			if (loginchoice == 1) {
				p = new RegularUser;
				p->login();

			}
			else if (loginchoice == 2) {
				p = new Admin;
				p->login();
			}
			else if (loginchoice == 3) {
				p = new Trainer;
				p->login();
			}


		}

		cout << "Do you want to perform any other operation?" << endl;
		cin >> l;
	} while (l != 'N');


}