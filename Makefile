CC=gcc
CFLAGS=-Wall -O3

INSTALL=/usr/bin/install -c
UNINSTALL=rm -f

PREFIX=/usr
EXEC_PREFIX=${PREFIX}
BINDIR=${EXEC_PREFIX}/bin
DATADIR=${PREFIX}/share


all: nixie.c
	        $(CC)  $(CFLAGS) `pkg-config --libs --cflags gtk+-2.0` -o nixie nixie.c

clean:
	        /bin/rm -f *.o *~

install: nixie
	test -d $(DESTDIR)$(BINDIR) || mkdir -p $(DESTDIR)$(BINDIR)
	test -d $(DESTDIR)$(DATADIR)/nixie-clock || mkdir -p $(DESTDIR)$(DATADIR)/nixie-clock
	$(INSTALL) -m 644 ./*.gif $(DESTDIR)$(DATADIR)/nixie-clock
	$(INSTALL) -m 755 nixie $(DESTDIR)$(BINDIR)
uninstall:
	$(UNINSTALL) $(DESTDIR)$(BINDIR)/nixie
	$(UNINSTALL) $(DESTDIR)$(DATADIR)/nixie-clock
