proj5.x: proj5.o passserver.o
	g++ -lcrypt -o proj5.x proj5.o passserver.o
proj5.o: proj5.cpp passserver.h
	g++ -c proj5.cpp
passserver.o: passserver.cpp passserver.h
	g++  -c  passserver.cpp
clean:
	rm *.o proj5.x
