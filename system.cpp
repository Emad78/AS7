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
	else if(re == FOLLOWERS)
		post_followers();
	else if(re == BUY)
		buy();
	else if(re == RATE)
		rate();
/*	else if(re == COMMENTS)
		post_comments();
*/	else
		throw Not_found();
}

void System::rate()
{
	if(now_user == NULL)
		throw Permission_denied();
	if(input.info[FILM_ID] == "" || input.info[SCORE] == "")
		throw Bad_request();
	Film* now_film = search_film(stoi(input.info[FILM_ID]));
	now_film->rating(stoi(input.info[SCORE]), now_user->get_id());
	Person* publisher = search_user_whith_id(now_film->get_publisher_id());
	publisher->catch_notif(now_user->get_username() + " rate to your film");   /////////////notif	
}

void System::buy()
{
	if(now_user == NULL)
		throw Permission_denied();
	if(input.info[FILM_ID] == "")
		throw Bad_request();
	Film* now_film = search_film(stoi(input.info[FILM_ID]));
	if(now_user->get_money() < now_film->get_price())
		throw Bad_request();
	now_user->update_money((-1) * now_film->get_price());
	now_user->add_bought_film(now_film);
	add_money_for_publisher(now_film);
	money = now_film->get_price();
}

void System::add_money_for_publisher(Film* now_film)
{
	Person* publisher = search_user_whith_id(now_film->get_publisher_id());
	double factor = 0;
	int price = now_film->get_price(), rate = now_film->_rate();
	if(rate < MEDIUM)
		factor = POOR_FACTOR;
	if(rate >= MEDIUM && rate < GOOD)
		factor = MEDIUM_FACTOR;
	if(rate >= GOOD)
		factor = GOOD_FACTOR;
	publisher->update_money(factor * price);
	publisher->catch_notif(now_user->get_username() + " buy your film"); //////////notif
}

Person* System::search_user_whith_id(int user_id)
{
	for(int i = 0; i < users.size(); i++)
		if(users[i]->get_id() == user_id)
			return users[i];
	return NULL;
}

void System::post_followers()
{
	if(now_user == NULL)
		throw Permission_denied();
	if(input.info[USER_ID] == "")
		throw Bad_request();
	if(!users[stoi(input.info[USER_ID]) - 1]->get_is_publisher())
		throw Bad_request();
	users[stoi(input.info[USER_ID]) - 1]->add_follower(now_user);
	cout<<OK<<endl;
}

void System::replies()
{
	if(input.info[FILM_ID] == "" || input.info[CONTENT] == ""
		|| input.info[COMMENT_ID] == "")
		throw Bad_request();	
	check_user(true);
	if(search_film(stoi(input.info[FILM_ID])) == NULL)
		throw Not_found();
	Film* now_film = check_film_for_publisher();
	send_reply(now_film); 
	cout<<OK<<endl;
}

void System::send_reply(Film* now_film)
{
	int person_id = now_film->reply(input);
	send_reply_notif(person_id);
}

void System::send_reply_notif(int person_id)
{
	string content = now_user->get_username() +"reply to you";    ///////////notif
	users[person_id]->catch_notif(content); 
}

void System::post_money()
{
	if(input.info[AMOUNT] == "")
	{
		check_user(true);
		money -= now_user->catch_money();
	}
	else
	{
		if(now_user == NULL)
			throw Permission_denied();
		now_user->update_money(stoi(input.info[AMOUNT]));
	}
	cout<<OK<<endl;
}

void System::post_films()
{
	if(input.info[NAME] == "" || input.info[YEAR] == ""
		|| input.info[LENGTH] == "" || input.info[PRICE] == ""
		|| input.info[SUMMARY] == "" || input.info[DIRECTOR] == "")
		throw Bad_request();
	check_user(true);
	Film* new_film;
	new_film = new Film(input, films.size() + 1, now_user->get_id());
	films.push_back(new_film);
	now_user->add_my_film(new_film);
	now_user->inform_followers();    /////////notif
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
	cout<<OK<<endl;
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
	string re = input.request;
	if(re == FOLLOWERS)
		get_followers();
	else if(re == PUBLISHED)
		published();
	else if(re == FILMS)
		get_films();
	else if(re == PURCHASED)
		purchased();
	else if(re == NOTIFICATIONS)
		notifications();
	else if(re == NOTIFICATIONS_READ)
		notifications_read();
	else 
		throw Bad_request();
}

void System::notifications_read()
{
	if(now_user == NULL)
		throw Permission_denied();
	now_user->read(_READ);		
}

void System::notifications()
{
	if(now_user == NULL)
		throw Permission_denied();
	now_user->read(NOT_READ);	
}

void System::purchased()
{
	if(now_user == NULL)
		throw Permission_denied();
		vector<Film*> searched = seaerh_films_by_filters(now_user->get_bought_films());
		print_films(searched);	
}

void System::get_films()
{
	if(now_user == NULL)
		throw Permission_denied();
	if(input.info[FILM_ID] == "")
	{
		vector<Film*> searched = seaerh_films_by_filters(films);
		print_films(searched);
	}
}

void System::published()
{
	check_user(true);
	vector<Film*> my_films = seaerh_films_by_filters(now_user->get_my_films());
	print_films(my_films);
}

void System::print_films(vector<Film*> printed)
{
	cout<<"#. "<<"Film Id"<<" | "<<"Film Name"<<" | ";
	cout<<"Film Length"<<" | "<<"Film Price"<<" | ";
	cout<<"Rate"<<" | "<<"Production Year"<<" | ";
	cout<<"Film Director"<<endl;
	for(int i = 0; i < printed.size(); i++)
		cout<<to_string(i+1)<<". "<<printed[i]<<endl;

}

vector<Film*> System::seaerh_films_by_filters(vector<Film*> source)
{
	vector<Film*> searched = source;
	if(input.info[NAME] != "")
		searched = filter_by_name(searched, input.info[NAME]);	
	if(input.info[MIN_RATE] != "")
		searched = filter_by_min_rate(searched, stof(input.info[MIN_RATE]));
	if(input.info[PRICE] != "")
		searched = filter_by_price(searched, stoi(input.info[PRICE]));
	if(input.info[MIN_YEAR] != "")
		searched = filter_by_min_year(searched, stoi(input.info[MIN_YEAR]));
	if(input.info[MAX_YEAR] != "")
		searched = filter_by_max_year(searched, stoi(input.info[MAX_YEAR]));
	if(input.info[DIRECTOR] != "")
		searched = filter_by_director(searched, input.info[DIRECTOR]);
	sort_films_by_id(searched);
	return searched;			
}

void System::sort_films_by_id(vector<Film*> &sorted)
{
	Film* temp;
	for(int i = 0; i < sorted.size(); i++)
		for(int j = i; j < sorted.size(); j++)
			if(sorted[j]->get_id() < sorted[i]->get_id())
			{
				temp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = temp;
			}
}

vector<Film*> System::filter_by_name(vector<Film*> source, string name)
{
	vector<Film*> filtered;
	filtered.clear();
	for(int i = 0; i < source.size(); i++)
		if(name == source[i]->get_name())
			filtered.push_back(source[i]);
	return filtered;
}

vector<Film*> System::filter_by_min_rate(vector<Film*> source, double min_rate)
{
	vector<Film*> filtered;
	filtered.clear();
	for(int i = 0; i < source.size(); i++)
		if(min_rate <= source[i]->_rate())
			filtered.push_back(source[i]);
	return filtered;
}

vector<Film*> System::filter_by_price(vector<Film*> source, int price)
{
	vector<Film*> filtered;
	filtered.clear();
	for(int i = 0; i < source.size(); i++)
		if(price == source[i]->get_price())
			filtered.push_back(source[i]);
	return filtered;
}

vector<Film*> System::filter_by_min_year(vector<Film*> source, int min_year)
{
	vector<Film*> filtered;
	filtered.clear();
	for(int i = 0; i < source.size(); i++)
		if(min_year <= source[i]->get_year())
			filtered.push_back(source[i]);
	return filtered;
}

vector<Film*> System::filter_by_max_year(vector<Film*> source, int max_year)
{
	vector<Film*> filtered;
	filtered.clear();
	for(int i = 0; i < source.size(); i++)
		if(max_year >= source[i]->get_year())
			filtered.push_back(source[i]);
	return filtered;
}

vector<Film*> System::filter_by_director(vector<Film*> source, string director)
{
	vector<Film*> filtered;
	filtered.clear();
	for(int i = 0; i < source.size(); i++)
		if(director == source[i]->get_director())
			filtered.push_back(source[i]);
	return filtered;
}

void System::get_followers()
{
	check_user(true);
	now_user->print_followers();
}

void System::delete_metod()
{
	string re = input.request;
	if(re == FILMS)
		delete_films();
	else if(re == COMMENTS)
		delete_comments();
	else 
		throw Bad_request();
}

void System::delete_comments()
{
	check_user(true);
	if(input.info[FILM_ID] == "" || input.info[COMMENT_ID] == "")
		throw Bad_request();
	Film* now_film;
	now_film = check_film_for_publisher();
	now_film->delete_comment(input);
	cout<<OK<<endl;
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