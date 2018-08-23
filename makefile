CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = ls.h
OBJ = ls.o fe.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

fe: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

