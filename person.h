#ifndef PEERSON_H
#define PEERSON_H

#include "refrence.h"
#include "film.h"

class Person
{
private:
	//struct//
	string username, email, password;
	int age;
	bool is_publisher;
	vector<Film*> bought_films;  // pointer or not

public:
	person();
	~person();
	
};

#endif