#ifndef FILM_H
#define FILM_H

#include "refrence.h"

class Film
{
private:
	int id, year, length;
	string name, summary, director;
	int rate, rate_number;
public:
	Film();
	~Film();
	
};

#endif