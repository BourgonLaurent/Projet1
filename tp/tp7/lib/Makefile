# Team #4546
#
# Authors:
# 	- Mehdi Benouhoud
# 	- Laurent Bourgon
# 	- Ihsane Majdoubi
# 	- Catalina-Andrea Araya-Figueroa
#
# Date: March 1st, 2023

# Making PHONY targets
.PHONY: all build clean

# Library variables

# Library name
LIB=embedded1900

# ==== INCLUDE C++ SOURCES HERE ====
CPP-SOURCES=led.cpp
# ====

# Compiler options
COMPILER=avr-gcc
CPP-VERSION=c++14
MCU=atmega324pa

# Linker options
LINKER=avr-ar
LINKER-OPTIONS=crs
OBJECT-FILES=$(CPP-SOURCES:.cpp=.o)
LIBRARY-FILE=lib$(LIB).a

# File clean options
REMOVE=rm
REMOVE-FLAGS=-f
ARTIFACTS=$(OBJECT-FILES) $(LIBRARY-FILE)

all: build

build:
	@echo [$(LIB)] Compiling library...
	$(COMPILER) -I. -std=$(CPP-VERSION) -mmcu=$(MCU) -c $(CPP-SOURCES) 
	@echo [$(LIB)] Compiled .o files
	@echo [$(LIB)] Linking/archiving links...
	$(LINKER) $(LINKER-OPTIONS) $(LIBRARY-FILE) $(OBJECT-FILES)
	@echo [$(LIB)] Linked/archived links into $(LIBRARY-FILE)
clean:
	@echo [$(LIB)] Cleaning files...
	$(REMOVE) $(REMOVE-FLAGS) $(ARTIFACTS)
	@echo [$(LIB)] Cleaned files
