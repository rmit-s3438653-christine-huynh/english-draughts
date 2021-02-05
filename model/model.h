/* model.h (Paul Miller 2017)
 * Modified by S3438653 Christine Huynh 2017
 */
#include "board.h"
#include "player.h"
#include "my_exception.h"
#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <sstream>
#include <map>
#include <thread>
#include <chrono>

#pragma once

namespace draughts
{
    namespace model
    {
        class model
        {
            static std::unique_ptr<model> instance;
            std::map<int, std::shared_ptr<player>> player_map;
            std::map<int, std::string> player_list;
            std::unique_ptr<board> game_board;
            std::unique_ptr<board> move_pos;
            std::shared_ptr<player> player1;
            std::shared_ptr<player> player2;
            std::shared_ptr<player> curr_player;
            std::shared_ptr<player> opp_player;

            model(void);
            bool player_exists(const std::string&);

            public:
            void start_game(int, int);
            char get_token(int,int);
            char get_board_tile(int,int);
            void make_move(int, int, int, int, int);

            bool validate_move(int, int, int, int);
            void validate_jump(char, int, int, int, int);
            void conseq_jump(char, int, int);
            void conseq_king_jump(char, int, int, char);
            void capture_token(char, int, int, int, int, int ,int);
            void switch_turn();
            void add_player(const std::string& );
            char to_upcase(char);
            bool is_king(char);
            int get_player_score(int);
            int get_current_player(void);
            std::string get_player_name(int);
            std::shared_ptr<draughts::model::player> get_player(int);
            std::map<int, std::string> get_player_list(void) const;
            int get_winner();
            int get_width();
            int get_height();
            static model * get_instance(void);
            static void delete_instance(void);
            virtual ~model(void);
        };
    }
}
