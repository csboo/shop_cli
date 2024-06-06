#include "external/cpptui/tui.hpp"
#include "menu.h"
#include "shop.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

void run(shop &shop);

// main function
int main() {
    shop shop;
    run(shop);
    return 0;
}
void run(shop &shop){
    tui::init_term(false, true);
    int error = 0;
    std::vector<std::string> menu;
    init_menu(menu);
    printmenu(menu);
    // std::string name;
    char opt = '\0';
    int pos=0;
    while (opt != 'q'){
        opt = get_option();
        clear_msg();

        switch (as_arrow(opt)) {
        case Arrows::Up:
            tui::screen::clear();
            tui::cursor::home();
            if (--pos < 0) {
                pos = menu.size()-1;
            }
            printmenu(menu, pos);
            continue;
        case Arrows::Down:
            tui::screen::clear();
            tui::cursor::home();
            if (++pos == menu.size()) {
                pos = 0;
            }
            printmenu(menu, pos);
            continue;
        case Arrows::Left:
        case Arrows::Right:
        case Arrows::None:
        default:
            break;
        }
        if (opt == 13) {
            // opt = static_cast<char>(pos + 1);
            opt = pos + 1 + 48; // -_-
            // tui::cursor::set_position(2, 1);
            // std::cout << opt;             
            // std::cin.get();
        }
        
        switch (opt) {
        case '1':
            print_msg(tui::tui_string("was 1").green());
            // tui::screen::clear();
            // tui::cursor::home();
            // tui::cursor::set_position(tui::screen::size()., )
            // shop.add_product(, , )
            break;
        case '2':
            print_msg(tui::tui_string("was 2").green());
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        case '6':
            break;
        case '7':
            break;
        case '8':
            break;
        default:
            tui::cursor::save();
            tui::cursor::set_position(2, 1);
            std::cout << tui::tui_string("\tHibas bemenet!").red() << "(" << ++error << "x)";
            tui::cursor::restore();
            continue;
        }
        error = 0;
    }
    
    tui::reset_term();
}
