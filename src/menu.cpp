#include "menu.h"
#include "external/cpptui/tui.hpp"
#include <iostream>
#include <vector>

void printmenu(std::vector<std::string> &menu, int invert){
    std::cout << tui::tui_string("\n\r\n\r\n\r\tValasszon opciot:\n\r\n\r").bold();
    for (auto line = 0; line < menu.size(); line++) {
        if (line == invert){
            std::cout << tui::tui_string(menu[line]).inverted();
        } else {
            std::cout << menu[line];
        }
        
    }
}

Arrows as_arrow (char &x){
    if(x == 27 && std::cin.peek() == 91) {
        std::cin.ignore();
        auto arrow = std::cin.get();
        switch (arrow) {
        case 65:
            return Arrows::Up;
        case 66:
            return Arrows::Down;
        case 67:
            return Arrows::Right;
        case 68:
            return Arrows::Left;
        default:
            std::cin.get();
            std::cin.get();
            std::cin.ignore();
            return Arrows::None;
        }
    }
    return Arrows::None;
}

const char get_option(){
    char opt = '\0';
    const std::string options = "1234567";
    std::cin.get(opt);
    if (!options.find(opt) && as_arrow(opt) == Arrows::None && opt != '\n') {
        get_option();
    }
    return opt;
}
void print_msg(std::string text){
    tui::cursor::save();
    tui::cursor::set_position(2, 1);
    std::cout << '\t' << text; 
    tui::cursor::restore();
    
}
void clear_msg(){
    tui::cursor::save();
    tui::cursor::set_position(2, 1);
    tui::screen::clear_line();
    tui::cursor::restore();
}

std::vector<std::string> init_menu(std::vector<std::string> &v){
    v.push_back("\t1: Arucikk hozzaadasa\n\r");
    v.push_back("\t2: Arucikk torlese\n\r");
    v.push_back("\t3: Eladas\n\r");
    v.push_back("\t4: Feltoltes\n\r");
    v.push_back("\t5: Osszes arucikk listazasa\n\r");
    v.push_back("\t6: Specifikus arucikk listazasa\n\r");
    v.push_back("\t7: Mentes\n\r");
    v.push_back("\tq: Kilepes\n\r\n\r");

    return v;
}
