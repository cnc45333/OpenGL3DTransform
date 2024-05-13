## taken from previous class makefiles

##Compiler
CC=g++
##Linker
LD=$(CC)
#Flags
CPPFLAGS = -Wall -g -DLINUX
LFLAGS = -lglut -L/usr/lib -Lusr/X11r6/lib -lXi -lXmu -lGL -lGLU -lm

TARGETS = $(PROGFILES:.cpp=)

PROGFILES = \
	main.cpp \
	$(NULL)

targets default: $(TARGETS)

$(PROGFILES:.cpp=):main.o
	$(CC) -o cg03 main.o ${LFLAGS}

depend :
	makedepend ${PROGFILES}
