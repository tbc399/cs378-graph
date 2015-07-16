FILES :=                              \
    .travis.yml                       \
    ../deque-tests/tbc399-TestDeque.c++ \
    ../deque-tests/tbc399-TestDeque.out \
    Deque.h                       \
    Deque.log                       \
    html                              \
    TestDeque.c++                   \
    TestDeque.out					\
	makefile

ifeq ($(CXX), clang++)
    COVFLAGS := --coverage
    GCOV     := gcov-4.6
else
    CXX      := g++-4.8
    COVFLAGS := -fprofile-arcs -ftest-coverage
    GCOV     := gcov-4.8
endif

CXXFLAGS := -pedantic -std=c++11 -Wall
LDFLAGS  := -lgtest -lgtest_main -pthread
VALGRIND := valgrind

all: TestDeque

check:
	@for i in $(FILES);                                         \
	do                                                          \
        [ -e $$i ] && echo "$$i found" || echo "$$i NOT FOUND"; \
    done

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunDeque
	rm -f RunDeque.out
	rm -f TestDeque
	rm -f TestDeque.out

config:
	git config -l

test: TestDeque.out

simple-test: TestDeque
	./TestDeque

deque-tests:
	git clone https://github.com/cs378-summer-2015/deque-tests.git

html: Doxyfile Deque.h RunDeque.c++ TestDeque.c++
	doxygen Doxyfile

Deque.log:
	git log > Deque.log

Doxyfile:
	doxygen -g

TestDeque: Deque.h TestDeque.c++
	$(CXX) $(COVFLAGS) $(CXXFLAGS) TestDeque.c++ -o TestDeque $(LDFLAGS)

TestDeque.out: TestDeque
	$(VALGRIND) ./TestDeque  >  TestDeque.out 2>&1
	$(GCOV) -b Deque.h     >> TestDeque.out
	$(GCOV) -b TestDeque.c++ >> TestDeque.out
	cat TestDeque.out