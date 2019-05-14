#ifndef PEERSON_H
#define PEERSON_H

#include "refrence.h"
#include "film.h"

class Person
{
private:
	Info info;
	int id;
	vector<Film*> bought_films;  // pointer or not
	int money;
public:
	person(Input input, int _id);
	~person();
	
};

#endif