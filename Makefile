# ipp - 
# See LICENSE file for copyright and license details.

.POSIX:

# C compiler
CC = gcc

# C flags
CFLAGS = -std=c99 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -pedantic -O3
LDFLAGS = -lsqlite3

# Target
PROG = ipp

# Sources and objects
SRCS = ipp.c
OBJS = ${SRCS:.c=.o}

all: ${PROG}

${PROG}: ${OBJS}
	${CC} -o ${PROG} ${OBJS} ${LDFLAGS}

.c.o:
	${CC} ${CFLAGS} -c $<

clean:
	rm -f ${PROG} ${OBJS}

install: all
	mkdir -p ${DESTDIR}/usr/local/bin
	cp -f ${PROG} ${DESTDIR}/usr/local/bin
	chmod 755 ${DESTDIR}/usr/local/bin/${PROG}
	mkdir -p ${DESTDIR}/usr/local/share/man/man1
	cp -f ipp.1 ${DESTDIR}/usr/local/share/man/man1
	chmod 644 ${DESTDIR}/usr/local/share/man/man1/ipp.1

uninstall:
	rm -f ${DESTDIR}/usr/local/bin/${PROG}
	rm -f ${DESTDIR}/usr/local/share/man/man1/ipp.1

.PHONY: all clean install uninstall
