CC=gcc
DEPS=lalloc.h list.h
CFLAGS=-I../include/
ODIR=../lib
LIBS=-lpthread



all:
	$(info [ CREATING DIRECTORY ])
	$(shell mkdir -p $(ODIR))
	$(info [ COMPILING SHARED/DYNAMIC LIBRARY ])
	$(CC) -shared -o $(ODIR)/liblist.so $(LIBS) $(CFLAGS)  -fPIC   lalloc.c 
	$(CC) -shared -o $(ODIR)/liblalloc.so $(LIBS) $(CFLAGS)  -fPIC   lalloc.c 
	$(info [ CREATING OBJECT FILE ])
	$(CC) -c $(CFLAGS) -o $(ODIR)/list.o 	list.c
	$(CC) -c $(CFLAGS) -o $(ODIR)/lalloc.o 	lalloc.c
	$(info [ COMPILING STATIC LIBRARY ])
	ar rcs $(ODIR)/liblist.a  $(ODIR)/list.o 
	ar rcs $(ODIR)/liblalloc.a  $(ODIR)/lalloc.o
	$(info [ REMOVING  OBJECT FILE ])
	rm -rf $(ODIR)/list.o $(ODIR)/lalloc.o

clean:

	$(info [ REMOVING OBJECT FILE ])
	rm -rf $(ODIR)/list.o
	rm -rf $(ODIR)/lalloc.o
	$(info [ REMOVING SHARED/DYNAMIC LIBRARY ])
	rm -rf $(ODIR)/liblist.so
	rm -rf $(ODIR)/liblalloc.so
	$(info [ REMOVING STATIC LIBRARY ])
	rm -rf $(ODIR)/liblist.a
	rm -rf $(ODIR)/liblalloc.a
