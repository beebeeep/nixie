CC=gcc
CFLAGS=-Wall -O3
all: nixie.c
	        $(CC)  $(CFLAGS) `pkg-config --libs --cflags gtk+-2.0` -o nixie nixie.c

clean:
	        /bin/rm -f *.o *~

install:
	mkdir -p /usr/share/games/nixie-clock
	cp ./*.gif /usr/share/games/nixie-clock
	cp ./nixie /usr/local/bin/nixie
	chmod a+x /usr/local/bin/nixie

