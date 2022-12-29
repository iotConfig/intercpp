CC=g++
CFLAGS= -g -Wall -W -I include/ -DLINUX
LFLAGS= -L/usr/X11R6/lib -lXm -lXt -lX11
SRCDIR=src
INCDIR=include
BINDIR=bin
VPATH=src:bin

all: FileTest Production RegularExpr TokenizeTest

FileTest: FileTest/FileTest.cpp 
	$(CC) $(CFLAGS) -c $< -o $@/$@	
Production: Production/Production.cpp 
	$(CC) $(CFLAGS) -c $< -o $@/$@	