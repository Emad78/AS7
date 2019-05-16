#ifndef PEERSON_H
#define PEERSON_H

#include "refrence.h"
#include "film.h"
#include "bad_request.h"
#include "not_found.h"
#include "permission_denied.h"

class Person
{
protected:
	Info info;
	int id;
	vector<Film*> bought_films;  // pointer or not
	int money;
public:
	Person(Input input, int _id);
	string get_username();
	bool get_is_publisher();
	Film* search_my_film(int _id){};
	void print_followers() {};
	void add_my_film(Film* new_film){};
	string get_password();
	friend ostream& operator<<(ostream& out, Person* person);
//	~Person();
	
};

#endif