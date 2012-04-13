# Drux Lord Makefile

CC         = gcc
SOURCES    = window.c window-cb.c druxlord.c main.c
OBJS       = ${SOURCES:.c=.o}
CFLAGS     = -Wall -fstack-protector -g -c `pkg-config --cflags gtk+-2.0`
LIBS       = `pkg-config --libs gtk+-2.0`
TARGET     = druxlord

${TARGET}: ${OBJS}
	${CC} ${LIBS} ${OBJS} -o ${TARGET}

.c.o:
	${CC} ${CFLAGS} $<

clean:
	rm -rf *.o ${TARGET}
