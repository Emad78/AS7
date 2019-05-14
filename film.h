#ifndef FILM_H
#define FILM_H

#include "refrence.h"
#include "bad_request.h"
#include "not_found.h"
#include "‫‪permission‬‬_denied‬.h‬"

class Film
{
private:
	int id, year, length;
	string name, summary, director;
	Rate rate;
public:
	Film(Input input, int _id);
	~Film();
	
};

#endif