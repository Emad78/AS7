#include "command.h"

Command::Command(string _line)
{
	set();
	line = _line;
}

void Command::set()
{
	input.info.insert({NAME, ""});
	input.info.insert({PRICE, ""});
	input.info.insert({DIRECTOR, ""});
	input.info.insert({MAX_YEAR, ""});
	input.info.insert({MIN_YEAR, ""});
	input.info.insert({MIN_RATE, ""});
	input.info.insert({YEAR, ""});
	input.info.insert({LENGTH, ""});
	input.info.insert({SUMMARY, ""});
	input.info.insert({USERNAME, ""});
	input.info.insert({PASSWORD, ""});
	input.info.insert({AGE, ""});
	input.info.insert({EMAIL, ""});
	input.info.insert({PUBLISHER, ""});
	input.info.insert({FILM_ID, ""});
	input.info.insert({COMMENT_ID, ""});
	input.info.insert({CONTENT, ""});
	input.info.insert({USER_ID, ""});
	input.info.insert({AMOUNT, ""});
	input.info.insert({SCORE, ""});
	input.info.insert({LIMIT, ""});	
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
	set();
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
		input.info[key] = value;        //hashing
	}
	cout<<"metod: "<< input.metod<<endl;
	cout<<"request: "<< input.request<<endl;
	cout<<"id: "<< input.info[FILM_ID]<<endl;

	return input;
}

