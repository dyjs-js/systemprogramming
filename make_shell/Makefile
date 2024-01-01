CC=gcc -g
LIBS= -lstdc++

jssh : command_utility.o run.o tokenize.o main.o
	gcc -o jssh command_utility.o run.o tokenize.o main.o

command_utility.o : command_utility.c
	gcc -c -o command_utility.o command_utility.c

run.o : run.c
	gcc -c -o run.o run.c

tokenize.o : tokenize.c
	gcc -c -o tokenize.o tokenize.c

main.o : main.c
	gcc -c -o main.o main.c

clean :
	rm *.o jssh