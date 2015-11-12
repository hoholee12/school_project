CC=x86_64-w64-mingw32-gcc
CFLAGS=-static -Wall -L /lib -Wno-missing-braces
LDFLAGS=-lglfw3 -lgdi32 -lopengl32
all:
	$(CC) $(CFLAGS) 3dproject.c $(LDFLAGS)