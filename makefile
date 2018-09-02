CC = g++
CFLAGS = -Wall -std=c++1z
DEPS = ls.h
OBJ = ls.o fe.o create.o copy.o remove.o snapshot.o main.o
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

