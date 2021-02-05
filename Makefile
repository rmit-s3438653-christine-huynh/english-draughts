# Makefile
# S3438653 Christine Huynh 2017
OBJS = main_noncurses.o ui.o controller.o model.o player.o board.o command.o window.o player_selection_window.o menu.o main_menu.o game_window.o add_player_window.o
CC = g++
CXXFLAGS = -Wall -pedantic -std=c++14

a2 : $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o a2

main_noncurses.o : main_noncurses.cpp ncview/ui.h nc_controller/controller.h model/model.h
	$(CC) $(CXXFLAGS) -c main_noncurses.cpp

ui.o : ncview/ui.h ncview/ui.cpp nc_controller/controller.h model/model.h
	$(CC) $(CXXFLAGS) -c ncview/ui.cpp

controller.o : nc_controller/controller.h nc_controller/controller.cpp model/model.h
	$(CC) $(CXXFLAGS) -c nc_controller/controller.cpp

model.o : model/model.h model/model.cpp model/player.h model/board.h model/my_exception.h
	$(CC) $(CXXFLAGS) -c model/model.cpp

player.o : model/player.h model/player.cpp
	$(CC) $(CXXFLAGS) -c model/player.cpp

board.o : model/board.h model/board.cpp model/token.h
	$(CC) $(CXXFLAGS) -c model/board.cpp

command.o : nc_controller/command.h nc_controller/command.cpp ncview/ui.h
	$(CC) $(CXXFLAGS) -c nc_controller/command.cpp

window.o : ncview/window.h ncview/ui.h model/model.h nc_controller/command.h
	$(CC) $(CXXFLAGS) -c ncview/window.cpp

player_selection_window.o : ncview/player_selection_window.h ncview/player_selection_window.cpp nc_controller/controller.h
	$(CC) $(CXXFLAGS) -c ncview/player_selection_window.cpp

menu.o : ncview/menu.h ncview/menu.cpp nc_controller/command.h
	$(CC) $(CXXFLAGS) -c ncview/menu.cpp

main_menu.o : ncview/main_menu.h ncview/main_menu.cpp nc_controller/command.h nc_controller/controller.h 
	$(CC) $(CXXFLAGS) -c ncview/main_menu.cpp

game_window.o : ncview/game_window.h ncview/game_window.cpp model/model.h
	$(CC) $(CXXFLAGS) -c ncview/game_window.cpp

add_player_window.o : ncview/add_player_window.h ncview/add_player_window.cpp ncview/ui.h model/model.h nc_controller/command.h 
	$(CC) $(CXXFLAGS) -c ncview/add_player_window.cpp

clean:
	\rm *.o *~ a2
