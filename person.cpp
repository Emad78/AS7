#include "person.h"

Person::Person(Input input, int _id)
{
	if(input.info[USERNAME] == "" || input.info[PASSWORD] == ""
		|| input.info[EMAIL] == "" || input.info[AGE] == "")
		throw Bad_request();
	info.username = input.info[USERNAME];
	info.password = input.info[PASSWORD];
	info.email = input.info[EMAIL];
	info.age = stoi(input.info[AGE]);
	info.is_publisher = false;
	id = _id; 
	money = 0;
}

string Person::get_username()
{
	return info.username;
}

string Person::get_password()
{
	return info.password;
}

bool Person::get_is_publisher()
{
	return info.is_publisher;
}
ostream& operator<<(ostream& out, Person* person)
{
	out<<person->id<<" | ";
	out<<person->info.username<<" | ";
	out<<person->info.email;
	return out;
}

void Person::catch_notif(string content)
{
	notifications.push_back(new Notification(content));   /// what is notification
}

void Person::update_money(int new_money)
{
	money += new_money;
}

int Person::get_id()
{
	return id;
}

int Person::get_money()
{
	return money;
}

void Person::add_bought_film(Film* bought_film)
{
	bought_films.push_back(bought_film);
}

vector<Film*> Person::get_bought_films()
{
	return bought_films;
}

