/* player.h (S3438653 Christine Huynh 2017)
 */
#include <string>

namespace draughts {
    namespace model {
        class player {
            int pid;
            char token;
            std::string name;
            int direction;

            public:
            player(int, std::string);
            int get_id();
            void set_token(char);
            char get_token();
            char get_token_up();
            std::string get_name();
            void set_direction(int);
            int get_direction();
        };
    }
}