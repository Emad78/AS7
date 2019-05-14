#ifndef SYSTEM_H
#define SYSTEM_H

#include "refrence.h"
#include "film.h"
#include "person.h"
#include "publisher.h"
#include "bad_request.h"
#include "not_found.h"
#include "‫‪permission‬‬_denied‬.h‬"

class System
{
private:
	vector<Film*> films;
	vector<Person*> users;
	int system_money;
	Command* command;
	Person* now_user;
	Input = input;
public:
	System();
	void run();
	void process();
	void metod_detect();
	void put_metod();
	void post_metod();
	void get_metod();
	void delete_metod();
	void signup();
	~System();
};

#endif