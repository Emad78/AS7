#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "refrence.h"
#include "person.h"

class Publisher : public Person
{
private:
	vector<Person*> followers;
	vector<Film*> my_films;
public:
	Publisher(Input input, int _id);
	void add_my_film(Film* new_film);
	void search_my_film(int _id);
	~Publisher();
	
};

#endif