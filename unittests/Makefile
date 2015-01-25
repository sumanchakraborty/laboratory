APP=tests

all:
	gcc -Wall -std=c99 -pedantic -g -o $(APP) *.c ../src/*.c -I../src -lm -fopenmp
debug:
	gcc -Wall -std=c99 -pedantic -g -o $(APP) *.c ../src/*.c -I../src -lm -fopenmp
clean:
	rm -f ${APP}
