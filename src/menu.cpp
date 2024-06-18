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
std::string read_rsp(std::string &rsp){
    rsp = "";
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
            if (in.value() == tui::chars::backspace && rsp.size() > 0) {
                tui::cursor::set_position(tui::cursor::get_position().first, tui::cursor::get_position().second-1);
                tui::screen::clear_line_right();
                rsp.pop_back();
            } else {
                rsp.push_back(in.value());
            }
            std::cout << tui::tui_string(in.value()).blue();
        }
    }
    tui::cursor::visible(false);
    print_log(concat("read valid input: ", rsp));
    return rsp;
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
std::string case_handling::make_prompt_string(std::string &holder, tui::tui_string &msg, std::pair<unsigned, unsigned> start_coords) {
    print_msg(msg, start_coords, false);
    tui::cursor::set_position(tui::cursor::get_position().first + 2, tui::cursor::get_position().second - (msg.size()) + 4);
    holder = read_rsp(holder);
    print_log(concat("returned str was: '", holder, "'"));
    return holder;
}
int case_handling::make_prompt_int(std::string &str_holder, int &int_holder, tui::tui_string &msg, std::pair<unsigned, unsigned> start_coords) {
    tui::cursor::set_position(start_coords);
    print_msg(msg, {tui::cursor::get_position().first, tui::screen::size().second / 2 - msg.size() / 2}, false);
    tui::cursor::set_position(tui::cursor::get_position().first + 2, tui::cursor::get_position().second - (msg.size()) + 4);
    str_holder = ""; int_holder = 0;
    read_rsp(str_holder);
    while (int_holder == 0) {
        try {
            int_holder = stoi(str_holder);
        } catch (std::invalid_argument) {
            print_msg(tui::tui_string("Invalid number").red(), {2, tui::screen::size().second / 2 - 8}); //magicnumber
            tui::cursor::set_position(tui::cursor::get_position().first, tui::cursor::get_position().second - str_holder.size());
            tui::screen::clear_line_right();
            read_rsp(str_holder);
        };
    }
    return int_holder;
}
std::string case_handling::get_valid_name(shop &shop, std::string &name, tui::tui_string &msg, std::pair<unsigned, unsigned> start_coords){
    name = case_handling::make_prompt_string(name, msg, start_coords);
    while(shop.binary_search_product_index(name) == -1){
        tui::screen::clear_line();
        print_msg(tui::tui_string(concat(name, " does not exist")).red(), {2, tui::screen::size().second / 2 - (name.size() / 2 + 15 / 2)}); //yam yam (Yet Another Magicnumber)
        make_prompt_string(name, msg, start_coords);
    }
    return name;
}

int case_handling::get_valid_amount(shop &shop, std::string &product_name, std::string &str_holder, int &int_holder, tui::tui_string &msg, std::pair<unsigned, unsigned> start_coords){
    int_holder = case_handling::make_prompt_int(str_holder, int_holder, msg, start_coords);
    tui::tui_string msg2;
    while(shop.get_products().at(shop.binary_search_product_index(product_name)).get_instock() < int_holder){
        int_holder < 0 ? 
                    msg2 = "Invalid number" :
                    msg2 = concat(int_holder, " is too big, there is only ", shop.get_products().at(shop.binary_search_product_index(product_name)).get_instock(), " of ", product_name, "s in stock");
        print_msg(msg2.red(), {2, tui::screen::size().second / 2 - msg2.size() /  2}); //yam yam (Yet Another Magicnumber)
        tui::screen::clear_line();
        int_holder = case_handling::make_prompt_int(str_holder, int_holder, msg, start_coords);
    }
    return int_holder;
}

void custom_keys(input &in, std::unordered_map<char, mapper> keys){
    auto key = keys.find(in.value());
    if (key != keys.end()) {
        in.set(key->second.state, key->second.value, key->second.arrow_state);
    }
}

