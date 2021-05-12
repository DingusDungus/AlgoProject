INCLUDE_DIRS= include
INC_PARAMS=$(foreach d, $(INCLUDE_DIRS), -I$d)
APP_NAME=algo.app
FLAGS=-Wall -Werror -o $(APP_NAME) $(INC_PARAMS)
MEM_FLAGS=-Wall -Werror -fsanitize=address -fno-omit-frame-pointer -o $(APP_NAME) $(INC_PARAMS)

APP_SRC=main.cpp
SRC:=$(shell find src -name '*.cpp')

all: main

app:
	clang++ $(APP_SRC) $(SRC) $(FLAGS)

main:
	clang++ $(APP_SRC) $(SRC) $(FLAGS) && ./$(APP_NAME)

memcheck:
	clang++ $(APP_SRC) $(SRC) $(MEM_FLAGS) && ./$(APP_NAME)

valgrind:
	clang++ $(APP_SRC) $(SRC) $(FLAGS) && valgrind --leak-check=full ./$(APP_NAME)

clean:
	rm $(APP_NAME)
