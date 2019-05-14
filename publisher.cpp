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

Film* Publisher::search_my_film(int _id)
{
	for(int i = 0; i < my_films.size(); i++)
		if(_id == my_films[i]->get_id())
			return my_films[i];
	return NULL;
}