/* board.h (S3438653 Christine Huynh 2017)
 */
#include "token.h"
#include <map>
#include <memory>

namespace draughts {
    namespace model {
        class board {
            int width;
            int height;
            std::map<int, std::map<int, std::shared_ptr<token>>> token_map;
            std::map<int, std::map<int, char>> move_map;

            public:
            board(void);
            char get_token(int,int);
            char get_board_tile(int,int);
            int get_token_count(char);
            int get_width();
            int get_height();
            void delete_token(int, int);
            void make_king(char, int, int);
            void move_token(int, int, int, int);
        };
    }
}