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
public:
	System();
	void run();
	~System();
};

#endif