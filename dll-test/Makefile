## VARIABLES

CXX=g++
CXXFLAGS=-O3 -std=c++17 -Wall
LDFLAGS=-static -shared

DIRSRC = src
DIROBJ = obj
DIRBIN = bin
DIRDEP = dep

PROGRAM=dll-test
LDLIBS=

## LOGICA

#detectamos el sistema operativo
ifeq ($(OS),Windows_NT)
    OS_NAME := Windows
else
    OS_NAME := $(shell uname)
endif

$(info OS_NAME = $(OS_NAME))

#definimos la s condiciones de compilacion dependiendo del sistema operativo
ifeq ($(OS_NAME),Windows)
PROGRAM:=$(addsuffix .dll,$(PROGRAM))
define MKDIR_OS
	-mkdir $(subst /,\,$(1))
endef
define RM_OS
	del /Q /S $(subst /,\,$(1))
endef
else
$(error Sistema operativo no valido)
endif

FILE_BIN=$(DIRBIN)/$(PROGRAM)

$(info LDLIBS = $(LDLIBS))
$(info FILE_BIN = $(FILE_BIN))

#listamos los archivos de codigo
SRCS = $(wildcard $(DIRSRC)/*.cpp $(DIRSRC)/*/*.cpp)
$(info SRCS sin prorizar = $(SRCS))

#optenemos los objetos
OBJS = $(SRCS:$(DIRSRC)/%.cpp=$(DIROBJ)/%.o)
$(info OBJS = $(OBJS))

#optenemos las dependencias
DEPS = $(SRCS:$(DIRSRC)/%.cpp=$(DIRDEP)/%.d)
$(info DEPS = $(DEPS))

## TARGETS

#targets que no son archivos
.PHONY: all clean

#inicio del make
all: $(FILE_BIN)

#archivos a linkar
$(FILE_BIN): $(OBJS)
	$(CXX) $^ -o $@ $(LDLIBS) $(LDFLAGS)

#incluimos las dependencias
-include $(DEPS)

#patron de objetos a compilar
$(DIROBJ)/%.o: $(DIRSRC)/%.cpp
#	creamos los subdirectorios y generamos los archivos de dependencias
	$(call MKDIR_OS,$(@D:$(DIROBJ)%=$(DIRDEP)%))
	$(CXX) -MM $< > $(@:$(DIROBJ)/%.o=$(DIRDEP)/%.d)
#	creamos los subdirectorios y compilamos los objetos
	$(call MKDIR_OS,$(@D))
	$(CXX) -o $@ -c $< $(CXXFLAGS) -I$(DIRSRC)

#limpiamos los archivos antiguos
clean:
	$(call RM_OS,$(DIROBJ) $(DIRDEP) $(FILE_BIN))
