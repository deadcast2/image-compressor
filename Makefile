CC = x86_64-w64-mingw32-gcc -Werror -Wno-attributes
CFLAGS = -std=c99 -O2 -Ilodepng -Ilibimagequant
LDFLAGS = -mconsole -g
LDLIBS = -lkernel32

image-compressor.exe: main.c
	$(CC) $(LDFLAGS) $(CFLAGS) libimagequant/*.c lodepng/*.c \
	main.c -o $@ $(LDLIBS)

clean:
	rm -f *.exe *.o
