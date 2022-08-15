//
// Created by milos on 11/06/2022.
//

#ifndef SEMESTER_PROJECT_MANAGER_H
#define SEMESTER_PROJECT_MANAGER_H

#include <iostream>
#include <map>
#include <vector>
#include "Password.h"

class Manager {
private:
	// passwords currently used in the manager
	std::vector<Password> passwordVec;
	// available categories of the passwords
	std::vector<std::string> categories = {
			"MAIN", "Games", "Social Media", "Bank"
	};
	// array of special characters used for generation of passwords, and checking for password safety
	constexpr static const char specialCharacters[10] = {
			'!','@','#','$','%','^',
			'&','*', '(', ')'
	};
public:

	/**
	 * Function initializes passwordVec field and fills it with passwords from file
	 * @param passwords map containing lines from the password file
	 */
	explicit Manager(const vector<string>& passwords);
	/**
	 * Function that is used to get password state from the manager
	 * @return vector of passwords used in the manager
	 */
	vector<string> getPasswords();
	/**
	 * initializes Categories from the input passwords into Category vector
	 */
	void initializeCategories();
	/**
	 * starts the main node of manager execution
	 */
	void initializeManager();
	/**
	 * outputs all passwords inside the passed vector
	 * @param listed vector of passwords that we want to list out
	 */
	static void listPasswords( vector<Password> listed);
	/**
	 * searches for passwords in a way specified by the user
	 */
	void searchForPasswords();
	/**
	 * sub-functions of "searchForPasswords()" - searches for passwords with specific description
	 */
	void searchByDesc();
	/**
	 * sub-functions of "searchForPasswords()" - searches for passwords with specific category
	 */
	void searchByCategory();
	/**
	 * sorts and prints out the vector of passwords
	 */
	void sortPasswords();
	/**
	 * adds a new password to the vector, password details are specified by the user
	 */
	void addPassword();
	/**
	 * lets the user to edit a chosen password
	 */
	void editPassword();
	/**
	 * removes a specified password from the passwordVec vector
	 */
	void removePassword();
	/**
	 * adds a new category to the categories vector
	 */
	void addCategory();
	/**
	 * removes a category from the categories vector
	 */
	void removeCategory();
	/**
	 * prints out all categories inside category vector
	 */
	void listCategories();
	/**
	 * function for checking if category exists in categories vector
	 * @param category category that we want to check for
	 * @return true if category is inside categories vector, false otherwise
	 */
	bool checkIfExistsCategory(const string & category);
	/**
	 * generates random password for the user
	 * @return randomly generated password
	 */
	static string generateRandomPassword();
	/**
	 * lets user input the password on his own, and then informs him if the password is safe
	 * @return password created by the user
	 */
	static string inputAndCheckNewPassword();
	/**
	 * checks if given password is safe or not
	 * @param password password that is to be checked
	 * @return true if password is safe, false otherwise
	 */
	static bool checkIfPasswordGood(const string& password);
	/**
	 * checks if a character is a special character from specialCharacters array
	 * @param c character that is to be checked
	 * @return true if it is a special char from the array, false otherwise
	 */
	static bool checkSpecialChar(const char& c);

};


#endif //SEMESTER_PROJECT_MANAGER_H
