CC = g++
FLAGS = -Wall -O3

HEADER = timer.h
TARGET = factorials
LIB = lib
TARGETED = $(LIB)/$(TARGET)

all: $(TARGET)
	@mkdir -p $(LIB)
	@$(CC) -o $(TARGETED) $(FLAGS) $(TARGET).cpp
	@./$(TARGETED)
	@rm $(TARGET)
