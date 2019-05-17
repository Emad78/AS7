#ifndef PEERSON_H
#define PEERSON_H

#include "refrence.h"
#include "film.h"
#include "notification.h"
#include "bad_request.h"
#include "not_found.h"
#include "permission_denied.h"

class Person
{
protected:
	Info info;
	int id;
	vector<Notification*> notifications;
	vector<Film*> bought_films;  // pointer or not
	int money;
public:
	Person(Input input, int _id);
	int get_money();
	string get_username();
	int get_id();
	bool get_is_publisher();
	void add_money(Input input);
	virtual Film* search_my_film(int _id){};
	virtual void print_followers() {};
	virtual void add_my_film(Film* new_film){};
	string get_password();
	void catch_notif(string content);
	virtual	void inform_followers(){};
	virtual	void add_follower(Person* follower){};
	virtual int catch_money() {};
	virtual void print_published(Input input) {};
	friend ostream& operator<<(ostream& out, Person* person);
//	~Person();
	
};

#endif