GENERATES = range *_out *.out

all: range

range: range.c
		cc -O0 -g $^ -o $@

test: range
		gdb --batch --quiet --command=script1_gdb --args ./range | grep '^@@@' | cut -c 4- > res1_out
		gdb --batch --quiet --command=script2_gdb --args ./range | grep '^@@@' | cut -c 4- > res2_out
		cmp res1_out test1_answer
		cmp res2_out test2_answer
clean:
		rm -rf $(GENERATES)