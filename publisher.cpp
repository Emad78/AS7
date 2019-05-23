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
		cout<<to_string(i + 1)<<". "<<followers[i]<<endl;
}

int Publisher::catch_money()
{
	int catching = second_money;
	money += second_money;
	second_money = 0;
	cout<<"catching = "<<catching;
	return catching;
}

void Publisher::inform_followers()
{
	string notif = "Publisher ";
	notif += info.username;
	notif += " with id ";
	notif += to_string(id);
	notif += " register new film.";
	for(int i = 0; i < followers.size(); i++)
		followers[i]->catch_notif(notif);
}

void Publisher::add_follower(Person* follower)
{
	string notif = "User ";
	notif += follower->get_username();
	notif += "with id ";
	notif += to_string(follower->get_id());
	notif += " follow you.";
	catch_notif(notif);
	followers.push_back(follower);
}

vector<Film*> Publisher::get_my_films()
{
	return my_films;
}

void Publisher::update_second(int new_money)
{
	second_money += new_money / 100;
}