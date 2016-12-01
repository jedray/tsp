

SRC=$(wildcard *.cpp)

all: main run

main: 
	g++ -g $(SRC) -o tsp
run: 
		./tsp < samples/tsp.in
clean:
		rm tsp
debug:
	valgrind ./tsp < samples/tsp.in 

