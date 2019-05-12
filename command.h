#ifndef COMMAND_H
#define COMMAND_H

#include "refrence.h"

#define USERNAME "username"
#define PASSWORD "password"
#define AGE "age"
#define EMAIL "email"
#define PUBLISHER "publisher"

#define NAME "name"
#define YEAR "year"
#define LENGTH "length"
#define PRICE "price"
#define SUMMARY "summary"
#define DIRECTOR "director"

#define MAX_YEAR "max_year"
#define MIN_YEAR "min_year"
#define MIN_RATE "min_rate"


class Command
{
private:
	map<string,string> info;
	int method;
	int request;
public:
	command();
	void set();
	void input(string line);
	string seprate_word(string &sentence,char delimiter);
	friend class Person;
	friend class System;
	friend class Film;
};

#endif