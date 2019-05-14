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