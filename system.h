#ifndef SYSTEM_H
#define SYSTEM_H

#include "refrence.h"
#include "film.h"
#include "person.h"
#include "publisher.h"

class System
{
private:
	vector<Film*> films;
	vector<Person*> users;
	int system_money;
	Command command;
public:
	System();
	~System();
};

#endif