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
			command = new Command(line);
			input = command.get_input();
			process();
			delete command;

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

void System::search_user(string username)
{
	for(int i = 0; i < users.size(); i++)
		if(username == users[i]->get_username())
			return users[i];
	return NULL;
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

void System::post_films()
{
	if(input.info[NAME] == "" || input.info[YEAR] == ""
		|| input.info[LENGTH] == "" || input.info[PRICE] == ""
		|| input.info[SUMMARY] == "" || input.info[DIRECTORY] == "")
		throw Bad_request();
	if(now_user == NULL)
		throw Permission_denied();
	if(now_user->get_is_publisher() == false)
		throw Permission_denied();			
	Film* new_film;
	new_film = new Film(input, films.size() + 1);
	films.push_back(new_film);
	now_user->add_my_film(new_film);
	cout<<OK<<endl;
}

void System::signup()
{
	Person* new_user;
	if(search_user(input.info[USERNAME] != NULL))
		throw Bad_request();
	if(input.info[PUBLISHER] == "true")
		new_user = Publisher(input, users.size() + 1);
	else
		new_user = Person(input, users.size() + 1);
	users.push_back(new_user);
	now_user = new_user;
	cout<<OK<<endl;
}

void System::login()
{
	Person* new_user;
	new_user = search_user(input.info[USERNAME]);
	if(new_user == NULL)
		throw Bad_request();
	if(new_user->get_password() != input.info[PASSWORD])
	{
		delete new_user;
		throw Bad_request();		
	}
	now_user = new_user;
	cout<<OK<<endl;
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

void System::put_films()
{
	if(now_user->get_is_publisher() == false)
		throw Permission_denied();
	Film* now_film = now_user->search_my_film(input.info[FILM_ID]); 
	if(now_film == NULL)
	{
		delete now_film;
		throw Permission_denied();
	}
	now_film->edit(input);
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








