#include "set_input.h"

void set_login_input(Input&  input, Request *req)
{
	input.metod = POST;
	input.request = LOGIN;
	input.info[USERNAME] = req->getBodyParam(USERNAME);
	input.info[PASSWORD] = req->getBodyParam(PASSWORD);
}