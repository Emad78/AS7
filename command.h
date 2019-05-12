#ifndef COMMAND_H
#define COMMAND_H

#include "refrence.h"

class Command
{
private:
	map<string,string> key_value;

public:
	command();
	~command();
	friend class Person;
	friend class System;
	friend class Film;
};

#endif