#include "command.h"

Command::command()
{
	set();
}

void Command::set()
{
	Input.info.insert({NAME, ""});
	Input.info.insert({PRICE, ""});
	Input.info.insert({DIRECTOR, ""});
	Input.info.insert({MAX_YEAR, ""});
	Input.info.insert({MIN_YEAR, ""});
	Input.info.insert({MIN_RATE, ""});
	Input.info.insert({YEAR, ""});
	Input.info.insert({LENGTH, ""});
	Input.info.insert({SUMMARY, ""});
	Input.info.insert({USERNAME, ""});
	Input.info.insert({PASSWORD, ""});
	Input.info.insert({AGE, ""});
	Input.info.insert({EMAIL, ""});
	Input.info.insert({PUBLISHER, ""});
	Input.info.insert({FILM_ID, ""});
	Input.info.insert({COMENT_ID, ""});
	Input.info.insert({CONTENT, ""});
	Input.info.insert({USER_ID, ""});
	Input.info.insert({AMOUNT, ""});
	Input.info.insert({SCORE, ""});
	Input.info.insert({LIMIT, ""});	
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

Input Command::get_input(string line)
{
	set();
	Input.method = check_method(seprate_word(line));
	Input.request = check_request(seprate_word(line));
	seprate_word(line);
	string key, value;
	while(line != "")
	{
		key = seprate_word(line);
		value = seprate_word(line);
		Input.info[key] = value;        //hashing
	}
}

