#include "person.h"

Person::Person(Input input, int _id)
{
	info.username = input.info[USERNAME];
	info.password = input.info[PASSWORD];
	info.email = input.info[EMAIL];
	info.age = stoi(input.info[AGE]);
	info.is_publisher = false;
	id = _id; 
}