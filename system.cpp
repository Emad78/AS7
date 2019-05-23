#include "system.h"

System::System()
{
	money = 0;
	users.clear();
	now_user = NULL;
	vector<int> empty = {0};
	suggestions.push_back(empty);	
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
	while(getline(cin, line))
	{
		try
		{
			if(line == "")
				continue;
			command = new Command(line);
			input = command->get_input();
			process();
		}catch(exception& ex)
		{
			cout<<ex.what()<<endl;
		}
		delete command;
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
	if(metod == POST)
		post_metod();
	else if(metod == GET)
		get_metod();
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
	else if(re == LOGOUT)
		logout();
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
	else if(re == COMMENTS)
		post_comments();
	else if(re == PUT_FILMS)
		put_films();	
	else if(re == DELETE_FILMS)
		delete_films();
	else if(re == DELETE_COMMENTS)
		delete_comments();				
	else
		throw Not_found();
}

void System::put_films()
{
	check_user(true);
	if(search_film(stoi(input.info[FILM_ID])) == NULL)
		throw Not_found();
	Film* now_film = check_film_for_publisher();
	film_exist(now_film); 
	now_film->edit(input);
	cout<<OK<<endl;
}


void System::post_comments()
{
	user_exist();
	if(input.info[FILM_ID] == "" || input.info[CONTENT] == "")
		throw Bad_request();	
	Film* now_film = search_film(stoi(input.info[FILM_ID]));
	film_exist(now_film);
	if(now_film == NULL)
		throw Not_found();
	int publisher_id;
	if(!now_user->search_bought_film(now_film->get_id()))
		throw Permission_denied();
	publisher_id = now_film->catch_comment(input.info[CONTENT], now_user->get_username(), now_user->get_id());
	string notif = "User ";
	notif += now_user->get_username();
	notif += " with id ";
	notif += to_string(now_user->get_id());
	notif += " comment on your film ";
	notif += now_film->get_name();
	notif += " with id ";
	notif += to_string(now_film->get_id());
	notif += ".";
	users[publisher_id]->catch_notif(notif);
	cout<<OK<<endl;
}

void System::rate()
{
	user_exist();
	if(input.info[FILM_ID] == "" || input.info[SCORE] == "")
		throw Bad_request();
	Film* now_film = search_film(stoi(input.info[FILM_ID]));
	film_exist(now_film);
	if(!now_user->search_bought_film(now_film->get_id()))
		throw Permission_denied();
	now_film->rating(stoi(input.info[SCORE]), now_user->get_id());
	Person* publisher = search_user_whith_id(now_film->get_publisher_id());
	string notif = "User ";
	notif += now_user->get_username(); 
	notif += " with id "; 
	notif += to_string(now_user->get_id());
	notif += " rate your film ";
	notif += now_film->get_name();
	notif += " with id ";
	notif += to_string(now_film->get_id());
	notif += ".";
	publisher->catch_notif(notif);
	cout<<OK<<endl;
}

void System::buy()
{
	user_exist();
	if(input.info[FILM_ID] == "")
		throw Bad_request();
	Film* now_film = search_film(stoi(input.info[FILM_ID]));
	film_exist(now_film);
	if(now_user->search_bought_film(now_film->get_id()))
	{
		cout<<OK<<endl;
		return;
	}
	if(now_user->get_money() < now_film->get_price())
		throw Permission_denied();
	now_user->update_money((-1) * now_film->get_price());
	update_suggestions(now_film->get_id());
	now_user->add_bought_film(now_film);
	add_money_for_publisher(now_film);
	money = now_film->get_price();
	cout<<OK<<endl;
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
	string notif = "User ";
	notif += now_user->get_username();
	notif += " with id ";
	notif += to_string(now_user->get_id());
	notif += " buy your film ";
	notif += now_film->get_name();
	notif += " with id ";
	notif += to_string(now_film->get_id());
	notif += ".";
	publisher->catch_notif(notif); 
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
	user_exist();
	if(input.info[USER_ID] == "")
		throw Bad_request();
	if(!users[stoi(input.info[USER_ID]) - 1]->get_is_publisher() || stoi(input.info[USER_ID]) > users.size())
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
	film_exist(now_film);
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
	string notif = "Publisher ";
	notif += now_user->get_username();
	notif += " with id ";
	notif += to_string(now_user->get_id());
	notif += " reply to your comment.";
	users[person_id - 1]->catch_notif(notif); 
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
		user_exist();
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
	now_user->inform_followers();
	add_new_for_suggest();
	cout<<OK<<endl;
}

void System::signup()
{
	if(now_user != NULL)
		throw Bad_request();
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
	if(now_user != NULL)
		throw Bad_request();	
	if(input.info[USERNAME] == "" || input.info[PASSWORD] == "")
		throw Bad_request();
	Person* new_user;
	new_user = search_user(input.info[USERNAME]);
	if(new_user == NULL)
		throw Bad_request();
	if(new_user->get_password() != input.info[PASSWORD])
	{
		throw Bad_request();		
	}
	now_user = new_user;	
	cout<<OK<<endl;
}

void System::logout()
{
	if(now_user == NULL)
		throw Bad_request();
	now_user = NULL;
	cout<<OK<<endl;
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
		throw Not_found();
	return now_film;	
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
	else if(re == MONEY)
		get_money();
	else 
		throw Bad_request();
}

void System::get_money()
{
	user_exist();
	if(now_user->get_username() != ADMIN)
		cout<<now_user->get_money()<<endl;
	if(now_user->get_username() == ADMIN)
		cout<<money<<endl;
}

void System::notifications_read()
{
	user_exist();
	now_user->read(_READ, stoi(input.info[LIMIT]));		
}

void System::notifications()
{
	user_exist();
	now_user->read(NOT_READ, ALL);	
}

void System::purchased()
{
	if(now_user == NULL)
		throw Permission_denied();
		vector<Film*> searched = seaerh_films_by_filters(now_user->get_bought_films());
		print_films(searched, ALL);	
}

void System::get_films()
{
	user_exist();
	if(input.info[FILM_ID] == "")
	{
		vector<Film*> searched = seaerh_films_by_filters(films);
		print_films(searched, EXISTED);
	}
	else
	{
		Film* now_film = search_film(stoi(input.info[FILM_ID]));
		film_exist(now_film);
		now_film->print_details();
		now_film->print_comments();
		print_recomend(now_film->get_id());
	}
}

void System::print_recomend(int id)
{
	/*Film* printed;
	vector<double> copy_rates = rates;
	vector<int> num = number;
	copy_rates.erase(copy_rates.begin() + id -1);
	num.erase(num.begin() + id - 1);
	int number = 0, max, max_index;
	cout<<"Recommendation Film"<<endl;
	cout<<"#. Film Id | Film Name | Film Length | Film Director"<<endl;
	while(number < 4 && copy_rates.size() != 0)
	{
		max_index = max_element(copy_rates.begin(), copy_rates.end()) - copy_rates.begin();;
		printed = search_film(num[max_index]);
		try
		{
			film_exist(printed);
			if(printed->get_publisher_id() == now_user->get_id())
				throw Bad_request();
		}catch(exception&)
		{
			copy_rates.erase(copy_rates.begin() + max_index);
			num.erase(num.begin() + max_index);
			continue;
		}
		copy_rates.erase(copy_rates.begin() + max_index);
		num.erase(num.begin() + max_index);
		number++;
		printed->print(number);
	}
*/}

void System::published()
{
	check_user(true);
	vector<Film*> my_films = seaerh_films_by_filters(now_user->get_my_films());
	print_films(my_films, EXISTED);
}

void System::print_films(vector<Film*> printed, int status)
{
	cout<<"#. "<<"Film Id"<<" | "<<"Film Name"<<" | ";
	cout<<"Film Length"<<" | "<<"Film price"<<" | ";
	cout<<"Rate"<<" | "<<"Production Year"<<" | ";
	cout<<"Film Director"<<endl;
	int number = 1;
	for(int i = 0; i < printed.size(); i++)
	{
		if(status  == EXISTED && !printed[i]->get_is_visible())
			continue;
		cout<<to_string(number)<<". "<<printed[i]<<endl;
		number++;
	}

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

void System::delete_comments()
{
	check_user(true);
	if(input.info[FILM_ID] == "" || input.info[COMMENT_ID] == "")
		throw Bad_request();
	Film* now_film;
	now_film = check_film_for_publisher();
	film_exist(now_film);
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
	user_exist();
	if(now_user->get_is_publisher() != is_publisher)
		throw Permission_denied();
}

bool System::film_exist(Film* film)
{
	if(film->get_is_visible() == false)
		throw Not_found();
	return true;
}

void System::user_exist()
{
	if(now_user == NULL)
		throw Permission_denied();			
}

void System::add_new_for_suggest()
{
	for(int i = 0; i < suggestions.size(); i++)
		suggestions[i].push_back(0);
	vector<int> new_film(suggestions.size() + 1, 0);
	suggestions.push_back(new_film);
}

void System::update_suggestions(int film_id)
{
	vector<Film*> relations = now_user->get_bought_films();
	for(int i = 0; i < relations.size(); i++)
	{
		suggestions[film_id][relations[i]->get_id()]++;
		suggestions[relations[i]->get_id()][film_id]++;		
	}
}