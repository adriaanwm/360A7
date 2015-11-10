all: lab7
	
lab7: lab7.o
	g++ -o lab7 lab7.o 

lab7.o: lab7.cpp
	g++ -c lab7.cpp 

clean: 
	rm lab7.o lab7
