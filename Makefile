CC		= gcc
GPP		= g++

CFLAGS	= -g -Wall -pthread -std=c++11

# Library flagss to be loaded e.g. -L../lib
LDFLAGS =

# Libraries to be loaded. e.g. -lfile
LIBS =

INCLUDE	= -I./include
SRCDIR	= src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
# SOURCES += $(wildcard $(SRCDIR)/*.c)


OBJS		= $(SOURCES:.c = .o)

# Define the executable file
EXECFILE=headupdisp

all: $(EXECFILE)
	@echo Compiling headupdisp

# Command to make $(EXECFILE)
$(EXECFILE): $(OBJS)
	$(GPP) $(CFLAGS) $(INCLUDE)  -o $(EXECFILE) $(OBJS) $(LDFLAGS) $(LIBS)

#Command to Make Object File
.c.o:
	$(GPP) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
