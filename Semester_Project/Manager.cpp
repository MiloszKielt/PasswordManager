//
// Created by milos on 11/06/2022.
//

#include "Manager.h"
#include <cmath>
#include <string>
#include <algorithm>


Manager::Manager(const vector<string>& passwords) {
	for(const std::string& p : passwords) {
		cout << p << endl;
		passwordVec.insert(passwordVec.end(), Password(p));
	}
	initializeCategories();
	initializeManager();
}

void Manager::initializeCategories() {
	for(Password p : passwordVec) {
		if(!checkIfExistsCategory(p.getCategory()))
			categories.push_back(p.getCategory());
	}
}

void Manager::initializeManager() {
	char opt = 0;
	while(opt != '0') {
		std::cout << "Hello, please choose one of this options: \n"
					 "0. EXIT\n"
					 "1. List passwords\n"
					 "2. Search for password\n"
					 "3. Sort passwords\n"
					 "4. Add a password\n"
					 "5. Edit a password\n"
					 "6. Remove a password\n"
					 "7. Add category\n"
					 "8. Remove category\n";
		cin>>opt;
		switch (opt) {
			case '1':
				listPasswords(this->passwordVec);
				break;
			case '2':
				searchForPasswords();
				break;
			case '3':
				sortPasswords();
				break;
			case '4':
				addPassword();
				break;
			case '5':
				editPassword();
				break;
			case '6':
				removePassword();
				break;
			case '7':
				addCategory();
				break;
			case '8':
				removeCategory();
				break;
			case '0':
				break;
			default:
				std::cout << "Wrong option, choose again" << std::endl;
				break;
		}
	}
}



void Manager::addCategory() {
	cout << "Provide name of category" << endl;
	string newCategory;
	cin >> newCategory;

	this->categories.push_back(newCategory);
}

void Manager::removeCategory() {
	cout << "Which category do you want to remove? (provide number) " << endl;
	listCategories();
	int choice;
	cin >> choice;
	if(choice > 0 && choice < categories.size()) {

		for(int i = 1; i < passwordVec.size(); i++) {
			if(passwordVec.at(i).getCategory() == categories[choice])
				passwordVec.at(i).setMarkedForDelete();
		}

		passwordVec.erase(
				std::remove_if(passwordVec.begin(), passwordVec.end(),
							   [](const Password& p){return p.markedForDelete;}),
				passwordVec.end()
				);

		categories.erase(categories.begin() + (choice));
	}

}

void Manager::listCategories() {
	cout << "Currently available categories:\n";
	for(int i = 1; i < categories.size(); i++) {
		cout << i << ". " << categories.at(i) << endl;
	}
}

void Manager::listPasswords(vector<Password> listed) {
	for (int i = 0; i < listed.size(); i++)
		cout << i << ". " << listed.at(i) << "\n";
}

void Manager::addPassword() {

	string result;
	string temp;
	cout << "Provide description for new password\n -> ";
	getline(cin >> ws,temp);
	//cin >> temp;
	result += temp;

	bool choice;
	cout << "Do you want the password to be generated automatically? (0/1)\n -> ";
	cin >> choice;
	if (choice) {
		while (!checkIfPasswordGood(temp))
			temp = generateRandomPassword();
	} else {
		temp = inputAndCheckNewPassword();
	}
	result += ';' + temp;
	listCategories();
	cout << "Provide the name of category\n -> ";
	getline(cin >> ws,temp);
	if (!checkIfExistsCategory(temp)) {
		cout << "No such directory! Process Aborted\n";
		return;
	}

	result += ';' + temp;
	cout << "Do you want to add URL and Login to the password? (0/1)\n -> ";
	cin >> choice;
	if(choice) {
		cout << "provide login:\n -> ";
		getline(cin >> ws, temp);
		result += ';' + temp;
		cout << "provide url:\n -> ";
		getline(cin >> ws, temp);
		result += ';' + temp;
	}


	passwordVec.insert(passwordVec.end(), Password(result));
}

bool Manager::checkIfExistsCategory(const string & category) {
	if(std::any_of(categories.begin(), categories.end(), [category](const string& s){return s == category;}))
		return true;

	return false;
}

void Manager::sortPasswords() {
	for(int i = 1; i < passwordVec.size(); i++) {
		for(int j = i+1 ; j < passwordVec.size(); j++) {
			if(passwordVec[j].getCategory().compare(passwordVec[i].getCategory()) < 0) {
				Password temp = passwordVec[i];
				passwordVec[i] = passwordVec[j];
				passwordVec[j] = temp;
			} else if(passwordVec[j].getCategory() == passwordVec[i].getCategory()) {
				if(passwordVec[j] < passwordVec[i]) {
					Password temp = passwordVec[i];
					passwordVec[i] = passwordVec[j];
					passwordVec[j] = temp;
				}
			}
		}
	}
	listPasswords(passwordVec);
}

string Manager::generateRandomPassword() {
	string result;
	while(result.length() != 18) {
		int i = int(rand() % 4 + 1);
		if(i == 1)
			result.push_back(char(97 + rand()%25));
		if(i == 2)
			result.push_back(char(65 + rand()%25));
		if(i == 3)
			result.push_back(char(48 + rand()%10));
		if(i == 4)
			result.push_back(specialCharacters[rand()%12]);
	}

	return result;
}

bool Manager::checkIfPasswordGood(const string& password) {
	bool hasLowerCase = false;
	bool hasUpperCase = false;
	bool hasNumber = false;
	bool hasSpecialChar = false;
	for(char c : password) {
		if(!hasLowerCase) {
			if('a' <= c && c <= 'z')
				hasLowerCase = true;
		}
		if(!hasUpperCase) {
			if('A' <= c && c <= 'Z')
				hasUpperCase = true;
		}
		if(!hasNumber) {
			if('0' <= c && c <= '9')
				hasNumber = true;
		}
		if(!hasSpecialChar) {
			if(checkSpecialChar(c))
				hasSpecialChar = true;
		}
	}

	return (hasSpecialChar && hasNumber && hasUpperCase && hasLowerCase);
}

string Manager::inputAndCheckNewPassword() {
	string result;
	cout << "Please deliver your password\n -> ";
	getline(cin >> ws,result);
	if(!checkIfPasswordGood(result))
		cout << "UNSAFE PASSWORD: editing it would be recommended\n"
				"make sure your password contains at least: \n"
				" - 1 lowercase letter\n"
				" - 1 uppercase letter\n"
				" - 1 number\n"
				" - 1 special character\n";
	return result;
}

bool Manager::checkSpecialChar(const char& c) {
	for(char spec : specialCharacters) {
		if(c == spec)
			return true;
	}
	return false;
}

void Manager::searchForPasswords() {
	int choice;
	cout<< "What criteria do you want to search by?\n"
		   "1. Description\n"
		   "2. Category\n"
		   "Enter other key to return to menu\n";
	cin>> choice;
	switch (choice) {
		case 1:
			searchByDesc();
			break;
		case 2:
			searchByCategory();
			break;
		default:
			cout << "Returning to menu...";
			break;
	}

}

vector<string> Manager::getPasswords() {
	vector<string> res;
	for(Password p : passwordVec)
		res.push_back(p.getPasswordString());

	return res;
}

void Manager::searchByDesc() {
	string criteria;
	cout << "What is to be included in desc?\n";
	cin >> criteria;

	vector<Password> result;

	for(Password p : passwordVec) {
		if(p.getDesc().find(criteria) != std::string::npos)
			result.push_back(p);
	}

	listPasswords(result);
}

void Manager::searchByCategory() {
	int choice = 0;
	while(choice > categories.size() || choice < 1) {
		cout << "choose category to look for" << endl;
		for (int i = 0; i < categories.size(); i++)
			cout << i + 1 << ". " << categories[i] << '\n';
		cin >> choice;
	}
	vector<Password> result;

	for(Password p : passwordVec) {
		if(p.getCategory() == categories[choice-1])
			result.push_back(p);
	}

	listPasswords(result);
}

void Manager::removePassword() {
	if(!passwordVec.empty() || passwordVec.size() == 1) {
		cout << "Provide index of password to delete: (1 is first position, " << passwordVec.size() - 1
			 << " is last, -1 to go back)\n";
		int choice;
		cin >> choice;
		if (choice >= 0 || choice < passwordVec.size()) {
			if(choice == 0)
				cout << "CANNOT DELETE MASTER PASSWORD\n";
			else
				passwordVec.erase(passwordVec.begin() + choice);
		}
	} else {
		cout << "Cannot delete anything, password list is empty\n" << endl;
	}
}

void Manager::editPassword() {
	cout << "Which password do you want to edit? (1 is first position "<< passwordVec.size() - 1 <<" is last)\n -> ";
	int choice;
	cin>>choice;

	if(choice == 0) {
		cout << "CANNOT EDIT MASTER PASSWORD\n";
		return;
	}
	if(choice >= passwordVec.size())
		return;


	Password* editing = &passwordVec.at(choice);
	cout << *editing << endl;

	cout << "What do you want to edit?\n"
			"1. Description\n"
			"2. Password\n"
			"3. Category\n"
			"4. Login\n"
			"5. URL\n -> ";
	cin>>choice;
	string edit;
	switch(choice) {
		case 1:
			getline(cin >> ws, edit);
			editing->setDesc(edit);
			break;
		case 2:
			edit = inputAndCheckNewPassword();
			editing->setPassword(edit);
			break;
		case 3:
			getline(cin >> ws, edit);
			if(checkIfExistsCategory(edit))
				editing->setCategory(edit);
			else
				cout << "No such category!\n";
			break;
		case 4:
			getline(cin >> ws, edit);
			editing->setLogin(edit);
			break;
		case 5:
			getline(cin >> ws, edit);
			editing->setURL(edit);
			break;
		default:
			cout << "Wrong choice!\n";
			break;
	}
}


