all:  build

CC        := g++
SOURCES   := $(wildcard *cpp)
INCLUDEH  := $(wildcard *hpp) 
INCLUDET  := $(wildcard *tpp)
MOCS      := command.hpp 
MOC_FILES := $(patsubst %.hpp, moc_%.cpp, $(MOCS))


OBJECTS   := $(patsubst %.cpp, ../../obj/%.o, $(SOURCES))
#OBJECTS   += $(patsubst moc_%.cpp, ../../obj/moc_%.o, $(MOC_FILES))
LIBRARIES := 
LIB_NAME  := $(notdir $(LIBRARIES))
L_NAME    := $(patsubst lib%.so, -l%, $(LIB_NAME))
L_NAME    += `pkg-config --libs Qt5Widgets Qt5Core Qt5Gui`
INCLUDE_H := $(patsubst %.hpp, ../../inc/%.hpp, $(INCLUDEH))
INCLUDE_T := $(patsubst %.tpp, ../../inc/%.tpp, $(INCLUDET))
INC       := -I../../inc
INC       += `pkg-config --cflags Qt5Widgets Qt5Core Qt5Gui`
LINKDIR   := $(shell bash -c 'pkg-config --variable libdir Qt5Widgets')
#LINKDIR   += ../../lib
LINK      := $(foreach link, $(LINKDIR), $(shell echo -L$(link)))
DEPENDS   := $(patsubst %.cpp, ../../obj/%.dep,$(SOURCES))
CFLAGS    := -c -g -Wall -Wextra -pedantic -std=c++11 -fPIC


ifeq ($(MAKECMDGOALS),)
	    -include $(DEPENDS)
else ifeq ($(MAKECMDGOALS),all)
	    -include $(DEPENDS)
endif

.PRESIOUS : $(MOC_FILES)

default :
	@echo $(DEPENDS)
	@echo $(LIBRARIES)

../../obj/%.dep : ./%.cpp $(MOC_FILES)
	$(CC) $(INC) $(CFLAGS) -MM  $< -MT "$@ $(patsubst %.dep,%.o,$@)" -o $@

moc_%.cpp : %.hpp
	@echo "MOC"
	moc $(INC) $< -o $@

$(OBJECTS) :
	$(CC) $(CFLAGS) $(INC) $< -o $@ 
	
.PRECIOUS : $(INCLUDE_H) $(INCLUDE_T)

build : ../../lib/libcommand.so

../../lib/libcommand.so : $(INCLUDE_H) $(INCLUDE_T) $(OBJECTS) 
	$(CC) -shared $(LINK) $(OBJECTS) -o $@ $(L_NAME)
	#mv ./moc_* ../../obj/

../../inc/%hpp : ./%hpp 
	ln -f $< $@

../../%tpp : ./%tpp 
	ln -f $< $@
