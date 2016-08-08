all: parser

parser: parser.o
	g++ parser.o -o parser

parser.o: parser.cpp
	g++ -c parser.cpp

run:
	./parser

clean:
	rm -f *.o parser
