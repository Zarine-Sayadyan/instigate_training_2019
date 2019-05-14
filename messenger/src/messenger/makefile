all:  ../../bin/messenger

CC        := g++
SOURCES   := $(wildcard *cpp)
INCLUDEH  := $(wildcard *hpp) 
INCLUDET  := $(wildcard *tpp)
MOCS      := messenger.hpp login_page.hpp main_page.hpp
MOC_FILES := $(patsubst %.hpp, moc_%.cpp, $(MOCS))


OBJECTS   := $(patsubst %.cpp, ../../obj/%.o, $(SOURCES))
#OBJECTS   += $(patsubst moc_%.cpp, ../../obj/moc_%.o, $(MOC_FILES))
LIBRARIES := ../../lib/libthreads.so ../../lib/libsocket.so
LIB_NAME  := $(notdir $(LIBRARIES))
L_NAME    := $(patsubst lib%.so, -l%, $(LIB_NAME))
L_NAME    += `pkg-config --libs Qt5Widgets Qt5Core Qt5Gui`
INCLUDE_H := $(patsubst %.hpp, ../../inc/%.hpp, $(INCLUDEH))
INCLUDE_T := $(patsubst %.tpp, ../../inc/%.tpp, $(INCLUDET))
INC       := -I../../inc
INC       += `pkg-config --cflags Qt5Widgets Qt5Core Qt5Gui`
LINKDIR   := $(shell bash -c 'pkg-config --variable libdir Qt5Widgets')
LINKDIR   += ../../lib
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
	@echo $(SOURCES)
	@echo $(LIB_H)
	@echo $(LIB_NAME)
	@echo $(LIBRARIES)
	@echo $(L_NAME)
	@echo $(INC)
	@echo $(OBJECTS)
	@echo $(MOC_FILES)
	@echo $(LINKDIR)
	@echo $(LINK)

../../obj/%.dep : %.cpp $(LIBRARIES) $(MOC_FILES) 
	@echo "DEP"
	$(CC) $(INC) -std=c++11 -fPIC -MM $< -MT "$@ $(patsubst %.dep,%.o,$@)" -o $@

moc_%.cpp : %.hpp
	@echo "MOC"
	moc $(INC) $< -o $@

$(OBJECTS) :
	@echo "OBJ"
	$(CC) $(CFLAGS) $(INC) $< -o $@ 

../../bin/messenger : $(INCLUDEH) $(INCLUDET) $(OBJECTS) 
	$(CC) -pthread $(LINK) $(OBJECTS) -o $@ $(L_NAME)
	mv ./moc_* ../../obj/

$(LIBRARIES) :
	$(MAKE) -C ../../threads
	$(MAKE) -C ../../ipc
	$(MAKE) -C ../../messenger_server

#../../inc/%hpp : ./%hpp 
#	ln -f $< $@

#../../%tpp : ./%tpp 
#	ln -f $< $@
