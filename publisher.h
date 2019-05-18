#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "refrence.h"
#include "person.h"

class Publisher : public Person
{
private:
	vector<Person*> followers;
	vector<Film*> my_films;
	int second_money;
public:
	Publisher(Input input, int _id);
	Film* search_my_film(int _id);
	void print_followers();
	int catch_money();
	void inform_followers();
	virtual vector<Film*> get_my_films();
	void add_follower(Person* follower);
	void add_my_film(Film* new_film);
	~Publisher();
	
};

#endif