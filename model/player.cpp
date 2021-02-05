/* player.cpp (S3438653 Christine Huynh 2017)
 */

#include "player.h"
#include <string>

draughts::model::player::player(int pid, std::string name)
{
    this->pid = pid;
    this->name = name;
}

int draughts::model::player::get_id() {
    return pid;
}

void draughts::model::player::set_token(char token) {
    this->token = token;
}

char draughts::model::player::get_token() {
    return token;
}

char draughts::model::player::get_token_up() {
    return (char)toupper(token);
}

std::string draughts::model::player::get_name() {
    return name;
}

void draughts::model::player::set_direction(int direction) {
    this->direction = direction;
}

int draughts::model::player::get_direction() {
    return direction;
}


