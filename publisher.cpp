#include "publisher.h"

Publisher::Publisher(Input input, int _id)
: Person(input, _id)
{
	second_money = 0;
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

int Publisher::catch_money()
{
	int catching = second_money;
	money += second_money;
	second_money = 0;
	return catching;
}

void Publisher::print_published(Input input)
{
	for(int i = 0; i < my_films.size(); i++)
		if( my_films[i]->is_same_film(input))
				cout<<to_string(i+1)<<my_films[i]<<endl;
}

void Publisher::inform_followers()
{
	string content = get_username() + "send new film";
	for(int i = 0; i < followers.size(); i++)
		followers[i]->catch_notif(content);
}

void Publisher::add_follower(Person* follower)
{
	string content = follower->get_username() + "follow you";  /////////notif
	catch_notif(content);
	followers.push_back(follower);
}






