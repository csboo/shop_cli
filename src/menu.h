#pragma once
#include "../external/cpptui/tui.hpp"
#include "shop.h"
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

class input {
public:
    enum Arrows{
        None = 0,
        Up = 1, 
        Down = 2,
        Left = 3, 
        Right = 4,
        Ctrl =5
    };
    enum States{
        Default = 0,
        Arrow = 1,
        Enter = 2,
        Bad = 3,
        Esc = 4
    };
    input() = default;
    void get();
    inline void set(States state = States::Default, char val = '\0', Arrows arrow_state = Arrows::None){this->state = state;this->opt = val;this->arrow_state = arrow_state;}
    //getters/setter
    inline auto get_state(){return this->state;}
    inline void switch_state(States state){this->state = state;}
    inline auto value(){return this->opt;} //getter for this->value, but the name is more convinient this way
    inline void set_value(char val){this->opt = val;}
    inline auto get_arrow_state(){return this->arrow_state;}
    void set_arrow_state(Arrows arrow_state){this->arrow_state = arrow_state;}
private:  
    Arrows is_arrow(char &x);

    char opt = '\0';
    States state;
    Arrows arrow_state;
};

namespace case_handling{
    std::string make_prompt_string(tui::tui_string &msg, std::pair<unsigned, unsigned> start_coords);
    int make_prompt_int(tui::tui_string &msg, std::pair<unsigned, unsigned> start_coords = {tui::cursor::get_position().first, tui::cursor::get_position().second});
    std::string get_valid_name(shop &shop, tui::tui_string &msg, std::pair<unsigned, unsigned> start_coords);
    int get_valid_amount(shop &shop, std::string &product_name, tui::tui_string &msg, std::pair<unsigned, unsigned> start_coords);
};
struct mapper{
    input::States state = input::States::Bad;  
    char value = '\0';
    input::Arrows arrow_state = input::Arrows::None;
};
void print_msg(std::string text, std::pair<unsigned, unsigned> coords = {2, 1}, bool save_cursor = true);
void clear_msg();
void printmenu(std::vector<std::string> &menu, int invert = 0);
std::vector<std::string> init_menu(std::vector<std::string> &v);
std::string read_valid_char();
void custom_keys(input &in, std::unordered_map<char, mapper> keys);
