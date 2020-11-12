CC = g++
FLAGS = -Wall -O3

TARGET = factorials
LIB = lib
TARGETED = $(LIB)/$(TARGET).o

all: $(TARGET).o
	$(CC) -o $(TARGETED) $(FLAGS) $(TARGET).cpp
	./$(TARGETED)
