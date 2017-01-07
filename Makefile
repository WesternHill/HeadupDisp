CC		= gcc
#CC=  #CROSS COMPILATION
GXX		= g++
#GXX= #CROSS COMPILATION
CFLAGS	= -g -Wall
DEPS	= disp.hpp
LDFLAGS = 
INCLUDE	= -I./include 
SRCDIR	= ./src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJDIR  = ./obj
OBJ		= $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o))) 

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	-mkdir -p $(OBJDIR)
	$(GXX) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: headupdisp

headupdisp: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)
	
clean: 
	rm -f $(OBJ)