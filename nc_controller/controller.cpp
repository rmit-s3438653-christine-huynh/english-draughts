/* controller.cpp (Paul Miller 2017)
 * Modified by S3438653 Christine Huynh 2017
 */
#include "controller.h"
#include "../ncview/ui.h"
#include "../model/model.h"

std::unique_ptr<draughts::nc_controller::controller>
draughts::nc_controller::controller::instance=nullptr;

draughts::nc_controller::controller::controller(void) 
{}

draughts::model::model * draughts::nc_controller::controller::get_model(
    void)
{
    return model::model::get_instance();
}

draughts::ncview::ui * draughts::nc_controller::controller::get_view(void)
{
    return ncview::ui::get_instance();
}

    draughts::nc_controller::controller*
draughts::nc_controller::controller::get_instance(void)
{
    if(instance == nullptr)
    {
        instance = std::unique_ptr<controller>(new controller);
    }
    return instance.get();
}

    std::vector<std::unique_ptr<draughts::nc_controller::command>>
draughts::nc_controller::controller::get_main_menu_commands(void)
{
    std::vector<std::unique_ptr<command>> main_menu_commands;
    // command for registering a player
    main_menu_commands.emplace_back(std::make_unique<addplayer_command>());
    // command that starts a new game with the selection of which registered 
    // players will be part of the game
    main_menu_commands.emplace_back(std::make_unique<newgame_command>());
    // command that quits the game
    main_menu_commands.emplace_back(std::make_unique<exit_command>());
    return std::move(main_menu_commands);
}

void draughts::nc_controller::controller::delete_instance(void)
{
    instance.reset(nullptr);
}

void draughts::nc_controller::controller::start_game(
    std::map<int, std::string> players)
{
    std::vector<int> ids;
    using player = std::pair<int, std::string>;
    player player1, player2;
    std::pair<player, player> theplayers; 
    int count = 0;
    for(auto & pair : players)
    {
        count++;
        ids.push_back(pair.first);
        if(count == 1)
        {
            player1 = pair;
        }
        else
        {
            player2 = pair;
        }
    }
    theplayers = std::make_pair(player1, player2);
    get_model()->start_game(ids[0], ids[1]);
    get_view()->show_game_window(theplayers);
}

draughts::nc_controller::controller::~controller(void)
{}
