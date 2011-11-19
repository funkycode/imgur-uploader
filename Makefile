CFLAGS += -std=gnu99 -Wall -Wwrite-strings -pthread
ENDIAN_CFLAGS=
PREFIX ?=/usr/local

VERSION := 0.0.1
TARBALL := n9imgur-$(VERSION).tar.gz
CURL_CFLAGS := `pkg-config libcurl --cflags`
CURL_LDFLAGS := `pkg-config libcurl --libs`
MINIXML_CFLAGS:=  `pkg-config --cflags jansson`
MINIXML_LDFLAGS:= `pkg-config --libs jansson`


ifndef VERBOSE
	QUIET_CC = @echo '    ' CC $@;
	QUIET_LINK = @echo '    ' LINK $@;
	QUIET_MKDIR = @echo '    ' MKDIR $@;
endif

ifdef BIG_ENDIAN
	ENDIAN_CFLAGS=-DWORDS_BIGENDIAN
endif

BINARY := bin/n9imgur
OBJECTS := src/upload.c 

all: $(BINARY)

install: $(BINARY)
	install -d $(DESTDIR)$(PREFIX)/bin
	install -m 755 $(BINARY) $(DESTDIR)$(PREFIX)/bin

$(BINARY): $(OBJECTS) bin
	$(QUIET_LINK)$(CC) $(LDFLAGS) $(CURL_LDFLAGS) $(MINIXML_LDFLAGS) $(OBJECTS) -o $@

%.o : %.c
	$(QUIET_CC)$(CC) $(CFLAGS) $(CURL_CFLAGS) $(MINIXML_CFLAGS) $(ENDIAN_CFLAGS) -o $@ -c $<

bin:
	$(QUIET_MKDIR)mkdir bin
dist:
	rm -rf $(TARBALL) n9imgur-$(VERSION)
	git archive --format=tar --prefix=n9imgur-$(VERSION)/ HEAD | tar -x
	git log > n9imgur-$(VERSION)/ChangeLog
	tar czvf $(TARBALL) n9imgur-$(VERSION)
	rm -rf n9imgur-$(VERSION)
clean:
	rm -rf bin
