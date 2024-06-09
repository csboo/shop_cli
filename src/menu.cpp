#include "menu.h"
#include "external/cpptui/tui.hpp"
#include <iostream>
#include <string>
#include <vector>

void printmenu(std::vector<std::string> &menu, int invert){
    tui::screen::clear();
    tui::cursor::home();
    tui::cursor::visible(false);
    std::cout << tui::tui_string("\n\r\n\r\n\r\tValasszon opciot:\n\r\n\r").bold();
    for (auto line = 0; line < menu.size(); line++) {
        if (line == invert){
            std::cout << tui::tui_string(menu[line]).inverted();
        } else {
            std::cout << menu[line];
        }
        
    }
}

void print_msg(std::string text, std::pair<unsigned, unsigned> coords, bool save_cursor){
    if (!save_cursor) {
        tui::cursor::set_position(coords.first, coords.second);
        std::cout << '\t' << text; 
        return;
    }
    std::pair<unsigned, unsigned> pos = tui::cursor::get_position();
    tui::cursor::set_position(coords.first, coords.second);
    std::cout << '\t' << text; 
    tui::cursor::set_position(pos);
    
}
void clear_msg(){
    std::pair<unsigned, unsigned> pos = tui::cursor::get_position();
    tui::cursor::set_position(2, 1);
    tui::screen::clear_line();
    tui::cursor::set_position(pos);
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
std::string read_rsp(std::string &rsp){
    input in;
    tui::cursor::visible(true);
    while (in.get_state() != input::States::Enter) {
        in.get();
        switch (in.value()) {
        case 127:
            if (rsp.size() > 0) {
                // tui::cursor::set_position(tui::cursor::get_position().first, tui::cursor::get_position().second - rsp.size());
                rsp.pop_back();
                // std::cout << rsp;
            }
            continue;
        case 13:
            continue;
        default: 
            rsp.push_back(in.value());
            break;
        }
        if (rsp.size() > 0) {
            if (rsp.size() % 2 == 1) {
                tui::cursor::set_position(tui::cursor::get_position().first, tui::cursor::get_position().second - rsp.size());
                tui::screen::clear_line_right();
            } else {
                tui::cursor::set_position(tui::cursor::get_position().first, tui::cursor::get_position().second - rsp.size() - 1);
                tui::screen::clear_line_right();
            }
        }
        std::cout << rsp;
    }
    return rsp;  
}
input::Arrows is_arrow (char &x){
    if(x == 27 && std::cin.peek() == 91) {
        std::cin.ignore();
        // auto arrow = std::cin.get();
        switch (std::cin.peek()) {
        case 65:
            return input::Arrows::Up;
        case 66:
            return input::Arrows::Down;
        case 67:
            return input::Arrows::Right;
        case 68:
            return input::Arrows::Left;
        default:
            std::cin.ignore(3);
            return input::Arrows::Ctrl;
        }
    } else {    
        return input::Arrows::None;
    }
}

void input::get(){
    std::cin.get(this->opt);
    if (this->opt == 'q') {
        this->state = this->States::Quit;
        return;
    }
    if (is_arrow(this->opt) != Arrows::None){
        this->state = this->States::Arrow;
        return;
    } else if (this->opt == 13){
        this->state = this->States::Enter;
        return;
    } else if (this->opt < 0){
        this->state = this->States::Bad;
        this->opt = '\0';
        std::cin.clear();
        return;
    } else {
        this->state = this->States::Default;
        return;
    }
}
