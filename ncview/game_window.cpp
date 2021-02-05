/* game_window.cpp (Paul Miller 2017)
 * Modified by S3438653 Christine Huynh 2017
 */
#include "game_window.h"
#include "../model/model.h"

draughts::ncview::game_window::game_window(const player_pair & theplayers) 
    : players(theplayers), quit(false)
{
}

void draughts::ncview::game_window::activate(void) 
{
    while(!quit)
    {
        int playernum = EOF;
        try
        {
            display_board();
            playernum = themodel->get_current_player(); // removed int 27/09
            std::cout << "It is " << themodel->get_player_name(playernum)
                << "'s turn and their score is " 
                << themodel->get_player_score(playernum) << std::endl;
        }
        catch(std::exception & ex)
        {
            std::cerr << ex.what() << std::endl;
            return;
        }
        try
        {
            std::pair<std::pair<int,int>,std::pair<int,int>> move_coords;
            move_coords = get_move_input();
            themodel->make_move(playernum, move_coords.first.first, 
                move_coords.first.second, move_coords.second.first,
                move_coords.second.second);
        }
        catch(std::exception& ex)
        {
            std::cerr << ex.what() << std::endl;
        }
    }
}

std::pair<std::pair<int,int>, std::pair<int,int>> 
    draughts::ncview::game_window::get_move_input(void)
{
    std::string input;
    std::pair<std::pair<int,int>,std::pair<int,int>> move;
    std::pair<int,int> start;
    std::pair<int,int> end;
    input = window::get_input("Please enter your next move: (row,col-row,col)");
    std::vector<std::string> moves;
    std::vector<std::string> coords;
    boost::split(moves, input, [](char ch){return ch == '-';});
    start = strtocoord(moves[0]);
    end = strtocoord(moves[1]);
    move = std::make_pair(start, end);
    return move;
}

void draughts::ncview::game_window::print_top_row(void)
{
    int xcount;
    std::cout << " ";
    for (xcount = 0; xcount < themodel->get_width(); ++xcount)
    {
        std::cout << " " << xcount + 1 << " |";
    }
    std::cout << std::endl;
}

std::pair<int,int> draughts::ncview::game_window::strtocoord(
    const std::string& input)
{
    int x, y;
    std::vector<std::string> parts;
    boost::split(parts, input, [](char ch){ return ch == ',';});
    x = stoi(parts[0]);
    y = stoi(parts[1]);
    return std::make_pair(x,y);
}

/* prints 1 | 2 | 3 | ..
 */
void draughts::ncview::game_window::print_row(int rownum)
{
    int xcount;
    std::cout << rownum + 1;
    for(xcount = 0; xcount < themodel->get_width(); ++xcount)
    {
        std::cout << " " << themodel->get_token(rownum + 1, xcount + 1)
            << " |";
    }
    std::cout << std::endl;
}

/* prints ------- ..
 */
void draughts::ncview::game_window::print_line(int numdashes)
{
    int count;
    for(count = 0; count < numdashes; ++count)
    {
        std::cout << '-';
    }
}

/* prints board to console
 */
void draughts::ncview::game_window::display_board(void)
{
    int ycount;

    print_top_row();
    print_line(themodel->get_width() * 4);
    std::cout << std::endl;

    for(ycount = 0; ycount < themodel->get_height(); ycount++)
    {
        print_row(ycount);
        print_line(themodel->get_width() * 4);
        std::cout << std::endl;
    }
}

