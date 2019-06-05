#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>
#include "../refrence.h"
#include "../system.h"


class LoginHandler : public RequestHandler {
private:
	System* system;
public:
	LoginHandler(System* _system);
	Response *callback(Request *);
};

class SignupHandler : public RequestHandler {
private:
	System* system;
public:
	SignupHandler(System* _system);
	Response *callback(Request *);
};

class HousetHandler : public TemplateHandler {
private:
	System* system;	
public:
  HousetHandler(System* _system, std::string filePath);
  std::map<std::string, std::string> handle(Request *req);
};


class AddfilmHandler : public RequestHandler {
private:
	System* system;
public:
	AddfilmHandler(System* _system);
	Response *callback(Request *);
};

class ProfileHandler : public TemplateHandler {
private:
	System* system;	
public:
  ProfileHandler(System* _system, std::string filePath);
  std::map<std::string, std::string> handle(Request *req);
};

class HouseHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class FilmdetailsHandler : public TemplateHandler {
private:
	System* system;	
public:
  FilmdetailsHandler(System* _system, std::string filePath);
  std::map<std::string, std::string> handle(Request *req);
};

#endif
