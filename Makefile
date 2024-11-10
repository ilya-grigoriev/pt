.PHONY: all install clean uninstall

VERSION = 1.0

PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

all:
	cc -g *.c -lncurses -o pt 

install:
	cc -g *.c -lncurses -o pt 
	mkdir -p $(PREFIX)/bin
	cp -f pt $(PREFIX)/bin
	chmod 755 $(PREFIX)/bin/pt
	
	mkdir -p $(MANPREFIX)/man1
	sed "s/VERSION/$(VERSION)/g" < pt.1 > $(MANPREFIX)/man1/pt.1
	chmod 644 $(MANPREFIX)/man1/pt.1

clean:
	rm -rf pt

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/pt
	rm -f $(DESTDIR)$(MANPREFIX)/man1/pt.1
