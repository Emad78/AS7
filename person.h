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
	vector<Film*> bought_films;
	int money;
public:
	Person(Input input, int _id);
	int get_money();
	string get_username();
	int get_id();
	bool get_is_publisher();
	void update_money(int new_money);
	void add_bought_film(Film* bought_film);
	bool search_bought_film(int _id);
	virtual Film* search_my_film(int _id){};
	virtual void print_followers() {};
	virtual void add_my_film(Film* new_film){};
	string get_password();
	void catch_notif(string content);
	void read(bool notif_status, int limit);
	vector<Film*> get_bought_films();
	virtual vector<Film*> get_my_films(){};
	virtual	void inform_followers(){};
	virtual	void add_follower(Person* follower){};
	virtual int catch_money() {};
	friend ostream& operator<<(ostream& out, Person* person);
};

#endif