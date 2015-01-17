CC=gcc
# from pkg-config --cflags libgphoto2
CFLAGS=-I/usr/include/gphoto2 -I/usr/include/libexif
# from pkg-config --libs libgphoto2
LFLAGS=-lgphoto2 -lgphoto2_port -lm -lexif
SRC=camera.cpp

all:
	$(CC) -o camera $(SRC) $(CFLAGS) $(LFLAGS)

.PHONY: clean

clean:
	rm -f camera
