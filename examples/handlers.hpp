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

class MapHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class SignupHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class AddfilmHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class ProfileHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class HouseHandler : public TemplateHandler {
public:
  Response *callback(Request *);
};

class FilmdetailsHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

#endif
