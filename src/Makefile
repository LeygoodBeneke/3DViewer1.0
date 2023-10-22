CC = gcc
CFLAGS = -Werror -Wextra -Wall -std=c11 -pedantic
SOURCES = 
LIBRARY = 
OBJ_PROJECT = 
TESTS =
UNAME = $(shell uname -s)

ifeq ($(UNAME), Linux)
	LDFLAGS = -lcheck -lm -lrt -lpthread -lsubunit
	OPEN_CM = xdg-open
endif
ifeq ($(UNAME), Darwin)
	LDFLAGS = -lcheck -lm
	OPEN_CM = open
endif

.PHONY: all dvi dist

all: clean install

install: $(LIBRARY)
	mkdir build
	qmake -o build
	make -C build

uninstall: 
	rm -rf build

test:

add_coverage:
	$(eval CFLAGS += --coverage)

gcov_report: add_coverage test
	gcov -b -l -p -c s21_*.gcno
	gcovr -o gcov_report.html --html --html-details -g -k -r . --html --html-details
	$(OPEN_CM) gcov_report.html

clean:
	rm -rf build
	rm -rf *.a *.o *.out *.info *.html *.gcno *.gcov *.gcda *.gch *.tgz *.css .clang_format

dvi: 
	$(OPEN_CM) dvi/dvi.html

dist: clean
	mkdir dist_3d_viewer/
	cp Makefile *.txt *.c *.h *.cpp *.ui dist_3d_viewer/
	tar -czvf s21_smartcalc.tgz dist_3d_viewer/
	rm -rf dist_3d_viewer/

valgrind: test
	valgrind --tool=memcheck --leak-check=yes --leak-check=full -s ./s21_tests

style:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h
	rm -rf .clang-format

edit_style:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h
	rm -rf .clang-format