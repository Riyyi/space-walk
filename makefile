#------------------------------------------------------------------------------#

PROGRAM := "space-walk"
HEADERS := \
	board.h \
	boardwindow.h \
	gamestate.h \
	infowindow.h \
	inputoutput.h \
	maingame.h \
	mainmenu.h \
	messagebox.h \
	player.h \
	selectionbox.h \
	spaceship.h \
	test.h \
	window.h
SOURCES := \
	board.cpp \
	boardwindow.cpp \
	infowindow.cpp \
	inputoutput.cpp \
	main.cpp \
	maingame.cpp \
	mainmenu.cpp \
	messagebox.cpp \
	player.cpp \
	selectionbox.cpp \
	spaceship.cpp \
	test.cpp \
	window.cpp

#------------------------------------------------------------------------------#

CXX         := g++
CXXFLAGS    := -lncurses -std=c++11 -Wall -Wextra

.PHONY: all debug run clean

all: run

debug: CXXFLAGS += -g -DDEBUG
debug: run

run: compile
	@./$(PROGRAM) ; \
		stty sane

compile: ${HEADERS} ${SOURCES}
	$(CXX) $(CXXFLAGS) $? -o $(PROGRAM)

clean:
	@-echo "Cleaning project.." ; \
		rm -f $(PROGRAM)
