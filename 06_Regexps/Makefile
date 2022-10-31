CFLAGS = -Wall -Werror
GENERATES = esub sed_res esub_res

all: esub.c
	cc $^ CFLAGS -o esub

test: esub
	echo 'string' | sed -E 's/regexp/substitution/' > sed_res
	./esub 'regexp' 'substitution' 'string' > esub_res
	diff sed_res esub_res

	echo 'string' | sed -E 's/(r)(.*)(g)/\\\3->\2<-g\\\1 \0/' > sed_res
	./esub '(r)(.*)(g)' '\\\3->\2<-g\\\1 \0' 'string' > esub_res
	diff sed_res esub_res

	echo '15 16 17 18 19 20 21' | sed -E 's/(1.*7.*(8.*2))/\2-\1=/' > sed_res
	./esub '(1.*7.*(8.*2))' '\2-\1=' '15 16 17 18 19 20 21' > esub_res
	diff sed_res esub_res

clean:
		rm -rf $(GENERATES)