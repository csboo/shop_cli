#pragma once
#include <string>
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
        Quit = 4
    };
    input() = default;
    void get();
    inline auto reset(){this->state = States::Default;this->opt = '0';this->arrow_state = Arrows::None;}
    inline auto get_state(){return this->state;}
    inline void set_state(States state){this->state = state;}
    inline auto value(){return this->opt;}
    inline void set_value(char val){this->opt = val;}
    inline auto get_arrow_state(){return this->arrow_state;}
private:  
    Arrows is_arrow(char &x);

    char opt = '\0';
    States state;
    Arrows arrow_state;
};

void print_msg(std::string text, std::pair<unsigned, unsigned> coords = {2, 1}, bool save_cursor = true);
void clear_msg();
void printmenu(std::vector<std::string> &menu, int invert = 0);
std::vector<std::string> init_menu(std::vector<std::string> &v);
std::string read_rsp(std::string &rsp);

