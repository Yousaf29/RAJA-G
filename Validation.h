#pragma once

#include<iostream>
using namespace std;
class Validation {
public:

	bool Password(char p[]) {
		int count = 0;
		int i = 0;
		while (p[i] != '\0') {
			count++;
			i++;
		}


		bool acceptPassLength = true;
		bool acceptPassU = true;
		bool acceptPassL = true;
		bool acceptPassN = true;
		bool acceptPassS = true;



		if (count != 9) {
			acceptPassLength = false;
			cout << "Error: password less than 9 characters!" << endl;

		}
		else
			acceptPassLength = true;
		if (count == 9) {
			for (int i = 0; i < 9; i++)
			{

				if (p[i] >= 65 && p[i] <= 90)
				{
					acceptPassU = true;
					break;
				}
				else
				{
					acceptPassU = false;
				}

			}

			for (int i = 0; i < 9; i++)
			{

				if (p[i] >= 97 && p[i] <= 122)
				{
					acceptPassL = true;
					break;
				}
				else
				{
					acceptPassL = false;
				}

			}

			for (int i = 0; i < 9; i++)
			{

				if (p[i] >= 48 && p[i] <= 57)
				{
					acceptPassN = true;
					break;
				}
				else
				{
					acceptPassN = false;
				}

			}

			for (int i = 0; i < 9; i++)
			{

				if (p[i] >= 33 && p[i] <= 47 || p[i] >= 58 && p[i] <= 64 || p[i] >= 91 && p[i] <= 96 || p[i] >= 123 && p[i] <= 126)
				{
					acceptPassS = true;
					break;
				}
				else
				{
					acceptPassS = false;
				}

			}
			if (!acceptPassU)
				cout << "Error: password does not have an uppercase letter!" << endl;

			if (!acceptPassL)
				cout << "Error: password does not have a lowercase letter!" << endl;

			if (!acceptPassN)
				cout << "Error: password does not have a numerical digit!" << endl;

			if (!acceptPassS)
				cout << "Error: password does not have a special character!" << endl;



		}

		if (acceptPassLength == true && acceptPassL == true && acceptPassN == true && acceptPassS == true && acceptPassU == true) {
			return 1;
		}
		else {
			return false;
		}



	}


};
