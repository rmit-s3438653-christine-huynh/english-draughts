-CPT 323 - Assignment 2 - Software Design and Implementation--------------------
Create a game prototype of the game Draughts using modern C++. The design of the
game is implemented in MVC pattern to communicate between components to reduce
coupling. The game is based on the game rules of Draughts.

-Getting Started----------------------------------------------------------------
Source files included in this submission are:
	direction.h	main_noncurses.cpp		Makefile

	model:		board.cpp			board.h
			my_exception.h
			model.cpp			model.h
			player.cpp			player.h
			token.h

	nc_controller:	command.cpp			command.h
			controller.cpp			controller.h

	ncview:		add_player_window.cpp		add_player_window.h
			game_window.cpp			game_window.h
			main_menu.cpp			main_menu.h
			menu.cpp			menu.h
			player_selection_window.cpp
			player_selection_window.h
			ui.cpp				ui.h
			window.cpp			window.h
				
-Prerequisites------------------------------------------------------------------
This can be run on RMIT core teaching servers (jupiter, saturn)

-Installing---------------------------------------------------------------------
1. Ensure all source files for the Draughts game are within their correct 
   folders as above. Where direction.h, main_noncurses.cpp and Makefile is outside
   these folders.
2. Compile the program using 'make'. This will call on Makefile to compile all
   the source files.
3. Run the program by issuing the following command in console:
   ./a2

-Running the program------------------------------------------------------------
1. After issuing the command to run, console should print the game menu:

		English Draughts
		----------------
		1) Add Player to the system
		2) Play Game
		3) Exit Game
		Please enter your choice:

2. Adding a player:
   Before the game can be played, players need to be created. Enter 1 into the
   console and press <enter> on the keyboard:

		Please enter the name for the new player:

3. Enter the name of the player into the console and press <enter> on the
   keyboard.
4. If the player name entered is unique and has not yet been registered before
   then a Player ID is created for that player:

		Player ID for <playername> is 0000
		Successfully added <playername> to the player roster
		Press <enter> to continue:

5. At least two players need to be pre-registered before a game can be played.
6. Playing the game:
   After registering two or more players into the system, option '2) Play Game'
   can be selected from the menu.

		Please enter your choice: 2
		Select a Player to add to the game
		----------------------------------
		1) <playername1>
		2) <playername2>
		Please enter your choice:

7. Enter the corresponding number next to the player name to be added to the
   game, only two players can be selected to play. The corresponding number 
   next to the player name will change after one player has been selected.

		You have selected the following player(s) to play the game:
		<playername1>
		Select a Player to add to the game
		----------------------------------
		1) <playername2>
		Please enter your choice:

8. After two players have been selected to play the game, the game begins.
   Players going first are selected at random to start the game.

   		Player <playername1> is using token: x
		  1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
		--------------------------------
		1   | x |   | x |   | x |   | x |
		--------------------------------
		2 x |   | x |   | x |   | x |   |
		--------------------------------
		3   | x |   | x |   | x |   | x |
		--------------------------------
		4   |   |   |   |   |   |   |   |
		--------------------------------
		5   |   |   |   |   |   |   |   |
		--------------------------------
		6 o |   | o |   | o |   | o |   |
		--------------------------------
		7   | o |   | o |   | o |   | o |
		--------------------------------
		8 o |   | o |   | o |   | o |   |
		It is <playername1>'s turn and their score is 0
		Please enter your move: (row,col-row,col):

9. The first player enters the co-ordinates of the token that they wish to move:
   the row separated by ',' and the column. Followed by a '-'then the 
   co-ordinates of the final position they like to move their token to: the row 
   separated by ',' and then the column.

		Please enter your move: (row,col-row,col): 3,2-4,3

10.The board updates the position of the player token, and the turn switches
   to the next player.

		Player <playername1> is now at 4,3
		Player <playername2> is using token: o
		  1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
		--------------------------------
		1   | x |   | x |   | x |   | x |
		--------------------------------
		2 x |   | x |   | x |   | x |   |
		--------------------------------
		3   |   |   | x |   | x |   | x |
		--------------------------------
		4   |   | x |   |   |   |   |   |
		--------------------------------
		5   |   |   |   |   |   |   |   |
		--------------------------------
		6 o |   | o |   | o |   | o |   |
		--------------------------------
		7   | o |   | o |   | o |   | o |
		--------------------------------
		8 o |   | o |   | o |   | o |   |
		It is <playername2>'s turn and their score is 0
		Please enter your move: (row,col-row,col):

11.Capturing a token:
   If a player decides to capture a neighbouring token that belongs to an 
   opponent. The player enters the co-ordinates of the token that they wish to 
   move followed by '-' then the  co-ordinates of the final position they like 
   to move their token to. Which in this case the empty cell diagonal to the 
   token they wish to capture. This is also the player's tokens final position.
		
		Player <playername2> is using token: o
		  1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
		--------------------------------
		1   | x |   | x |   | x |   | x |
		--------------------------------
		2 x |   | x |   | x |   | x |   |
		--------------------------------
		3   |   |   | x |   | x |   | x |
		--------------------------------
		4   |   | x |   |   |   |   |   |
		--------------------------------
		5   |   |   | o |   |   |   |   |
		--------------------------------
		6 o |   | o |   |   |   | o |   |
		--------------------------------
		7   | o |   | o |   | o |   | o |
		--------------------------------
		8 o |   | o |   | o |   | o |   |
		It is <playername2>'s turn and their score is 0
		Please enter your move: (row,col-row,col): 5,4-3,2
		Player <playername2> is capturing a token
		Press <enter> to continue

12.After pressing <enter> on the keyboard, the opponent token is removed from 
   the board. Player score increases by 1, and the token is moved to the new
   position.
		Opponent token x at 4,3 has been removed from the board
		Player <playername2> is now at 3,2
		no more legal jump

13.Consecutive captures:
   If a player token has successfully captured an opponent token and is in the
   position to capture another token. The system will prompt the player to 
   press <enter> to do a consecutive jump.

   		Player <playername1> is using token: x
		  1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
		--------------------------------
		1   | x |   | x |   | x |   | x |
		--------------------------------
		2   |   |   |   |   |   |   |   |
		--------------------------------
		3   |   |   | x |   |   |   |   |
		--------------------------------
		4   |   |   |   | o |   |   |   |
		--------------------------------
		5   |   |   |   |   |   |   |   |
		--------------------------------
		6   |   |   |   | o |   |   |   |
		--------------------------------
		7   |   |   |   |   |   |   |   |
		--------------------------------
		8 o |   | o |   | o |   | o |   |
		It is <playername1>'s turn and their score is 6
		Please enter your move: (row,col-row,col): 3,4-5,6
		Player <playername1> is capturing a token
		Press <enter> to continue
		Opponent token o at 4,5 has been removed from the board
		Player <playername1> is now at 5,6
		Player <playername1> is capturing a token
		Press <enter> to continue
		Opponent token o at 6,5 has been removed from the board
		Player <playername1> is now at 7,4
		no more legal jump

14.Consecutive captures with a option:
   If a player token has successfully captured an opponent token and is in the
   position to capture one or more tokens. The system will prompt the player to 
   press <enter> to do a consecutive jump.

		Player <playername2> can capture token on the left or right
		Enter <L> to capture token on the left : 3,4
		   or <R> to capture token on the Right: 3,6
		r
		Player <playername2> is capturing a token
		Press <enter> to continue
		Opponent token x at 3,6 has been removed from the board
		Player <playername1> is now at 2,7
		no more legal jump

15.Winning the game:
   When a player score reaches 12, the system announces the winner and the game
   ends.
		<playername1> has won the game

16.Exiting the game:
   At the menu, enter 3 into the console and press <enter> on the keyboard. The
   system is exited.
   

-Built With---------------------------------------------------------------------
N/A

-Authors------------------------------------------------------------------------
Christine Huynh (s3438653)

-Acknowledgments----------------------------------------------------------------
Paul Miller - source material a2_startup.zip (.cpp, .h)
Xiangmin Zhou - references COSC1252-1254 -- Lectures
Various authors - stackoverflow.com
Unknown authors - http://en.cppreference.com
Unknown authors - www.cplusplus.com
Unknown authors - https://www.tutorialspoint.com