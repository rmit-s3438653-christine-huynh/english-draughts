/* add_player_window.cpp (Paul Miller 2017)
 * Modified by S3438653 Christine Huynh 2017
 */
#include "add_player_window.h"
#include "ui.h"
#include "../model/model.h"
#include "../nc_controller/command.h"

/* creates the view that allows us to add players to the system by name
 */
void draughts::ncview::add_player_window::activate(void)
{
    std::string name;
    bool success = false;
    std::string recv;

    while(!success){
        try {
            name = window::get_input(
               "Please enter the name for the new player"  
            );
            draughts::model::model * themodel = 
                draughts::model::model::get_instance();
            themodel->add_player(name);
            /*std::cout << "Successfully added " << name << " to the player roster."
            << std::endl;*/
            success = true;
        }
        catch(std::exception& ex)
        {
            std::cerr << ex.what() << std::endl;
            return;
        }
    }
    /*std::cout << "Successfully added " << name << " to the player roster."
        << std::endl;*/
    std::cout << "Press <enter> to continue: " << std::endl;
    std::cin.get();
    view->main_menu();
}
