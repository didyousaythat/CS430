CC = gcc
CFLAGS = -Wall
RM = rm -f

all: ppmrw

ppmConverter: ppmrw.c ppmrw.h
	$(CC) $(CFLAGS) ppmrw.c ppmrw.h -o ppmrw

clean:
	$(RM) ppmrw *~s
