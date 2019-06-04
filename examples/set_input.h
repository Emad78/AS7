#ifndef SET_INPUT_H
#define SET_INPUT_H

#include "../refrence.h"
#include "handlers.hpp"

void set_login_input(Input&  input, Request *req);
void set_signup_input(Input&  input, Request *req);
void set_addfilm_input(Input&  input, Request *req);
void set_price_input(Input&  input, Request *req);
void set_myfilm_input(Input&  input, Request *req);
void set_myfilm_delete_input(Input&  input, Request *req);
void set_bought_film_input(Input&  input, Request *req);

#endif