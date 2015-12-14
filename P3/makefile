comp: parser.o scanner.o main.o
	g++ parser.o scanner.o main.o -o comp

scanner.o: scanner.cpp
	g++ -c scanner.cpp

parser.o: parser.cpp
	g++ -c parser.cpp

main.o: main.cpp
	g++ -c main.cpp

codeGen.o: codeGen.cpp
	g++ -c codeGen.cpp

clean:
	rm -rf *.o comp
