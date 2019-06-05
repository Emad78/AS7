#include "handlers.hpp"
#include "set_input.h"

using namespace std;

LoginHandler::LoginHandler(System* _system)
:system(_system)
{}

Response *LoginHandler::callback(Request *req) {
  Input input;
  set_login_input(input, req);
  system->run(input);
  Response *res = Response::redirect("/house?publisher="+input.info[PUBLISHER]);
  res->setSessionId(input.info[ID]);
  return res;
}

SignupHandler::SignupHandler(System* _system)
:system(_system)
{}

Response *SignupHandler::callback(Request *req) {
  Input input;
  set_signup_input(input, req);
  system->run(input);
  Response *res = Response::redirect("/house?publisher="+input.info[PUBLISHER]);
  res->setSessionId(input.info[ID]);
  return res;
}

HousetHandler::HousetHandler(System* _system, string filePath) :system(_system), TemplateHandler(filePath) {}

map<string, string> HousetHandler::handle(Request *req) {
  map<string, string> context;
  Input input;
  if( req->getQueryParam(FILM_ID ) != "")
  {
    set_myfilm_delete_input(input, req);
    system->run(input);    
  }
  set_myfilm_input(input, req);
  system->run(input);
  input.info.insert({"999",""});
  system->show_films(input); 
  for(auto it = input.info.begin(); it != input.info.end(); it++)
    cout<<it->first<<endl;     
  context = input.info;
  req->setQueryParam(PUBLISHER, system->is_publisher(req->getSessionId()));
  context[PUBLISHER] = req->getQueryParam(PUBLISHER);
  return context;
}

AddfilmHandler::AddfilmHandler(System* _system)
:system(_system)
{}

Response *AddfilmHandler::callback(Request *req) {
  Input input;
  set_addfilm_input(input, req);
  input.info[ID] = req->getSessionId();
  system->run(input);
  Response *res = Response::redirect("/add_film?publisher=" + system->is_publisher(req->getSessionId()));
  return res;
}

ProfileHandler::ProfileHandler(System* _system, string filePath) :system(_system), TemplateHandler(filePath) {}

map<string, string> ProfileHandler::handle(Request *req) 
{
  map<string, string> context;
  if(req->getBodyParam(PRICE) != "")
    {
      Input input;
      set_price_input(input, req);
      system->run(input);
    }
  else if(req->getBodyParam(SCORE) != "")
  {
      Input input;
      set_score_input(input, req);
      system->run(input);
  }
  Input input;
  input.info.clear();    
  set_bought_film_input(input, req);
  system->run(input);
  input.info.insert({"999",""});
  context = input.info;
  return context;
}


Response *HouseHandler::callback(Request *req) {
  Response *res = Response::redirect("/house");
  return res;
}

FilmdetailsHandler::FilmdetailsHandler(System* _system, string filePath) :system(_system), TemplateHandler(filePath) {}

map<string, string> FilmdetailsHandler::handle(Request *req) {
  map<string, string> context;
  Input input;
  if(req->getBodyParam(FILM_ID) == "")
  {
    set_buy_input(input, req);
    system->run(input);
  }
  input.info.clear();
  set_details_input(input, req);
  system->run(input);
  context = input.info;
  for(auto it = context.begin(); it != context.end(); it++)
    cout<<it->second<<endl;     
  req->setQueryParam(PUBLISHER, system->is_publisher(req->getSessionId()));
  return context;
}
