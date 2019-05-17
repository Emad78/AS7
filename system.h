#ifndef SYSTEM_H
#define SYSTEM_H

#include "refrence.h"
#include "film.h"
#include "person.h"
#include "publisher.h"
#include "command.h"
#include "bad_request.h"
#include "not_found.h"
#include "permission_denied.h"

class System
{
private:
	vector<Film*> films;
	vector<Person*> users;
	int money;
	Command* command;
	Person* now_user;
	Input input;
public:
	System();
	void run();
	void process();
	void metod_detect();
	void put_metod();
	void post_metod();
	void get_metod();
	void delete_metod();
	void buy();
	void add_money_for_publisher(Film* now_film);
	void signup();
	void login();
	void post_films();
	void put_films();
	void delete_films();
	void check_user(bool is_publisher);
	void get_followers();
	void post_money();
	void published();
	void replies();
	void delete_comments();
	void post_followers();
	void send_reply(Film* now_film);
	void send_reply_notif(int person_id);
	Film* check_film_for_publisher();
	Person* search_user(string username);
	Person* search_user_whith_id(int user_id);
	Film* search_film(int film_id);
	~System();
};

#endif