#pragma once
#include "../external/cpptui/tui.hpp"
#include "external/cpptui/input.hpp"
#include "shop.h"
#include <string>
#include <vector>

namespace case_handling {
    std::string make_prompt_string(tui::string& msg, std::pair<unsigned, unsigned> start_coords);
    int make_prompt_int(tui::string& msg, std::pair<unsigned, unsigned> start_coords = {
                                              tui::cursor::get_position().first, tui::cursor::get_position().second});
    std::string get_valid_name(shop& shop, tui::string& msg, std::pair<unsigned, unsigned> start_coords);
    int get_valid_amount(shop& shop, std::string& product_name, tui::string& msg,
                         std::pair<unsigned, unsigned> start_coords);
}; // namespace case_handling
// struct mapper{
//     input::States state = input::States::Bad;
//     char value = '\0';
//     input::Arrows arrow_state = input::Arrows::None;
// };
void print_msg(const std::string &text, std::pair<unsigned, unsigned> coords = {2, 1}, bool save_cursor = true);
void clear_msg();
void printmenu(std::vector<std::string>& menu, size_t invert = 0);
std::vector<std::string> init_menu(std::vector<std::string>& v);
inline std::string read_valid_char() {
    std::string temp;
    Input inp;
    tui::cursor::visible(true);
    std::cout.flush();
    while (inp != SpecKey::Enter) {
        inp = Input::read();
        if (inp.is_ch) {
            temp.push_back(inp.ch);
            std::cout << inp.ch << std::flush;
        }
        if (inp == SpecKey::Backspace && temp.size() > 0) {
            tui::cursor::set_position(tui::cursor::get_position().first, tui::cursor::get_position().second - 1);
            tui::screen::clear_line_right();
            temp.pop_back();
        }
    }
    tui::cursor::visible(false);
    return temp;
}
// void custom_keys(input &in, std::unordered_map<char, mapper> keys);
