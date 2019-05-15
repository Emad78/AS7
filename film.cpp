#include "film.h"

Film::Film(Input input)
{
	id = _id;
	year = stoi(input.info[YEAR]);
	length = stoi(input.info[LENGTH]);
	name = input.info[NAME];
	summary = input.info[SUMMARY];
	director = input.info[DIRECTOR];
	if(year == 0 || length == 0)
		throw Bad_request();
	rate.score.clear();
	rate.user_id.clear();	
	is_visible = true;
}

void Film::edit(Input input)
{
	if(stoi(input.info[YEAR]) == 0 ||
		stoi(input.info[LENGTH]) == 0)
		throw Bad_request();	
	if(input.info[YEAR] != "")
		year = stoi(input.info[YEAR]);
	if(input.info[LENGTH] != "")
		length = stoi(input.info[LENGTH]);
	if(input.info[NAME] != "")
		name = input.info[NAME];
	if(input.info[SUMMARY] != "")
		summary = input.info[SUMMARY];
	if(input.info[DIRECTOR] != "")
		director = input.info[DIRECTOR];
}

int Film::get_id()
{
	return id;
}

bool Film::ge_is_visible()
{
	return is_visible;
}
