#ifndef COMMAND_H
#define COMMAND_H

#include "refrence.h"
#include "bad_request.h"
#include "not_found.h"
#include "permission_denied.h"

class Command
{
private:
	Input input;
	string line;
public:
	Command(string _line);
	void set();
	Input get_input();
	string seprate_word(string &sentence,char delimiter);
	friend class Person;
	friend class System;
	friend class Film;
};

#endif