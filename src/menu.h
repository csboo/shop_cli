#pragma once
#include <string>
#include <vector>

void print_msg(std::string text/*, int &count_err, bool iserror = false*/);
void clear_msg();
const char get_option();
void printmenu(std::vector<std::string> &menu, int invert = 0);
std::vector<std::string> init_menu(std::vector<std::string> &v);
void highlight(int &pos);
enum Arrows{
    None = 0,
    Up = 1, 
    Down = 2,
    Left = 3, 
    Right = 4
};
Arrows as_arrow (char &x);
