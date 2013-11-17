APP=tests

all:
	gcc -Wall -std=c99 -pedantic -g -o $(APP) *.c ../src/*.c -I../src -lm -lpng -fopenmp
debug:
	gcc -Wall -std=c99 -pedantic -g -o $(APP) *.c ../src/*.c -I../src -lm -lpng -fopenmp
clean:
	rm -f ${APP}
