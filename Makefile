###############################################################################
###               University of Hawaii, College of Engineering
###               Lab 2 - Catnap - SRE - Spring 2023
###
### Build and test a program that explores integers
###
### @see     https://www.gnu.org/software/make/manual/make.html
###
### @file    Makefile
### @author  Mark Nelson <marknels@hawaii.edu>
###############################################################################

TARGET = catnap


all:  $(TARGET)


CC     = gcc
CFLAGS = -Wall -Wextra $(DEBUG_FLAGS)


debug: DEBUG_FLAGS = -g -DDEBUG
debug: clean $(TARGET)


catnap.o: catnap.c
	$(CC) $(CFLAGS) -c catnap.c


catnap: catnap.o
	$(CC) $(CFLAGS) -o $(TARGET) catnap.o


test: $(TARGET)
	./$(TARGET)


clean:
	rm -f $(TARGET) *.o
