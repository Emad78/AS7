#include "publisher.h"

Publisher::Publisher(Input input, int _id)
: Person(input, _id)
{
	info.is_publisher = true;
	followers.clear();
}

void Publisher::add_my_film(Film* new_film)
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

void Publisher::print_followers()
{
	cout<<"List of Followers"<<endl;
	cout<<"#. User Id"<<" | "<<"User Username"<<" | "<<"User Email"<<endl;
	for(int i = 0; i < followers.size(); i++)
		cout<<to_string(i)<<". "<<followers[i]<<endl;
}