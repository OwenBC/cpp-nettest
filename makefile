CC=g++
#  -g		- adds debugging
#  -Wall	- turn on most compiler warnings
FLAGS=-g -Wall 
LIBS=-pthread -lrt

# TARGET=app

all: app

app: app.o game.o
	$(CC) $(FLAGS) -o app app.o game.o server.o client.o

app.o: app.cpp game.hpp
	$(CC) $(FLAGS) -c app.cpp

game.o: game.cpp game.hpp server.o client.o
	$(CC) $(FLAGS) -c game.cpp server.o client.o

server.o: server.cpp server.hpp
	$(CC) $(FLAGS) -c server.cpp

client.o: client.cpp client.hpp
	$(CC) $(FLAGS) -c client.cpp

clean:
	rm -rf *.o app
