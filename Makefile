# ipp - 
# See LICENSE file for copyright and license details.

.POSIX:

# C compiler
CC = gcc

# C flags
CFLAGS = -std=c99 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -pedantic -O3
LDFLAGS =

# Target
PROG = ipp

# Sources and objects
SRCS = ipp.c
OBJS = ${SRCS:.c=.o}

all: ${PROG}

${PROG}: ${OBJS}
	${CC} ${LDFLAGS} -o ${PROG} ${OBJS}

.c.o:
	${CC} ${CFLAGS} -c $<

clean:
	rm -f ${PROG} ${OBJS}

install: all
	mkdir -p ${DESTDIR}/usr/local/bin
	cp -f ${PROG} ${DESTDIR}/usr/local/bin
	chmod 755 ${DESTDIR}/usr/local/bin/${PROG}

uninstall:
	rm -f ${DESTDIR}/usr/local/bin/${PROG}

.PHONY: all clean install uninstall
