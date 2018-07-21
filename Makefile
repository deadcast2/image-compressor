CC = x86_64-w64-mingw32-gcc -Werror -Wno-attributes
CFLAGS = -std=c99 -O2 -Ilodepng
LDFLAGS = -mconsole -g
LDLIBS = -lkernel32

image-compressor.exe: main.c
	$(CC) $(LDFLAGS) $(CFLAGS) fastlz.c libimagequant/*.c main.c -o $@ $(LDLIBS)

clean:
	rm -f *.exe *.o
