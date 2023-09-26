# Makefile: Makefile for project1

# design names
DESIGN = bin/PhotoLab bin/PhotoLabTest

#libs
LIBS   = src/libFilter.a src/libFileIO.a

CC     = gcc
DEBUG  = -DDEBUG -g
CFLAGS = -Wall -std=c11
LFLAGS = -Wall -lm
AR     = ar rc
RANLIB = ranlib

IMAGES = pic/bw.ppm \
         pic/negative.ppm \
         pic/colorfilter.ppm \
         pic/edge.ppm \
         pic/hflip.ppm \
         pic/shuffle.ppm \
         pic/hmirror.ppm \
         pic/border.ppm \
         pic/normalize.ppm \
         pic/rotate.ppm \
         pic/posterize.ppm \
         pic/blur.ppm \
	 pic/crop.ppm \
	 pic/brightnessandcontrast.ppm \
	 pic/bigresize.ppm \
	 pic/smallresize.ppm \
	 pic/watermark.ppm \

all: bin/PhotoLab bin/PhotoLabTest


########### generate object files ###########

#target to generate Image.o
src/Image.o: src/Image.c src/Image.h src/Constants.h
	$(CC) $(CFLAGS) -c src/Image.c -o src/Image.o

#target to generate Test.o
src/Test.o: src/Test.c src/Test.h src/FileIO.h src/DIPs.h src/Advanced.h src/Image.h src/Constants.h
	$(CC) $(CFLAGS) -c src/Test.c -o src/Test.o

#target to generate Test_DEBUG.o
src/Test_DEBUG.o: src/Test.c src/Test.h src/FileIO.h src/DIPs.h src/Advanced.h src/Constants.h
	$(CC) $(CFLAGS) $(DEBUG) -c src/Test.c -o src/Test_DEBUG.o

#target to generate FileIO.o
src/FileIO.o: src/FileIO.h src/FileIO.c src/Constants.h
	$(CC) $(CFLAGS) -c src/FileIO.c -o src/FileIO.o

#target to generate FileIO_DEBUG.o
src/FileIO_DEBUG.o: src/FileIO.h src/FileIO.c src/Constants.h
	$(CC) $(CFLAGS) $(DEBUG) -c src/FileIO.c -o src/FileIO_DEBUG.o

#target to generate DIPs.o
src/DIPs.o: src/DIPs.h src/DIPs.c src/Constants.h
	$(CC) $(CFLAGS) -c src/DIPs.c -o src/DIPs.o

#target to generate Advanced.o
src/Advanced.o: src/Advanced.h src/Advanced.c src/Constants.h
	$(CC) $(CFLAGS) -c src/Advanced.c -o src/Advanced.o

#target to generate PhotoLab.o
src/PhotoLab.o: src/PhotoLab.c src/DIPs.h src/Advanced.h src/FileIO.h src/Constants.h src/Image.h
	$(CC) $(CFLAGS) -c src/PhotoLab.c -o src/PhotoLab.o

#target to generate FileIO_DEBUG.o
src/PhotoLab_DEBUG.o: src/PhotoLab.c src/DIPs.h src/Advanced.h src/FileIO.h src/Constants.h src/Image.h
	$(CC) $(CFLAGS) $(DEBUG) -c src/PhotoLab.c -o src/PhotoLab_DEBUG.o

########### generate library files ###########

#target to generate libFilter.a
src/libFilter.a: src/DIPs.o src/Advanced.o
	$(AR) src/libFilter.a src/Advanced.o src/DIPs.o
	$(RANLIB) src/libFilter.a

########### generate executables ###########

#target to generate PhotoLab
bin/PhotoLab: src/PhotoLab.o src/FileIO.o src/Image.o src/Test.o src/libFilter.a
	$(CC) $(LFLAGS) src/PhotoLab.o src/FileIO.o src/Image.o src/Test.o -Lsrc -lFilter -o bin/PhotoLab

#target to generate test
bin/PhotoLabTest: src/PhotoLab_DEBUG.o src/FileIO_DEBUG.o src/Image.o src/Test_DEBUG.o src/libFilter.a
	$(CC) $(LFLAGS) src/PhotoLab_DEBUG.o src/FileIO_DEBUG.o src/Image.o src/Test_DEBUG.o -Lsrc -lFilter -o bin/PhotoLabTest
	
#target to clean the directory
clean:
	rm -f src/*.o pic/*.jpg $(DESIGN) $(IMAGES) $(LIBS)
