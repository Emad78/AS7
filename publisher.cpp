#include "publisher.h"

Publisher::publisher(Input input, int _id)
: Person(input, _id)
{
	is_publisher = true;
	followers.clear();
}

Publisher::add_my_film(Film* new_film)
{
	my_films.push_back(new_film);
}