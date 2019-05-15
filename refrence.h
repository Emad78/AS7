#ifndef REFRENCE_H
#define REFRENCE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

#define USERNAME "username"
#define PASSWORD "password"
#define AGE "age"
#define EMAIL "email"
#define PUBLISHER "publisher"

#define NAME "name"
#define YEAR "year"
#define LENGTH "length"
#define PRICE "price"
#define SUMMARY "summary"
#define DIRECTOR "director"
#define FILM_ID "film_id"

#define MAX_YEAR "max_year"
#define MIN_YEAR "min_year"
#define MIN_RATE "min_rate"

#define COMENT_ID "coment_id"
#define CONTENT "content"

#define USER_ID "user_id"

#define AMOUNT "amount"

#define SCORE "score"

#define LIMIT "limit"

#define PUT "PUT"
#define POST "POST"
#define GET "GET"
#define DELETE "DELETE"

#define SIGNUP "signup"
#define LOGIN "login"
#define FILMS "films"
#define FOLLOWERS "followers"
#define MONEY "money"
#define PUBLISHED "published"
#define REPLIES "replies"
#define COMMENTS "comments"
#define BUY "buy"
#define RATE "rate"
#define PURCHASED "purchased"
#define NOTIFICATIONS "notifications"
#define READ "read"
#define NOTIFICATIONS_READ "notificationsread"

#define OK "ok"

using namespace std;

struct Input
{
	map<string,string> info;
	string metod;
	string request;
};

struct Info
{
	string username, email, password;
	int age;
	bool is_publisher;
};

struct Rate
{
	vector<double> score;
	vector<int> user_id;
};

#endif