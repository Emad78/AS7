CC=g++
STD=-std=c++11 
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: myserver.out

set_input.o : examples/set_input.cpp examples/set_input.h
	$(CC) $(CF) -c examples/set_input.cpp	

template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o template_parser.o

response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o response.o

request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o request.o

utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o utilities.o

server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o server.o

route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o route.o

handlers.o: examples/handlers.cpp server/server.hpp examples/set_input.h utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/handlers.cpp -o handlers.o

my_server.o: examples/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/my_server.cpp -o my_server.o

main.o: main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c main.cpp -o main.o

command.o: command.cpp command.h refrence.h bad_request.h not_found.h permission_denied.h
	$(CC) $(CF) -c command.cpp

system.o: system.cpp system.h refrence.h bad_request.h not_found.h permission_denied.h film.h person.h publisher.h
	$(CC) $(CF) -c system.cpp

publisher.o: publisher.cpp publisher.h person.h refrence.h bad_request.h not_found.h permission_denied.h
	$(CC) $(CF) -c  publisher.cpp

person.o: person.cpp person.h refrence.h bad_request.h not_found.h permission_denied.h
	$(CC) $(CF) -c person.cpp

film.o: film.cpp film.h refrence.h bad_request.h not_found.h permission_denied.h
	$(CC) $(CF) -c film.cpp

coment.o: coment.cpp coment.h refrence.h bad_request.h not_found.h permission_denied.h
	$(CC) $(CF) -c coment.cpp

notification.o: notification.cpp notification.h refrence.h bad_request.h not_found.h permission_denied.h
	$(CC) $(CF) -c notification.cpp

myserver.out: set_input.o my_server.o main.o handlers.o response.o request.o utilities.o server.o route.o template_parser.o command.o system.o publisher.o person.o film.o coment.o notification.o
	$(CC) $(CF) -o myserver.out set_input.o my_server.o handlers.o response.o request.o utilities.o server.o route.o template_parser.o main.o command.o system.o publisher.o person.o film.o coment.o notification.o

.PHONY: clean
clean:
	rm -rf $(TEMPLATE_DIR) *.o *.out &> /dev/null
