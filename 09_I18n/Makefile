CFLAGS = -Wall -std=c99
LDFLAGS = -lm

PROG = guess_number

.PHONY: all clean

all: $(PROG) mo

$(PROG): $(PROG).c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(PROG).pot: $(PROG).c
	xgettext --keyword=_ --language=C --output po/$(PROG).pot $(PROG).c

$(PROG).po: $(PROG).pot
	msginit -i po/$(PROG).pot -l ru_RU.UTF-8 -o po/$(PROG).po

mo: $(PROG).po
	mkdir -p ./ru_RU.utf8/LC_MESSAGES
	msgfmt --check --verbose --output-file=ru_RU.utf8/LC_MESSAGES/$(PROG).mo $<

clean:
	@rm -f $(PROG)
	@rm -r ru_RU.utf8/r