CC = gcc
CFLAGS = -Werror -Wextra -Wall -std=c11
SOURCES =
LIBRARY =
OBJ_PROJECT =
TESTS =
UNAME = $(shell uname -s)
SOURCES = $(wildcard *.c *.cpp)
HEADERS = $(wildcard *.h)

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
	cd parser; make test

add_coverage:
	$(eval CFLAGS += --coverage)

gcov_report: add_coverage test
#	gcov -b -l -p -c proj_*.gcno
#	gcovr -o gcov_report.html --html --html-details -g -k -r . --html --html-details
#	$(OPEN_CM) gcov_report.html
	cd parser; make gcov_report

clean:
	rm -rf build
	rm -rf *.a *.o *.out *.info *.html *.gcno *.gcov *.gcda *.gch *.tgz *.css .clang_format src
	cd parser; make clean

dvi:
	$(OPEN_CM) dvi/dvi.html

dist: clean
	mkdir dist_3d_viewer/
	cp Makefile $(SOURCES) $(HEADERS) -r parser/ QtGifImage/ dist_3d_viewer/
	tar -czvf proj_smartcalc.tgz ../src
	rm -rf dist_3d_viewer/

valgrind: test
	#valgrind --tool=memcheck --leak-check=yes --leak-check=full -s ./proj_tests
	cd parser; make leaks
style:
	find . -name "*.cpp" -or -name "*.h" -or -name "*.c" | xargs clang-format -n
	cd parser; make style

edit_style:
	find . -name "*.cpp" -or -name "*.h" -or -name "*.c" | xargs clang-format -i
	cd parser; make reformat_code
