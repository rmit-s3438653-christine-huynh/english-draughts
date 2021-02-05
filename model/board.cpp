/* board.cpp (S3438653 Christine Huynh 2017)
 */

#include "board.h"

draughts::model::board::board(void) {
    width = 8;
    height = 8;

   
    for(int h = 1; h <= this->height; h++) {
        for(int w = 1; w <= this->width; w++) {
            if(h == 1) {
                if (w % 2 == 0) {
                    token_map[h][w] = std::shared_ptr<token>(new token('x'));
                }
                else {
                    token_map[h][w] = std::shared_ptr<token>(new token(' '));
                }
            }
            else if (h == 2) {
                if (w % 2 == 0) {
                    token_map[h][w] = std::shared_ptr<token>(new token(' '));
                }
                else {
                    token_map[h][w] = std::shared_ptr<token>(new token('x'));
                }
            }
            else if (h == 3) {
                if (w % 2 == 0) {
                    token_map[h][w] = std::shared_ptr<token>(new token('x'));
                }
                else {
                    token_map[h][w] = std::shared_ptr<token>(new token(' '));
                }
            }
            else if (h == 4) {
                token_map[h][w] = std::shared_ptr<token>(new token(' '));
            }
            else if (h == 5) {
                token_map[h][w] = std::shared_ptr<token>(new token(' '));
            }
            else if (h == 6) {
                if (w % 2 == 0) {
                    token_map[h][w] = std::shared_ptr<token>(new token(' '));
                }
                else {
                    token_map[h][w] = std::shared_ptr<token>(new token('o'));
                }
            }
            else if (h == 7) {
                if (w % 2 == 0) {
                    token_map[h][w] = std::shared_ptr<token>(new token('o'));
                }
                else {
                    token_map[h][w] = std::shared_ptr<token>(new token(' '));
                }
            }
            else if (h == 8) {
                if (w % 2 == 0) {
                    token_map[h][w] = std::shared_ptr<token>(new token(' '));
                }
                else {
                    token_map[h][w] = std::shared_ptr<token>(new token('o'));
                }
            }
        }
    }


    move_map = {
        {1, {{1, ' '}, {2, 'T'}, {3, ' '}, {4, 'T'}, {5, ' '}, {6, 'T'}, {7, ' '}, {8, 'T'}} },
        {2, {{1, 'T'}, {2, ' '}, {3, 'T'}, {4, ' '}, {5, 'T'}, {6, ' '}, {7, 'T'}, {8, ' '}} },
        {3, {{1, ' '}, {2, 'T'}, {3, ' '}, {4, 'T'}, {5, ' '}, {6, 'T'}, {7, ' '}, {8, 'T'}} },
        {4, {{1, 'T'}, {2, ' '}, {3, 'T'}, {4, ' '}, {5, 'T'}, {6, ' '}, {7, 'T'}, {8, ' '}} },
        {5, {{1, ' '}, {2, 'T'}, {3, ' '}, {4, 'T'}, {5, ' '}, {6, 'T'}, {7, ' '}, {8, 'T'}} },
        {6, {{1, 'T'}, {2, ' '}, {3, 'T'}, {4, ' '}, {5, 'T'}, {6, ' '}, {7, 'T'}, {8, ' '}} },
        {7, {{1, ' '}, {2, 'T'}, {3, ' '}, {4, 'T'}, {5, ' '}, {6, 'T'}, {7, ' '}, {8, 'T'}} },
        {8, {{1, 'T'}, {2, ' '}, {3, 'T'}, {4, ' '}, {5, 'T'}, {6, ' '}, {7, 'T'}, {8, ' '}} },
    };
}

/* gets the token stored at the coordinates passed in. 
 * view calls this and then renders it in front end 
 */
char draughts::model::board::get_token(int x ,int y) {

    // https://stackoverflow.com/questions/35969534/c-iterate-over-map-of-maps
    for(auto &outer_key : this->token_map) {
        for(auto &inner_key : outer_key.second) {

          if ((outer_key.first == x) && (inner_key.first == y)) {
              return inner_key.second->get_token();
          }
        }
    }
    return EOF;
}

char draughts::model::board::get_board_tile(int x ,int y) {
    for(auto &outer_key : this->move_map) {
        for(auto &inner_key : outer_key.second) {

          if ((outer_key.first == x) && (inner_key.first == y)) {
              return inner_key.second;
          }
        }
      }
      return EOF;
}

// modify to include case insensitive
int draughts::model::board::get_token_count(char player_token) {
    int count;
    for(auto &outer_key : this->token_map) {
        for(auto &inner_key : outer_key.second) {

            if (tolower(inner_key.second->get_token()) == player_token) {
                ++count;
            }
        }
    }
    return count;
}

/* gets the width of the board
 */
int draughts::model::board::get_width() {
    return this->width;
}

/* gets the height of the board
 */
int draughts::model::board::get_height() {
    return this->height;
}

void draughts::model::board::delete_token(int row, int col) {
    --*token_map[row][col];
}

void draughts::model::board::make_king(char player_token, int row, int col) {
    if (player_token == 'x') {
        if (row == get_width()) {
            ++*token_map[row][col];
        }
    }
    else if(player_token == 'o') {
        if (row == 1) {
            ++*token_map[row][col];
        }
    }
}

/* edits token_map
*/
void draughts::model::board::move_token(int start_row, int start_col, int end_row, int end_col) {
    token_map[end_row][end_col]->set_token(token_map[start_row][start_col]->get_token());
    --*token_map[start_row][start_col];
}