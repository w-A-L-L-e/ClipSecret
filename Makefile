CXX=g++

all: clips obfuscator

obfuscator: obfuscator.o
	$(CXX) -o obfuscator $^

secrets.h: obfuscator
	./obfuscator "1234" "hello world"

clips: secrets.h clips.o
	$(CXX) -o clips clips.cpp -lcurses

install: 
	./obfuscator
	$(CXX) -o clips clips.cpp -lcurses
	cp clips ~/bin/
	rm secrets.h

clean:
	@rm -rf *.o clips obfuscator secrets.h
