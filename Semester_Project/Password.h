//
// Created by milos on 27/05/2022.
//

#ifndef SEMESTER_PROJECT_PASSWORD_H
#define SEMESTER_PROJECT_PASSWORD_H

#include <iostream>

using namespace std;

class Password {
private:
	string desc;
	string password;
	string category;
	string url;
	string login;
public:
	bool markedForDelete = false;
	/**
	 * Creates a new object of class password
	 * @param line string from which the password is extracted
	 */
	explicit Password(const string& line);
	/**
	 * Overridden funtion to print out password objects
	 * @param os output stream that prints the content
	 * @param p password that is to be printed
	 * @return output stream with information about the password
	 */
	friend ostream& operator<<(ostream& os, const Password& p);
	/**
	 * function used to get the whole string with all non-empty fields of password
	 * @return string with all non-empty fields of password
	 */
	string getPasswordString();
	/**
	 * getter for description of password
	 * @return description of password the method was invoked on
	 */
	string getDesc();
	/**
	 * getter for category of password
	 * @return category of password the method was invoked on
	 */
	string getCategory();
	/**
	 * overridden operator for comparing 2 passwords
	 * @param p password to be compared with password the method was invoked on
	 * @return true if @param p is lesser, false otherwise
	 */
	bool operator<(const Password& p);
	/**
	 * overridden operator for comparing 2 passwords
	 * @param p password to be compared with password the method was invoked on
	 * @return true if @param p is greater, false otherwise
	 */
	bool operator>(const Password& p);
	/**
	 * overridden operator for comparing 2 passwords
	 * @param p password to be compared with password the method was invoked on
	 * @return true if @param p is equal to password invoking the method, false otherwise
	 */
	bool operator==(const Password& p);
	/**
	 * sets the password to be marked for delete
	 */
	void setMarkedForDelete();

	/**
	 * setters for each of password string fields
	 * @param edit edited variable that will be set as new variable for that position
	 */
	void setDesc(string edit);
	void setPassword(string edit);
	void setCategory(string edit);
	void setLogin(string edit);
	void setURL(string edit);



};


#endif //SEMESTER_PROJECT_PASSWORD_H
