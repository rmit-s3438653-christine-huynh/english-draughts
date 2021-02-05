/* token.h (S3438653 Christine Huynh 2017)
 */
#include <cctype>

namespace draughts
{
    namespace model
    {
        class token
        {
            char my_char;
            public:
            token(char c){
                my_char = c;
            };

            void set_token(char c){
                my_char = c;
            }
            char get_token(){
                return my_char;
            }

            token& operator++() {
                this->my_char = (char) std::toupper(this->my_char);
                return *this;
            }
            token operator++(int) {
                token temp(*this);
                operator++();
                return temp;
            }

            token& operator--() {
                this->my_char = ' ';
                return *this;
            }
            token operator--(int) {
                token temp(*this);
                operator--();
                return temp;
            }
        };
    }
}