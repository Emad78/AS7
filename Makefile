cc := g++ -c -std=c++11

all:a.out

a.out: main.o command.o system.o publisher.o person.o film.o coment.o notification.o
	g++ main.o command.o system.o publisher.o person.o film.o coment.o notification.o

main.o: main.cpp refrence.h system.h
	$(cc) main.cpp

command.o: command.cpp command.h refrence.h bad_request.h not_found.h permission_denied.h
	$(cc) command.cpp

system.o: system.cpp system.h refrence.h bad_request.h not_found.h permission_denied.h film.h person.h publisher.h
	$(cc) system.cpp

publisher.o: publisher.cpp publisher.h person.h refrence.h bad_request.h not_found.h permission_denied.h
	$(cc) publisher.cpp

person.o: person.cpp person.h refrence.h bad_request.h not_found.h permission_denied.h
	$(cc) person.cpp

film.o: film.cpp film.h refrence.h bad_request.h not_found.h permission_denied.h
	$(cc) film.cpp

coment.o: coment.cpp coment.h refrence.h bad_request.h not_found.h permission_denied.h
	$(cc) coment.cpp

notification.o: notification.cpp notification.h refrence.h bad_request.h not_found.h permission_denied.h
	$(cc) notification.cpp

.PHONY: clean
clean:
	rm *.o 
	rm a.out