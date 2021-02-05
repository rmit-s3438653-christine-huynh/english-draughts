/* model.cpp (Paul Miller 2017) * Modified by S3438653 Christine Huynh 2017 */ 

#include "model.h" 
#include <map>
#include <string>
#include <random>
#include <fstream>

std::unique_ptr<draughts::model::model> draughts::model::model::instance =
nullptr;

draughts::model::model::model(void) {
}

bool draughts::model::model::player_exists(const std::string& player_name) {
    for (std::map<int,std::shared_ptr<player>>::iterator it = player_map.begin(); it != player_map.end(); ++it) {
        if(player_name == it->second->get_name()) {
            return true;
        }
    } 
    return false;
}

/* starts a game where the two players in the game are represented by their ids.
 * prompting for the selection of the two players and then passing those ids 
 * into this function
 * you will need to call other functions to create the data structures and do 
 * the basic setup for a game
 */
void draughts::model::model::start_game(int plr1, int plr2) {
    game_board = std::unique_ptr<board>(new board);
    move_pos = std::unique_ptr<board>(new board);
    player1 = get_player(plr1);
    player1->set_token('x');
    player1->set_direction(1);
    player2 = get_player(plr2);
    player2->set_token('o');
    player2->set_direction(-1);
    curr_player = player1; 
    opp_player = player2;
    std::cout << "Player " << curr_player->get_name() << " is using token: "<< curr_player->get_token() << std::endl;
}

/* gets the token stored at the coordinates passed in. 
 * view calls this and then renders it in front end 
 */
char draughts::model::model::get_token(int row, int col) {
    return this->game_board->get_token(row,col); 
}

char draughts::model::model::get_board_tile(int row, int col) {
    return this->move_pos->get_board_tile(row,col);
}

/* represents an attempt to make a move. 
 * You will need to validate that the move is legal and then apply the move to 
 * the board. 
 */
void draughts::model::model::make_move(int player_id,
    int start_row, int start_col, int end_row, int end_col) {
        if (get_winner() != -1) {
            std::cout << get_player_name(get_winner()) << " has won the game"<< std::endl;
            exit(1);
        }
        
        try {
            if (validate_move(start_row, start_col, end_row, end_col) == false) {
                return;
            }
        }
        catch(const std::exception& e) {
            std::cout << e.what() << std::endl;
            return;  
        }

        switch_turn();

        if (curr_player == player1) {
            std::cout << "Player " << curr_player->get_name() << " is using token: x" << std::endl;            
        }
        else {
            std::cout << "Player " << curr_player->get_name() << " is using token: o" << std::endl;
        }
}

bool draughts::model::model::validate_move(int start_row, int start_col, int end_row, int end_col) {
    char token_at_location = get_token(start_row, start_col);
    char end_pos = get_token(end_row, end_col);
    char valid_pos = get_board_tile(end_row, end_col);

        // if selected start position is has no token
        if ((token_at_location == EOF) || (token_at_location == ' ')) {
            // no token at start_row, start_col
            throw missing_token(std::to_string(start_row) + "," + std::to_string(start_col) + " does not exist");
            return false;
        }
        // if end row is outside boundaries
        if (end_row > get_width() || end_row < 0 ) {
            // row outside boundaries
            throw out_of_bounds(std::to_string(end_row) + "is not within board width dimensions (1-8)");
            return false;
        }
        // if end col is outside boundaries
        if (end_col > get_height() || end_col < 0 ) {
            // col outside boundaries
            throw out_of_bounds(std::to_string(end_col) + "is not within board height dimension (1-8)");
            return false;
        }

        if (token_at_location != curr_player->get_token() && token_at_location != curr_player->get_token_up()) {
            throw incorrect_token(std::to_string(start_row) + "," + std::to_string(start_col) + " belongs to opponent");
            return false;
        }
        if ((end_pos != EOF) && (end_pos != ' ')) {
            // end co-ord contains a token
            throw blocked_token(std::to_string(end_row) + "," + std::to_string(end_col) + " contains a token");
            return false;
        }
        if (valid_pos == 'T') {
            if (end_row == start_row - (1*curr_player->get_direction())) { // moving backward
                // king move backward
                if (is_king(token_at_location) == true) {
                    game_board->move_token(start_row, start_col, end_row, end_col);
                    std::cout << "Player " << curr_player->get_name() << " is now at " << end_row << "," << end_col << std::endl;
                    return true;
                }
                throw invalid_move("Normal token cannot move backwards");
                return false;
            }
            // normal move, downward
            if ((end_row == start_row + (1 * curr_player->get_direction())) && (end_col == start_col + 1 || end_col == start_col - 1)) {
                game_board->move_token(start_row, start_col, end_row, end_col);
                std::cout << "Player " << curr_player->get_name() << " is now at " << end_row << "," << end_col << std::endl;
                // create king if end_row = 8
                game_board->make_king(curr_player->get_token(), end_row, end_col);
                return true;
            }
            // normal jump over opponent token, downward
            if ((end_row == start_row + (2*curr_player->get_direction())) && (end_col == start_col + 2 || end_col == start_col - 2)) {
                validate_jump(token_at_location, start_row, start_col, end_row, end_col);
                // create king if end_row = 8
                game_board->make_king(curr_player->get_token(), end_row, end_col);
                return true;
            }
            // king jump, backward (upward)
            if ((end_row == start_row - (2*curr_player->get_direction())) && (end_col == start_col + 2 || end_col == start_col - 2)) {
                if (is_king(token_at_location) == true) {
                    validate_jump(token_at_location, start_row, start_col, end_row, end_col);
                    return true;
                }
                throw invalid_move("Normal token cannot move backwards");
                return false;
            }
        }
        else {
            throw invalid_input("Unknown input");
            return false;
        }
    return false;
}

/* validates the jump is possible to capture opponent token
*/
void draughts::model::model::validate_jump(char player_token, int start_row, int start_col, int end_row ,int end_col) {
    char token_at_location = get_token(start_row, start_col);
    int mid_row = start_row + (end_row-start_row)/2;
    int mid_col = start_col + (end_col-start_col)/2;
    char mid_token = get_token(mid_row, mid_col);

    try {
        if (mid_token == opp_player->get_token() || mid_token == opp_player->get_token_up()) {
            capture_token(player_token, start_row, start_col, end_row, end_col, mid_row, mid_col); // modify
            if (is_king(token_at_location) == true) {
                conseq_king_jump(player_token, end_row, end_col, mid_token); 
                }
                conseq_jump(player_token, end_row, end_col);
        }
        else {
            return;
        } 
    }
    catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return;
}

/* check for a potential conseq jump */
void draughts::model::model::conseq_jump(char player_token, int row, int col) {
    int temp_end_row;
    int temp_end_col_l;
    int temp_end_col_r;
    char left_token;
    char right_token;
    char choice;
    bool retry = true;

    temp_end_row = row + (2 * curr_player->get_direction());
    temp_end_col_l = col - 2;
    temp_end_col_r = col + 2;
    
    int mid_row = row + (temp_end_row - row)/2;
    int mid_col_l = col + (temp_end_col_l - col)/2;
    int mid_col_r = col + (temp_end_col_r - col)/2;
    
    // check if end_pos is on board
    if ((temp_end_row > 0) && (temp_end_row <= get_width() )) {
        if ((temp_end_col_l > 0) && (temp_end_col_l <= get_width() )) {
            left_token = get_token(mid_row, mid_col_l);
        }
        if ((temp_end_col_r > 0) && (temp_end_col_r <= get_width() )) {
            right_token = get_token(mid_row, mid_col_r);
        }
    }

    // if the jump can be made
    if ( (get_token(temp_end_row, temp_end_col_l) == ' ') && (get_token(temp_end_row, temp_end_col_r) == ' ') ) {
        if ((left_token == opp_player->get_token() || left_token == opp_player->get_token_up()) && (right_token == opp_player->get_token() || right_token==opp_player->get_token_up())) {
            // choice of 2 jumps
            std::cout << "Player " << curr_player->get_name() << " can capture token on the left or right" << std::endl;
            while (retry == true) {
                std::cout << "Enter <L> to capture token on the Left : " << mid_row << "," << mid_col_l << std::endl;
                std::cout << "   or <R> to capture token on the Right: " << mid_row << "," << mid_col_r << std::endl;
                try {
                    std::cin >> choice;
                    if (tolower(choice) == 'l') {
                        // left
                        capture_token(player_token, row, col, temp_end_row, temp_end_col_l, mid_row, mid_col_l);
                        if (is_king(player_token) == true) {
                            conseq_king_jump(player_token, temp_end_row, temp_end_col_l, opp_player->get_token()); // modify
                        }
                        conseq_jump(player_token, temp_end_row, temp_end_col_l);
                        retry = false;
                    }
                    else if (tolower(choice) == 'r') {
                        // right
                        capture_token(player_token, row, col, temp_end_row, temp_end_col_r, mid_row, mid_col_r);
                        if (is_king(player_token) == true) {
                            conseq_king_jump(player_token, temp_end_row, temp_end_col_r, opp_player->get_token()); // modify
                        }
                        conseq_jump(player_token, temp_end_row, temp_end_col_r);
                        retry = false;
                    }
                    else {
                        throw invalid_input("Unknown input");
                    }
                } // end try
                catch(const std::exception& e) {
                    std::cout << e.what() << std::endl;
                }
            } // end retry

        } // end if 
    } // end if
    if (get_token(temp_end_row, temp_end_col_l) == ' ') {
        // opponent token can be captured on the left
        if ((left_token == opp_player->get_token() || left_token == opp_player->get_token_up()) && right_token == ' ') {
            capture_token(player_token, row, col, temp_end_row, temp_end_col_l, mid_row, mid_col_l);
            if (is_king(player_token) == true) {
                conseq_king_jump(player_token, temp_end_row, temp_end_col_l, opp_player->get_token()); // modify
            }
            conseq_jump(player_token, temp_end_row, temp_end_col_l);
        }
    } // end if
    else if (get_token(temp_end_row, temp_end_col_r) == ' ') {
        // opponent token can be captured on the right
        if (left_token == ' ' && (right_token==opp_player->get_token() || right_token==opp_player->get_token_up())) {
            capture_token(player_token, row, col, temp_end_row, temp_end_col_r, mid_row, mid_col_r);
            if (is_king(player_token) == true) {
                conseq_king_jump(player_token, temp_end_row, temp_end_col_r, opp_player->get_token()); // modify
            }
            conseq_jump(player_token, temp_end_row, temp_end_col_r);
        }
    }
    else {
        // no legal jumps
        std::cout << "no more legal jump" << std::endl;
        return;
    }
    return;
}

void draughts::model::model::conseq_king_jump(char player_token, int row, int col, char opponent) {
    int temp_end_row_front;
    int temp_end_col_left;
    int temp_end_col_right;
    int temp_end_row_back;
    int left_token_front;
    int right_token_front;
    int left_token_back;
    int right_token_back;
    char choice;
    bool retry = true;

    temp_end_row_front = row + 2;
    temp_end_col_left = col - 2;
    temp_end_col_right = col + 2;
    temp_end_row_back = row - 2;

    // check end_pos is on board
    if ((temp_end_row_front > 0) && (temp_end_row_front <= get_height() )) {
        if ((temp_end_row_back > 0) && (temp_end_row_back <= get_height() )) {
            if ((temp_end_col_left > 0) && (temp_end_col_left <= get_width() )) {
                left_token_front = get_token(temp_end_row_front - 1, temp_end_col_left + 1);
                left_token_back = get_token(temp_end_row_back + 1, temp_end_col_left + 1);
            }
            if ((temp_end_col_right > 0) && (temp_end_col_right <= get_width() )) {
                right_token_front = get_token(temp_end_row_front - 1, temp_end_col_right - 1);
                right_token_back = get_token(temp_end_row_back + 1, temp_end_col_right - 1);
            }
        }
    }
    // check for potential tokens to jump
        if ((left_token_back == opponent || left_token_back == to_upcase(opponent)) ||
            (right_token_back  == opponent || right_token_back == to_upcase(opponent)) ||
            (left_token_front  == opponent || left_token_front == to_upcase(opponent)) ||
            (right_token_front  == opponent || right_token_front == to_upcase(opponent)) ) {
            
            std::cout << "Player " << curr_player->get_name() << " can capture one or more tokens" << std::endl;
            while (retry == true) {
                if ( get_token(temp_end_row_back, temp_end_col_left) == ' ') {
                    if (left_token_back == opponent || left_token_back == to_upcase(opponent)) {
                        std::cout << "Player " << curr_player->get_name() << " can capture token on the Back-Left" << std::endl;
                        std::cout << "Enter <Y> to capture token on the Back-Left : " << temp_end_row_back + 1 << "," << temp_end_col_left + 1 << std::endl;
                        std::cout << "   or <N> to capture a different token: " << std::endl;
                        try {
                            std::cin >> choice;
                            if (tolower(choice) == 'y') { // back-left
                                capture_token(player_token, row, col, temp_end_row_back, temp_end_col_left, temp_end_row_back + 1, temp_end_col_left + 1);
                                conseq_king_jump(player_token, temp_end_row_back, temp_end_col_left, opponent);
                                retry = false;
                            }
                            else {
                                std::cout << "Player skipped capture" << std::endl;
                            }
                        }
                        catch(const std::exception& e) {
                            std::cout << e.what() << std::endl;
                            return;
                        }
                        
                    }
                }
                if ( get_token(temp_end_row_back, temp_end_col_right) == ' ') { 
                    if (right_token_back==opponent || right_token_back==toupper(opponent)) {
                        std::cout << "Player " << curr_player->get_name() << " can capture token on the Back-Right" << std::endl;
                        std::cout << "Enter <Y> to capture token on the Back-Right : " << temp_end_row_back + 1 << "," << temp_end_col_right - 1 << std::endl;
                        std::cout << "   or <N> to capture a different token: " << std::endl;

                        try {
                            std::cin >> choice;
                            if (tolower(choice)=='y') {
                                // back-right
                                capture_token(player_token, row, col, temp_end_row_back, temp_end_col_right, temp_end_row_back + 1, temp_end_col_right - 1);
                                conseq_king_jump(player_token, temp_end_row_back, temp_end_col_right, opponent);
                                retry=false;
                            }
                            else {
                                std::cout << "Player skipped capture" << std::endl;
                            }
                        }
                        catch(const std::exception& e) {
                            std::cout << e.what() << std::endl;
                            return;
                        }
                    }
                }
                if ( get_token(temp_end_row_front, temp_end_col_left) == ' ') {
                    if (left_token_front  == opponent || left_token_front == to_upcase(opponent)) {
                        std::cout << "Player " << curr_player->get_name() << " can capture token on the Front-Left" << std::endl;
                        std::cout << "Enter <Y> to capture token on the Front-Left : " << temp_end_row_front - 1 << "," << temp_end_col_left + 1 << std::endl;
                        std::cout << "   or <N> to capture a different token: " << std::endl;
                        try {
                            std::cin >> choice;
                            if (tolower(choice) == 'y') { // back-right
                                capture_token(player_token, row, col, temp_end_row_front, temp_end_col_left, temp_end_row_front - 1, temp_end_col_left + 1);
                                conseq_king_jump(player_token, temp_end_row_front, temp_end_col_left, opponent);
                                retry = false;
                            }
                            else {
                                std::cout << "Player skipped capture" << std::endl;
                            }
                        }
                        catch(const std::exception& e) {
                            std::cout << e.what() << std::endl;
                            return;
                        }
                    }
                }
                if ( get_token(temp_end_row_front, temp_end_col_right) == ' ') {
                    if (right_token_front  == opponent || right_token_front == to_upcase(opponent)) {
                        std::cout << "Player " << curr_player->get_name() << " can capture token on the Front-Right" << std::endl;
                        std::cout << "Enter <Y> to capture token on the Front-Right : " << temp_end_row_front - 1 << "," << temp_end_col_right - 1 << std::endl;
                        std::cout << "   or <N> to capture a different token: " << std::endl;

                        try {
                            std::cin >> choice;
                            if (tolower(choice) == 'y') { // back-right
                                capture_token(player_token, row, col, temp_end_row_front, temp_end_col_right, temp_end_row_front - 1, temp_end_col_right - 1);
                                conseq_king_jump(player_token, temp_end_row_front, temp_end_col_right, opponent);
                                retry = false;
                            }
                            else {
                                std::cout << "Player skipped capture" << std::endl;
                            }
                        }
                        catch(const std::exception& e) {
                            std::cout << e.what() << std::endl;
                            return;
                        }
                    }
                }
            }// end retry
        } // end if found tokens to capture
        
    return;
}

/* capture token */
void draughts::model::model::capture_token(char player_token, int start_row, int start_col, int end_row, int end_col, int del_row, int del_col) {
    std::cout << "Player " << curr_player->get_name() << " is capturing a token"<< std::endl;
    std::cout << "Press <enter> to continue: " << std::endl;
    std::cin.get();

        game_board->delete_token(del_row, del_col);
        std::cout << "Opponent token "<<opp_player->get_token()<<" at " << del_row << "," << del_col << " has been removed from the board"<< std::endl;
        game_board->move_token(start_row, start_col, end_row, end_col);
        // create king if end_row = 8
        game_board->make_king(player_token, end_row, end_col);
    
    std::cout << "Player " << curr_player->get_name() << " is now at " << end_row << "," << end_col << std::endl;
    return;
}

/* switch turn to next player */
void draughts::model::model::switch_turn() {
    if (curr_player == player1) {
        curr_player = player2;
        opp_player = player1;
    }
    else {
        curr_player = player1;
        opp_player = player2;
    }
}

/* adds a player with the specified name to the system. 
 * generating unique ids for each player (an int) and 
 * checking that the player exists in the system.
 * If any validation fails you should be throwing exceptions. 
 */
void draughts::model::model::add_player(const std::string& player_name) {
    int uid;
    std::map<int, std::shared_ptr<player>>::iterator it;
    
    if (player_exists(player_name) == true) {
        // player exists.
        std::cout << "Player " << player_name << " already exists. Use a different name." << std::endl;
        return;
    }

    // generate a random id number from 1-9999
    std::random_device rd;
    std::mt19937 mt(rd() );
    std::uniform_int_distribution<int> dis(1,9999);
    uid = dis(mt);

    it = player_map.find(uid);
    while (it != player_map.end() ) {
        // uid not unique
        uid = dis(mt);
        it = player_map.find(uid);
    }


    // add new id and player to map 
    player_map[uid] = std::shared_ptr<player>(new player (uid, player_name));
    player_list[uid] = player_name;
    std::cout << "Player ID for " << player_name << " is " << uid << std::endl;
    std::cout << "Successfully added " << player_name << " to the player roster"
    << std::endl;
}

char draughts::model::model::to_upcase(char token) {
    return (char)toupper(token);
}

// checks if token is king
bool draughts::model::model::is_king(char player_token) {
    if (player_token == curr_player->get_token_up()) {
        return true;
    }
    return false;
}

/* gets the player score for the player with the player id passed in. 
 */
int draughts::model::model::get_player_score(int player_id) {
    char player_token;
    int count;
    int score = 12;
    
    if (player_id == player1->get_id()) {
        player_token = 'x';
        count = game_board->get_token_count(player_token);
    }
    else {
        player_token = 'o';
        count = game_board->get_token_count(player_token);
    }
    return score -= count;
    //return score;
}

/* gets the id for the player whose turn it currently is. 
 */
int draughts::model::model::get_current_player(void) {
    return curr_player->get_id();
}

std::string draughts::model::model::get_player_name(int player_id) {
    return player_list[player_id];
}

std::shared_ptr<draughts::model::player> draughts::model::model::get_player(int player_id) {
    return player_map.find(player_id)->second;
}

std::map<int, std::string> draughts::model::model::get_player_list(void) const{
    return player_list;
}

/* gets the player id of the player that has won the game. 
 * It should return -1 if the game is still in progress.
 */
int draughts::model::model::get_winner() {
    int count_x;
    int count_o;

    count_x = get_player_score(1);
    count_o = get_player_score(2);

    if (count_x == 12) {
        return player2->get_id();
    }
    else if (count_o == 12) {
        return player1->get_id();
    }
    else {
        return EOF;
    }   
}

/* gets the width of the board
 */
int draughts::model::model::get_width() {
    int width = 8;
    return width;
}

/* gets the height of the board
 */
int draughts::model::model::get_height() {
    int height = 8;
    return height;
}

draughts::model::model * draughts::model::model::get_instance(void) {
    if(instance == nullptr) {
        instance = std::unique_ptr<model>(new model);	
    }
    return instance.get();
}

void draughts::model::model::delete_instance(void) {
    instance.reset(nullptr);
}

draughts::model::model::~model(void) {
}