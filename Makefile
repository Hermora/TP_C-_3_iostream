COMP=g++
EDL=g++
EXEC=main

CFLAGS=-Wall -ansi -pedantic -std=c++11
INT = Trajet.h TrajetSimple.h TrajetCompose.h Catalogue.h TestTrajet.h
REAL=$(INT:.h=.cpp)
OBJ=$(REAL:.cpp=.o)

.PHONY: clean

%.o: %.cpp
	$(COMP) $(CFLAGS) -c $< 

$(EXEC): $(OBJ)
	$(EDL) -o $(EXEC) $(OBJ)
	
clean:
	rm -f *.o $(EXEC)

