#include "command.h"

Command::command()
{
	set();
}

void Command::set()
{
	info.insert({NAME, ""});
	info.insert({PRICE, ""});
	info.insert({DIRECTOR, ""});
	info.insert({MAX_YEAR, ""});
	info.insert({MIN_YEAR, ""});
	info.insert({MIN_RATE, ""});
	info.insert({YEAR, ""});
	info.insert({LENGTH, ""});
	info.insert({SUMMARY, ""});
	info.insert({USERNAME, ""});
	info.insert({PASSWORD, ""});
	info.insert({AGE, ""});
	info.insert({EMAIL, ""});
	info.insert({PUBLISHER, ""});
}

string Command::seprate_word(string &sentence,char delimiter = ' ')
{
	int line_index = sentence.find(delimiter);
	string word;
	word=sentence.substr(0,line_index);
	sentence=sentence.substr(line_index+1,sentence.size()-line_index);
	if (word == sentence && line_index == -1)
		sentence="";
	return word;
}

void Command::input(string line)
{
	set();
	method = check_method(seprate_word(line));
	request = check_request(seprate_word(line));
	seprate_word(line);
	while(line != "")
	{
		info[seprate_word(line)] = seprate_word(line);
	}
}

