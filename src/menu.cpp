#include "menu.h"
#include "external/cpptui/tui.hpp"
#include "shop.h"
#include "tools.h"
#include <iostream>
#include <string>
#include <unordered_map>
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
        tui::screen::clear_line();
        std::cout << text; 
        return;
    }
    std::pair<unsigned, unsigned> pos = tui::cursor::get_position();
    tui::cursor::set_position(coords.first, coords.second);
    tui::screen::clear_line();
    std::cout << text; 
    tui::cursor::set_position(pos);
}
void clear_msg(){
    std::pair<unsigned, unsigned> pos = tui::cursor::get_position();
    tui::cursor::set_position(2, 1);
    tui::screen::clear_line();
    tui::cursor::set_position(pos);
}

std::vector<std::string> init_menu(std::vector<std::string> &v){
    v.push_back("\t1: Add a product\n\r");
    v.push_back("\t2: Delete a product\n\r");
    v.push_back("\t3: Sell\n\r");
    v.push_back("\t4: Restock\n\r");
    v.push_back("\t5: List all\n\r");
    v.push_back("\t6: List Specific product\n\r");
    v.push_back("\t7: Save\n\r");
    v.push_back("\t8: Load\n\r");
    v.push_back("\tq: Kilepes\n\r\n\r");

    return v;
}
std::string read_valid_char() {
    std::string temp = "";
    input in;
    tui::cursor::visible(true);
    while (in.get_state() != input::States::Enter) {
        in.get();
        print_log(concat("input was ", int(in.value())));
        if (in.get_state() == input::States::Esc) {
            print_log(concat("Esc detected"));
            return "\0";
        }
        if (in.get_state() == input::States::Default) {
            if (in.value() == tui::chars::backspace && temp.size() > 0) {
                tui::cursor::set_position(tui::cursor::get_position().first, tui::cursor::get_position().second-1);
                tui::screen::clear_line_right();
                temp.pop_back();
            } else {
                temp.push_back(in.value());
            }
            std::cout << tui::tui_string(in.value()).blue();
        }
    }
    tui::cursor::visible(false);
    print_log(concat("read valid input: '", temp, "'"));
    return temp;
}
input::Arrows input::is_arrow (char &x) {
    if(x == 27 && std::cin.peek() == 91) {
        std::cin.ignore();
        switch (std::cin.peek()) {
        case 65:
            std::cin.ignore();
            return input::Arrows::Up;
        case 66:
            std::cin.ignore();
            return input::Arrows::Down;
        case 67:
            std::cin.ignore();
            return input::Arrows::Right;
        case 68:
            std::cin.ignore();
            return input::Arrows::Left;
        default:
            std::cin.ignore();
            std::cin.ignore();
            std::cin.ignore();
            std::cin.ignore();
            return input::Arrows::Ctrl;
        }
    } else {    
        return input::Arrows::None;
    }
}

void input::get(){
    std::cin.get(this->opt);
    switch (this->is_arrow(this->opt)){
    case input::Arrows::Up:
        this->set(input::States::Arrow, '\0', input::Arrows::Up);
        return;
    case input::Arrows::Down:
        this->set(input::States::Arrow, '\0', input::Arrows::Down);
        return;
    case input::Arrows::Left:
        this->set(input::States::Arrow, '\0', input::Arrows::Left);
        return;
    case input::Arrows::Right:
        this->set(input::States::Arrow, '\0', input::Arrows::Right);
        return;
    case input::Arrows::Ctrl:
        this->set(input::States::Arrow, '\0', input::Arrows::Ctrl);
        return;
    case input::Arrows::None:
        if (this->opt == 27) {
            this->set(input::States::Esc, '\0', input::Arrows::None);
            return;
        }
        if (this->opt == tui::chars::Enter){
            this->set(input::States::Enter);
            return;
        } else if (this->opt < 0){
            this->set(input::States::Bad);
            // std::cin.clear();
            return;
        } else {
            this->state = input::States::Default;
            return;
        }
    }
}
std::string case_handling::make_prompt_string(tui::tui_string &msg, std::pair<unsigned, unsigned> start_coords) {
    std::string temp;
    print_msg(msg, start_coords, false);
    tui::cursor::set_position(tui::cursor::get_position().first + 2, tui::cursor::get_position().second - (msg.size()) + 4);
    temp = read_valid_char();
    print_log(concat("returned str was: '", temp, "'"));
    return temp;
}
int case_handling::make_prompt_int(tui::tui_string &msg, std::pair<unsigned, unsigned> start_coords) {
    std::string temp_str;
    int temp_int = 0;
    tui::cursor::set_position(start_coords);
    print_msg(msg, {tui::cursor::get_position().first, tui::screen::size().second / 2 - msg.size() / 2}, false);
    tui::cursor::set_position(tui::cursor::get_position().first + 2, tui::cursor::get_position().second - (msg.size()) + 4);
    temp_str = read_valid_char();
    while (temp_int == 0) {
        try {
            temp_int = stoi(temp_str);
        } catch (std::invalid_argument) {
            print_msg(tui::tui_string("Invalid number").red(), {2, tui::screen::size().second / 2 - 8}); //magicnumber
            tui::cursor::set_position(tui::cursor::get_position().first, tui::cursor::get_position().second - temp_str.size());
            tui::screen::clear_line_right();
            temp_str = read_valid_char();
        };
    }
    return temp_int;
}
std::string case_handling::get_valid_name(shop &shop, tui::tui_string &msg, std::pair<unsigned, unsigned> start_coords){
    std::string temp_str = case_handling::make_prompt_string(msg, start_coords);
    while(shop.binary_search_product_index(temp_str) == -1){
        tui::screen::clear_line();
        print_msg(tui::tui_string(concat(temp_str, " does not exist")).red(), {2, tui::screen::size().second / 2 - (temp_str.size() / 2 + 15 / 2)}); //yam yam (Yet Another Magicnumber)
        temp_str = make_prompt_string(msg, start_coords);
    }
    return temp_str;
}

int case_handling::get_valid_amount(shop &shop, std::string &product_name, tui::tui_string &msg, std::pair<unsigned, unsigned> start_coords){
    int temp_int = case_handling::make_prompt_int(msg, start_coords);
    tui::tui_string error_msg;
    while(shop.get_products().at(shop.binary_search_product_index(product_name)).get_instock() < temp_int){
        temp_int < 0 ? 
                    error_msg = "Invalid number" :
                    error_msg = concat(temp_int, " is too big, there is only ", shop.get_products().at(shop.binary_search_product_index(product_name)).get_instock(), " of ", product_name, "s in stock");
        print_msg(error_msg.red(), {2, tui::screen::size().second / 2 - error_msg.size() /  2});
        tui::screen::clear_line();
        temp_int = case_handling::make_prompt_int(msg, start_coords);
    }
    return temp_int;
}

void custom_keys(input &in, std::unordered_map<char, mapper> keys){
    auto key = keys.find(in.value());
    if (key != keys.end()) {
        in.set(key->second.state, key->second.value, key->second.arrow_state);
    }
}

