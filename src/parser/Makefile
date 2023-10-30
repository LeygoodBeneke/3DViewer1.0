OS=$(shell uname)
CC=gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra -pedantic
ifeq ($(OS), Darwin)
 CHECK= -lcheck -lpthread -lm
else
 CHECK= -lcheck -lpthread -lm -lsubunit
endif

SOURCE = parser.c
OBJECTS = $(SOURCE: .c=.o)
TESTS = $(wildcard tests/*.c)
HEADERS = $(wildcard *.h tests/*.h)

all: main

main: build test

build: $(SOURCE) $(HEADER)
	$(CC) $(CFLAGS) -c $(SOURCE)

test: build
	$(CC) $(CFLAGS) $(TESTS) $(SOURCE) $(CHECK) -o test `pkg-config --cflags --libs check`
	./test

rebuild: clean all

gcov_report: build
	$(CC) $(CFLAGS) --coverage $(SOURCE) $(TESTS) $(CHECK) -o ./test
	./test
	mkdir report
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
	rm -rf *.gcda *.gcno *.out

leaks: clean test
	$(CC) $(CFLAGS) $(SOURCE) main_for_valgrind.c
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./a.out

style:
	clang-format -style=google -n $(SOURCE) $(TESTS) $(HEADERS)

reformat_code:
	clang-format -style=google -i $(SOURCE) $(TESTS) $(HEADERS)

clean:
	rm -rf *.o *.gcda *.gcno *.a *.out *.info *.dSYM report test $(PROJECT)
