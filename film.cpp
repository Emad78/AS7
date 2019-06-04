#include "film.h"

Film::Film()
{
	rate.score.clear();
	rate.user_id.clear();	
	is_visible = false;
}

Film::Film(Input input, int _id, int _publisher_id)
{
	id = _id;
	year = stoi(input.info[YEAR]);
	length = stoi(input.info[LENGTH]);
	price = stoi(input.info[PRICE]);
	name = input.info[NAME];
	summary = input.info[SUMMARY];
	director = input.info[DIRECTOR];
	if(year <= 0 || length <= 0 || price <= 0)
		throw Bad_request();
	rate.score.clear();
	rate.user_id.clear();	
	is_visible = true;
	publisher_id = _publisher_id;
	rate.score.push_back(stoi(input.info[SCORE]));
	rate.user_id.push_back(_publisher_id);
}

void Film::edit(Input input)
{
	if(input.info[YEAR] != "")
		year = stoi(input.info[YEAR]);
	if(input.info[LENGTH] != "")
		length = stoi(input.info[LENGTH]);
	if(input.info[NAME] != "")
		name = input.info[NAME];
	if(input.info[SUMMARY] != "")
		summary = input.info[SUMMARY];
	if(input.info[DIRECTOR] != "")
		director = input.info[DIRECTOR];
	if(input.info[PRICE] != "")
		price = stoi(input.info[PRICE]);
}

int Film::get_id()
{
	return id;
}

bool Film::get_is_visible()
{
	return is_visible;
}

void Film::_delete()
{
	is_visible = false;
}

bool Film::is_same_film(Input input)
{
	if(input.info[NAME] != "")
		if(name != input.info[NAME])
			return false;
	if(input.info[MIN_RATE] != "")
		if(_rate() < stof(input.info[MIN_RATE]))
			return false;
	if(input.info[MIN_YEAR] != "")
		if(year < stoi(input.info[MIN_YEAR]))
			return false;
	if(input.info[MAX_YEAR] != "")
		if(year > stoi(input.info[MAX_YEAR]))
			return false;
	if(input.info[DIRECTOR] != "")
		if(director != input.info[DIRECTOR])
			return false;
	if(input.info[PRICE] != "")
		if(price != stoi(input.info[PRICE]))
			return false;		
	return true;
}

double Film::_rate()
{
	double avg = 0;
	for(int i = 0; i < rate.score.size(); i++)
		avg += rate.score[i];
	if(rate.score.size() == 0)
		return 0;
	return (avg / rate.score.size()); 
}

ostream& operator<<(ostream& out, Film* film)
{
	out<<"id: "<<film->id<<" | "<<"name: "<<film->name<<" | "<<"length: "<<film->length<<" | ";
	out<<"price: "<<film->price<<" | "<<setprecision(2)<<film->_rate()<<" | ";
	out<<"year: "<<film->year<<" | "<<"director: "<<film->director;
	return out;
}

int Film::reply(Input input)
{
	if(stoi(input.info[COMMENT_ID]) > comments.size())
		throw Bad_request();
	return comments[stoi(input.info[COMMENT_ID]) - 1]->reply(input);
}

void Film::delete_comment(Input input)
{
	if(stoi(input.info[COMMENT_ID]) > comments.size())
		throw Not_found();
	comments[stoi(input.info[COMMENT_ID]) - 1]->_delete();
}

int Film::get_price()
{
	return price;
}

int Film::get_publisher_id()
{
	return publisher_id;
}

void Film::rating(int score, int person_id)
{
	for(int i = 0; i < rate.user_id.size(); i++)
		if(person_id == rate.user_id[i])
		{
			rate.score[i] = score;
			return;
		}
	rate.user_id.push_back(person_id);
	rate.score.push_back(score);
}

int Film::get_year()
{
	return year;
}

string Film::get_name()
{
	return name;
}

string Film::get_director()
{
	return director;
}

int Film::catch_comment(string content, string name, int id)
{
	Comment* new_comment = new Comment(content, comments.size() + 1, id);
	comments.push_back(new_comment);
	return publisher_id - 1;
}

void Film::print_details()
{
	cout<<"Details of Film "<<name<<endl;
	cout<<"Id = "<<id<<endl;
	cout<<"Director = "<<director<<endl;
	cout<<"Length = "<<length<<endl;
	cout<<"Year = "<<year<<endl;
	cout<<"Summary = "<<summary<<endl;
	cout<<"Rate = "<<setprecision(2)<<_rate()<<endl;
	cout<<"Price = "<<price<<endl<<endl;
}

void Film::print_comments()
{
	cout<<"Comments"<<endl;
	for(int i = 0; i < comments.size(); i++)
		if(comments[i]->get_is_visible() == true)
			cout<<comments[i];
	cout<<endl;
}

void Film::print(int number)
{
	cout<<number<<". "<<id<<" | "<<name<<" | "<<length<<" | "<<director<<endl;
}