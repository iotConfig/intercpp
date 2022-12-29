CC=g++
CFLAGS= -g -Wall -W -I include/ -DLINUX
LFLAGS= -L/usr/X11R6/lib -lXm -lXt -lX11
SRCDIR=src
INCDIR=include
BINDIR=bin
VPATH=src:bin
OBJLIST=Tokenizer.o File.o

all: Production.o File.o CharStream.o ExecutionRules.o ParsingExpressions.o ParsingOperators.o RegularEx.o Tokenizer.o Rules.o

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $(BINDIR)/$@

