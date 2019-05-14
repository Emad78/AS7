#ifndef PEERSON_H
#define PEERSON_H

#include "refrence.h"
#include "film.h"
#include "bad_request.h"
#include "not_found.h"
#include "‫‪permission‬‬_denied‬.h‬"

class Person
{
private:
	Info info;
	int id;
	vector<Film*> bought_films;  // pointer or not
	int money;
public:
	person(Input input, int _id);
	string get_username();
	string get_password();
	~person();
	
};

#endif