#include "handlers.hpp"
//#include "set_input.h"

using namespace std;

void set_login_input(Input&  input, Request *req)
{
  input.metod = POST;
  input.request = LOGIN;
  input.info[USERNAME] = req->getBodyParam(USERNAME);
  input.info[PASSWORD] = req->getBodyParam(PASSWORD);
}

LoginHandler::LoginHandler(System* _system)
:system(_system)
{}

Response *LoginHandler::callback(Request *req) {
  Input input;
  set_login_input(input, req);
  system->run(input);
  cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
  Response *res = Response::redirect("/house");
//  res->setSessionId("");//////////////////////
  return res;
}

Response *SignupHandler::callback(Request *req) {
  Response *res = Response::redirect("/house");
  return res;
}

Response *AddfilmHandler::callback(Request *req) {
  Response *res = Response::redirect("/add_film");
  return res;
}

Response *ProfileHandler::callback(Request *req) {
  Response *res = Response::redirect("/profile");
  return res;
}

Response *HouseHandler::callback(Request *req) {
  Response *res = Response::redirect("/house");
  return res;
}

Response *FilmdetailsHandler::callback(Request *req) {
  Response *res = Response::redirect("/film_details");
  return res;
}