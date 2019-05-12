#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "refrence.h"
#include "person.h"

class Publisher : public Person
{
private:
	vector<Person*> followers;
	
public:
	Publisher();
	~Publisher();
	
};

#endif