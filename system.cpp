#include "system.h"

System::System()
{
	system_money = 0;
	command = new Command();
	users.clear();
	now_user = NULL;	
}

System::~System()
{
	for(int i = films.size() - 1; i >= 0; i--)
		delete films[i];
	for(int i = users.size() - 1; i >= 0; i--)
		delete users[i];
	delete command;
	delete now_user;
}

void System::run()
{
	string line;
	while(true)
	{
		try
		{
			getline(cin, line);
			input = command.get_input(line);
			process();

		}catch(exception& ex)
		{
			cout<<ex.what()<<endl;
		}
	}
}

void System::process()
{
	metod_detect();	
}

void System::metod_detect()
{
	switch (input.metod)
	{
		case PUT:
			put_metod();
			break;
		case POST:
			post_metod();
			break;
		case GET:
			get_metod();
			break;
		case DELETE:
			delete_metod();
			break;
		default:
			throw Bad_request();
			break;
	}
}

void System::post_metod()
{
	switch(input.request)
	{
		case LOGIN:
			login();
			break;
		case SIGNUP:
			signup();
			break;
		case FILMS:
			post_films();
			break;
		case MONEY:
			post_money();
			break;
		case REPLIES:
			replies();
			break;
		case FOLLOWERS:
			post_followers();
			break;
		case BUY:
			buy();
			break;
		case RATE:
			rate();
			break;
		case COMMENTS:
			post_comments();
			break;
		default:
			throw Not_found();
			break;
	}
}
void System::signup()
{
	Person* new_user;
	if(input.info[PUBLISHER] == "true")
		new_user = Publisher(input, users.size() + 1);
	else
		new_user = Person(input, users.size() + 1);
	users.push_back(new_user);
}

void System::put_metod()
{
	switch(input.request)
	{
		case FILMS:
			put_films();
			break;
		default:
			throw Not_found();
			break;
	}
}

void System::get_metod()
{
	switch(input.request)
	{
		case FOLLOWERS:
			get_followers();
			break;
		case PUBLISHED:
			published();
			break;
		case FILMS:
			get_films();
			break;
		case PURCHASED:
			purchased();
			break;
		case NOTIFICATIONS:
			notifications();
			break;
		case NOTIFICATIONSREAD:
			notificationsread();
			break;
		default:
			throw Not_found();
			break;
	}
}

void System::delete_metod()
{
	switch (input.request)
	{
		case FILMS:
			delete_films();
			break;
		case COMMENTS:
			delete_comments();
			break;
		default:
			throw Not_found();
			break;
	}
}








