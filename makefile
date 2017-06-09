#
#  Makefile
#  naijagame
#
#  Created by Olusegun Ojewale 20-03-2017.
#
# Determine the platform

UNAME_S := $(shell uname -s)

# CC
ifeq ($(UNAME_S),Darwin)
  CC := clang++ -arch x86_64
else
  CC := g++
endif


CFLAGS=-I.
LIBS=-lGL -lGLU -lGLEW -lglut -lglfw 


#Directories
SRCDIR := src
TARGETDIR := bin


#Builds
EXEC := naijagame
AI_FILE := user.kw
TARGET := $(TARGETDIR)/$(EXEC)


$(EXEC) : $(SRCDIR)/*.cpp $(SRCDIR)/*.h $(TARGET) $(SRCDIR)/$(AI_FILE) 
	$(CC)  -o $(TARGET) $(SRCDIR)/*.cpp $(SRCDIR)/*.h $(LIBS)  

$(TARGET): 
	@echo "creating target directory ."
	@mkdir -p $(TARGETDIR); cp $(SRCDIR)/$(AI_FILE) $(TARGETDIR)

launch : $(EXEC) 
	./$(TARGET)

clean :
	@echo "removing bin directory."
	rm -fr $(TARGETDIR)

.PHONY: clean
