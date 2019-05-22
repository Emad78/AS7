#include "command.h"

Command::Command(string _line)
: line(_line)
{}

void Command::check_email(string email) {
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        if(!regex_match(email, pattern))
        	throw Bad_request();
}

void Command::check_format()
{
	if(input.info[EMAIL] != "")
		check_email(input.info[EMAIL]);
		check_is_number(input.info[PRICE]);
		check_is_number(input.info[MAX_YEAR]);
		check_is_number(input.info[MIN_YEAR]);
		check_is_number(input.info[MIN_RATE]);
		check_is_number(input.info[YEAR]);
		check_is_number(input.info[LENGTH]);
		check_is_number(input.info[AGE]);
		check_is_number(input.info[FILM_ID]);
		check_is_number(input.info[COMMENT_ID]);
		check_is_number(input.info[USER_ID]);
		check_is_number(input.info[AMOUNT]);
		check_is_number(input.info[SCORE]);
		check_is_number(input.info[LIMIT]); 
}

void Command::check_is_number(string is_number)
{
	for(int i = 0; i < is_number.size(); i++)
		if(is_number[i] < '0' || is_number[i] > '9')
			throw Bad_request();
}

string Command::seprate_word(string &sentence,char delimiter = ' ')
{
	int line_index = 0;
	string word;
	while(line_index == 0 && sentence.size() != 0)
	{
		line_index = sentence.find(delimiter);
		word=sentence.substr(0,line_index);
		sentence=sentence.substr(line_index+1,sentence.size()-line_index);
	}
	if (word == sentence && line_index == -1)
		sentence="";
	return word;
}

Input Command::get_input()
{
	input.metod = seprate_word(line);
	input.request = seprate_word(line);
	string key, value;
	key = seprate_word(line);
	if(input.request == NOTIFICATIONS)
		if(key == READ)
		{
			key = seprate_word(line);
			input.request = NOTIFICATIONS_READ;
		}
	while(line != "")
	{
		key = seprate_word(line);
		value = seprate_word(line);
		input.info[key] = value;
	}
	check_format();
	return input;
}
