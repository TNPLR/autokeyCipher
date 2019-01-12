CC=gcc
CFLAGS=-O3 -Wall

.PHONY: all help install clean uninstall
help:
	@echo "AutokeyCipher"
	@echo "\"make all\" to compile all the files"
	@echo "\"make install\" to install autokeyCipher(ac)"
	@echo "\"make uninstall\" to remove autokeyCipher(ac)"
	@echo "\"make clean\" to clean all the object files"
all: ac
ac: main.c
	${CC} ${CFLAGS} $^ -o $@
clean:
	rm ./ac
install: ac
	install ./ac /usr/local/bin/
uninstall:
	rm -f /usr/local/bin/ac
