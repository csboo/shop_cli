#include "menu.h"
#include "../external/cpptui/tui.hpp"
#include "shop.h"
#include "tools.h"
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

void printmenu(std::vector<std::string>& menu, size_t invert) {
    tui::screen::clear();
    tui::cursor::home();
    tui::cursor::visible(false);
    std::cout << tui::string("\n\r\n\r\n\r\tValasszon opciot:\n\r\n\r").bold();
    for (size_t line = 0; line < menu.size(); line++) {
        if (line == invert) {
            std::cout << tui::string(menu[line]).inverted();
        } else {
            std::cout << menu[line];
        }
    }
}

void print_msg(const std::string &text, std::pair<unsigned, unsigned> coords, bool save_cursor) {
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
    tui::cursor::set_position(pos.first, pos.second);
}
void clear_msg() {
    std::pair<unsigned, unsigned> pos = tui::cursor::get_position();
    tui::cursor::set_position(2, 1);
    tui::screen::clear_line();
    tui::cursor::set_position(pos.first, pos.second);
}

std::vector<std::string> init_menu(std::vector<std::string>& v) {
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

std::string case_handling::make_prompt_string(tui::string& msg, std::pair<unsigned, unsigned> start_coords) {
    std::string temp;
    print_msg(msg, start_coords, false);
    tui::cursor::set_position(tui::cursor::get_position().first + 2,
                              tui::cursor::get_position().second - (msg.size()) + 4);
    temp = read_valid_char();
    print_log(concat("returned str was: '", temp, "'"));
    return temp;
}
int case_handling::make_prompt_int(tui::string& msg, std::pair<unsigned, unsigned> start_coords) {
    std::string temp_str;
    int temp_int = 0;
    tui::cursor::set_position(start_coords.first, start_coords.second);
    print_msg(msg, {tui::cursor::get_position().first, (tui::screen::size().second / 2) - (msg.size() / 2)}, false);
    tui::cursor::set_position(tui::cursor::get_position().first + 2,
                              tui::cursor::get_position().second - (msg.size()) + 4);
    temp_str = read_valid_char();
    while (temp_int == 0) {
        try {
            temp_int = stoi(temp_str);
        } catch (const std::invalid_argument &err) {
            print_msg(tui::string("Invalid number").red(), {2, (tui::screen::size().second / 2) - 8}); // magicnumber
            tui::cursor::set_position(tui::cursor::get_position().first,
                                      tui::cursor::get_position().second - temp_str.size());
            tui::screen::clear_line_right();
            temp_str = read_valid_char();
        };
    }
    return temp_int;
}
std::string case_handling::get_valid_name(shop& shop, tui::string& msg, std::pair<unsigned, unsigned> start_coords) {
    std::string temp_str = case_handling::make_prompt_string(msg, start_coords);
    while (shop.binary_search_product_index(temp_str) == -1) {
        tui::screen::clear_line();
        print_msg(
            tui::string(concat(temp_str, " does not exist")).red(),
            {2, (tui::screen::size().second / 2) - (temp_str.size() / 2 + 15 / 2)}); // yam yam (Yet Another Magicnumber)
        temp_str = make_prompt_string(msg, start_coords);
    }
    return temp_str;
}

int case_handling::get_valid_amount(shop& shop, std::string& product_name, tui::string& msg,
                                    std::pair<unsigned, unsigned> start_coords) {
    size_t temp_int = case_handling::make_prompt_int(msg, start_coords);
    tui::string error_msg;
    while (shop.get_products().at(shop.binary_search_product_index(product_name)).get_instock() < temp_int) {
        temp_int < 0
            ? error_msg = "Invalid number"
            : error_msg = concat(temp_int, " is too big, there is only ",
                                 shop.get_products().at(shop.binary_search_product_index(product_name)).get_instock(),
                                 " of ", product_name, "s in stock");
        print_msg(error_msg.red(), {2, (tui::screen::size().second / 2) - (error_msg.size() / 2)});
        tui::screen::clear_line();
        temp_int = case_handling::make_prompt_int(msg, start_coords);
    }
    return temp_int;
}

// void custom_keys(input &in, std::unordered_map<char, mapper> keys){
//     auto key = keys.find(in.value());
//     if (key != keys.end()) {
//         in.set(key->second.state, key->second.value, key->second.arrow_state);
//     }
// }
