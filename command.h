#ifndef COMMAND_H
#define COMMAND_H

#include "refrence.h"

class Command
{
private:
	Input input;
public:
	command();
	void set();
	Input get_input(string line);
	string seprate_word(string &sentence,char delimiter);
	friend class Person;
	friend class System;
	friend class Film;
};

#endif