#ifndef FILM_H
#define FILM_H

#include "refrence.h"
#include "coment.h"
#include "bad_request.h"
#include "not_found.h"
#include "permission_denied.h"

class Film
{
private:
	int id, year, length, price;
	string name, summary, director;
	Rate rate;
	vector<Coment*> coments;
	bool is_visible;
public:
	Film(Input input, int _id);
	void edit(Input input);
	int get_id();
	bool get_is_visible();
	void _delete();
	double _rate();
	bool is_same_film(Input input);
	friend ostream& operator<<(ostream& out, Film* film);
//	~Film();
	
};

#endif