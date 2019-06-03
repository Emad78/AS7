#include "examples/handlers.hpp"
#include "examples/my_server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  try {
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.get("/login", new ShowPage("static/login.html"));
    server.post("/login", new LoginHandler());
    server.get("/signup", new ShowPage("static/signup.html"));
    server.post("/signup", new SignupHandler());
    server.post("/house", new HouseHandler());    
    server.get("/house", new ShowPage("static/house.html"));
    server.get("/add_film", new ShowPage("static/add_film.html"));        
    server.post("/add_film", new AddfilmHandler());
    server.get("/film_details", new ShowPage("static/film_details.html"));        
    server.post("/afilm_details", new FilmdetailsHandler());
    server.get("/profile", new ShowPage("static/profile.html"));            
    server.post("/profile", new ProfileHandler());    
    server.get("/home.png", new ShowImage("static/home.png"));
    server.get("/", new ShowPage("static/home.html"));
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
