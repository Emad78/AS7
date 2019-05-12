#include "command.h"

Command::command()
{
	set();
}

void Command::set()
{
	set_person_info();
	set_film_info();
	set_search_info();	
}

viod Command::set_search_info()
{
	search_info.insert({NAME, ""});
	search_info.insert({PRICE, ""});
	search_info.insert({DIRECTOR, ""});
	search_info.insert({MAX_YEAR, ""});
	search_info.insert({MIN_YEAR, ""});
	search_info.insert({MIN_RATE, ""});
}

void Command::set_film_info()
{
	film_info.insert({NAME, ""});
	film_info.insert({YEAR, ""});
	film_info.insert({LENGTH, ""});
	film_info.insert({PRICE, ""});
	film_info.insert({SUMMARY, ""});
	film_info.insert({DIRECTOR, ""});	
}

void Command::set_person_info()
{
	person_info.insert({USERNAME, ""});
	person_info.insert({PASSWORD, ""});
	person_info.insert({AGE, ""});
	person_info.insert({EMAIL, ""});
	person_info.insert({PUBLISHER, ""});
}