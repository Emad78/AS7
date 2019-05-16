#include "system.h"

System::System()
{
	money = 0;
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
			input = command->get_input();
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

Person* System::search_user(string username)
{
	for(int i = 0; i < users.size(); i++)
		if(username == users[i]->get_username())
			return users[i];
	return NULL;
}

void System::metod_detect()
{
	string metod = input.metod;
	if(metod == PUT)
		put_metod();
	else if(metod == POST)
		post_metod();
	else if(metod == GET)
		get_metod();
	else if(metod == DELETE)
		delete_metod();
	else
		throw Bad_request();
}

void System::post_metod()
{
	string re = input.request;
	if(re == LOGIN)
		login();
	else if(re == SIGNUP)
		signup();
	else if(re == FILMS)
		post_films();
	else if(re == MONEY)
		post_money();
	else if(re == REPLIES)
		replies();
/*	else if(re == FOLLOWERS)
		post_followers();
	else if(re == BUY)
		buy();
	else if(re == RATE)
		rate();
	else if(re == COMMENTS)
		post_comments();
*/	else
		throw Not_found();
}

void System::replies()
{
	if(input.info[FILM_ID] == "" || input.info[CONTENT] == ""
		|| input.info[COMENT_ID] == "")
		throw Bad_request();	
	check_user(true);
	if(search_film(stoi(input.info[FILM_ID])) == NULL)
		throw Not_found();
	Film* now_film = check_film_for_publisher();
	send_reply(now_film); 
}

void System::send_reply(Film* now_film)
{
	int person_id = now_film->reply(input);
	send_notif(person_id);
}

void System::send_notif(int person_id)
{
	users[person_id]->catch_notif(input);
}

void System::post_money()
{
	if(input.info[AMOUNT] == "")
	{
		check_user(true);
		money -= now_user->catch_money();
	}
}

void System::post_films()
{
	if(input.info[NAME] == "" || input.info[YEAR] == ""
		|| input.info[LENGTH] == "" || input.info[PRICE] == ""
		|| input.info[SUMMARY] == "" || input.info[DIRECTOR] == "")
		throw Bad_request();
	check_user(true);
	Film* new_film;
	new_film = new Film(input, films.size() + 1);
	films.push_back(new_film);
	now_user->add_my_film(new_film);
	cout<<OK<<endl;
}

void System::signup()
{
	if(input.info[USERNAME] == "" || input.info[PASSWORD] == ""
		|| input.info[EMAIL] == "" || input.info[AGE] == "")
		throw Bad_request();
	Person* new_user;
	if(search_user(input.info[USERNAME]) != NULL)
		throw Bad_request();
	if(input.info[PUBLISHER] == "true")
		new_user = new Publisher(input, users.size() + 1);
	else
		new_user = new Person(input, users.size() + 1);
	users.push_back(new_user);
	now_user = new_user;
	cout<<OK<<endl;
}

void System::login()
{
	if(input.info[USERNAME] == "" || input.info[PASSWORD] == "")
		throw Bad_request();
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
	if(input.request == FILMS)
		put_films();
	else
		throw Not_found();
}

Film* System::check_film_for_publisher()
{
	Film* now_film = now_user->search_my_film(stoi(input.info[FILM_ID])); 
	if(now_film == NULL)
	{
		delete now_film;
		throw Permission_denied();
	}
	if(now_film->get_is_visible() == false)
		throw Bad_request();
	return now_film;	
}

void System::put_films()
{
	check_user(true);
	if(search_film(stoi(input.info[FILM_ID])) == NULL)
		throw Not_found();
	Film* now_film = check_film_for_publisher(); 
	now_film->edit(input);
}

Film* System::search_film(int film_id)
{
	for(int i = 0; i < films.size(); i++)
	if(film_id == films[i]->get_id())
		return films[i];
	return NULL;
}

void System::get_metod()
{
	cout<<2<<endl;
	string re = input.request;
	if(re == FOLLOWERS)
		get_followers();
	else if(re == PUBLISHED)
		published();
/*	else if(re == FILMS)
		get_films();
	else if(re == PURCHASED)
		purchased();
	else if(re == NOTIFICATIONS)
		notifications();
	else if(re == NOTIFICATIONSREAD)
		notificationsread();
*/	else 
		throw Bad_request();
}

void System::published()
{
	check_user(true);
	now_user->print_published(input);
}

void System::get_followers()
{
	cout<<1<<endl;
	check_user(true);
	cout<<1<<endl;
	now_user->print_followers();
}

void System::delete_metod()
{
	string re = input.request;
	if(re == FILMS)
		delete_films();
/*	else if(re == COMMENTS)
		delete_comments();
*/	else 
		throw Bad_request();
}

void System::delete_films()
{
	check_user(true);
	Film* deleted_film;
	if(search_film(stoi(input.info[FILM_ID])) == NULL)
		throw Not_found();
	deleted_film = now_user->search_my_film(stoi(input.info[FILM_ID]));
	if(deleted_film == NULL)
		throw Permission_denied();
	deleted_film->_delete();
	cout<<OK<<endl;
}

void System::check_user(bool is_publisher)
{
	if(now_user == NULL)
		throw Permission_denied();		
	if(now_user->get_is_publisher() != is_publisher)
		throw Permission_denied();
}






