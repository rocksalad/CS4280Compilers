testScanner: parser.o scanner.o main.o
	g++ parser.o scanner.o main.o -o testScanner

scanner.o: scanner.cpp
	g++ -c scanner.cpp

parser.o: parser.cpp
	g++ -c parser.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -rf *.o testScanner
