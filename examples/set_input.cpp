#include "set_input.h"

void set_login_input(Input&  input, Request *req)
{
	input.metod = POSTT;
	input.request = LOGIN;
	input.info[USERNAME] = req->getBodyParam(USERNAME);
	input.info[PASSWORD] = req->getBodyParam(PASSWORD);
}

void set_signup_input(Input&  input, Request *req)
{
	input.metod = POSTT;
	input.request = SIGNUP;
	input.info[USERNAME] = req->getBodyParam(USERNAME);
	input.info[PASSWORD] = req->getBodyParam(PASSWORD);
	input.info[EMAIL] = req->getBodyParam(EMAIL);
	input.info[AGE] = req->getBodyParam(AGE);
	if(req->getBodyParam(PUBLISHER) == "Publisher")
		input.info[PUBLISHER] = "true";
	else
		input.info[PUBLISHER] = "";		
}

void set_addfilm_input(Input&  input, Request *req)
{
	input.metod = POSTT;
	input.request = FILMS;
	input.info[NAME] = req->getBodyParam(NAME);
	input.info[PRICE] = req->getBodyParam(PRICE);
	input.info[YEAR] = req->getBodyParam(YEAR);
	input.info[LENGTH] = req->getBodyParam(LENGTH);
	input.info[SCORE] = req->getBodyParam(SCORE);
	input.info[DIRECTOR] = req->getBodyParam(DIRECTOR);
	input.info[SUMMARY] = req->getBodyParam(SUMMARY);
}

void set_price_input(Input&  input, Request *req)
{
	input.metod = POSTT;
	input.request = MONEY;
	input.info[AMOUNT] = req->getBodyParam(PRICE);
}	

void set_myfilm_delete_input(Input&  input, Request *req)
{
	input.metod = POSTT;
	input.request = DELETE_FILMS;
	input.info[FILM_ID] = req->getQueryParam(FILM_ID);				
}	

void set_myfilm_input(Input&  input, Request *req)
{
	input.metod = GETT;
	input.request = PUBLISHED;
	if(req->getQueryParam(DIRECTOR) != "")
		input.info[DIRECTOR] = req->getQueryParam(DIRECTOR);
}

void set_bought_film_input(Input&  input, Request *req)
{
	input.metod = GETT;
	input.request = PURCHASED;
}

