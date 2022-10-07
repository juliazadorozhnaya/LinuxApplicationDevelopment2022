GENERATES = prog prog-a prog-so liboutput_static.a liboutput.so *.log *.o
CFLAGS = -fPIC -Wall -Werror

all:	prog prog-a prog-so

prog:	const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	cc -L. prog.o -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc -L. prog.o -loutput -o $@

fun.o: fun.c outlib.h

liboutput_static.a:	const.o fun.o
	ar -rcs $@ $^

liboutput.so: const.o fun.o
	cc  -shared $^ -o $@

test: test1 test2 test3

test1: prog prog-a prog-so
	./prog > $@.log 2> /dev/null
	./prog-a > $@_a.log 2> /dev/null
	LD_LIBRARY_PATH=`pwd` ./prog-so	> $@_so.log 2> /dev/null
	cmp $@.log $@_a.log
	cmp $@.log $@_so.log
	@ echo TEST 1 COMPLETED 

test2: prog prog-a prog-so
	./prog a > $@.log 2> /dev/null
	./prog-a a > $@_a.log 2> /dev/null
	LD_LIBRARY_PATH=`pwd` ./prog-so	a > $@_so.log 2> /dev/null
	cmp $@.log $@_a.log 
	cmp $@.log $@_so.log
	@ echo TEST 2 COMPLETED

test3: prog prog-a prog-so
	./prog a b c > $@.log 2> /dev/null
	./prog-a a b c > $@_a.log 2> /dev/null
	LD_LIBRARY_PATH=`pwd` ./prog-so	a b c > $@_so.log 2> /dev/null
	cmp $@.log $@_a.log
	cmp $@.log $@_so.log
	@ echo TEST 3 COMPLETED

clean:
	rm -rf $(GENERATES)
