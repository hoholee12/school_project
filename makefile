CC=x86_64-w64-mingw32-gcc
CFLAGS=-static -Wall
test95:
	$(CC) $(CFLAGS) test95.c -lmingw32 -I/usr/local/include/SDL -lSDLmain -lSDL