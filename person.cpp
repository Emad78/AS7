#include "person.h"

Person::Person(Input input, int _id)
{
	if(input.info[USERNAME] == "" || input.info[PASSWORD] == ""
		|| input.info[EMAIL] == "" || input.info[AGE])
		throw Bad_request();
	info.username = input.info[USERNAME];
	info.password = input.info[PASSWORD];
	info.email = input.info[EMAIL];
	info.age = stoi(input.info[AGE]);
	info.is_publisher = false;
	id = _id; 
}

void Person::get_username()
{
	return username;
}