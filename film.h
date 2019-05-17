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
	int id, year, length, price, publisher_id;
	string name, summary, director;
	Rate rate;
	vector<Comment*> comments;
	bool is_visible;
public:
	Film(Input input, int _id, int _publisher_id);
	void edit(Input input);
	int get_id();
	bool get_is_visible();
	void _delete();
	void delete_comment(Input input);
	double _rate();
	bool is_same_film(Input input);
	int reply(Input input);
	friend ostream& operator<<(ostream& out, Film* film);
//	~Film();
	
};

#endif