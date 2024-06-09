#include "external/cpptui/tui.hpp"
#include "menu.h"
#include "shop.h"
#include "tools.h"
#include <exception>
#include <iostream>
#include <string>
#include <system_error>
#include <unistd.h>
#include <utility>
#include <vector>

void run(shop &shop);

// main function
int main() {
    shop shop;
    run(shop);
    return 0;
}
void run(shop &shop){
    reset_log();
    tui::init_term(false, true);
    int error = 0;
    std::vector<std::string> menu;
    init_menu(menu);
    printmenu(menu);
    // std::string name;
    input opt;
    int pos=0;
    int iter = 0;
    while (opt.get_state() != input::States::Quit){
        print_log(concat("On: ", iter));
        opt.get();
        print_log(concat("opt was: '", int(opt.value()), "'" ));
        print_log(concat("state was: '", opt.get_state(), "'" ));
        clear_msg();
        switch (opt.get_state()) {
        case input::States::Quit:
            continue;
        case input::States::Bad:
            continue;
        case input::States::Arrow:
            print_log(concat("Arrow detected, should be: ", opt.get_arrow_state()));
            switch (opt.get_arrow_state()) {
            case input::Arrows::Up:
                print_log("Arrow up");
                if (--pos < 0) {
                    pos = menu.size()-1;
                }
                printmenu(menu, pos);
                continue;            

            case input::Arrows::Down:
                print_log("Arrow down");
                if (++pos == menu.size()) {
                    pos = 0;
                }
                printmenu(menu, pos);
                continue;
            case input::Arrows::Left:
            case input::Arrows::Right:
            default:
                print_log(concat("On: ", iter, " Arrow NOT up NOR down"));
                opt.reset();
                opt.set_state(input::States::Default);
                break;
            }            
        case input::States::Enter: 
            opt.set_value(pos + 1 + 48); // -_-
            opt.set_state(input::States::Default);
            break;
        case input::States::Default: 
            break;
        }
        if(opt.get_state() == input::States::Default){
            tui::tui_string msg;
            std::string rsp;
            switch (opt.value()) {
            case '1':
                tui::screen::clear();
                tui::cursor::home();
                msg = "Adja meg a hozzaadni kivant termek nevet:";
                print_msg(msg.bold(), {6, tui::screen::size().second /2 - msg.size()/2}, false);
                tui::cursor::set_position(tui::cursor::get_position().first + 1, tui::cursor::get_position().second - (msg.size()/2) - 1);
                read_rsp(rsp);
                std::cin.get();
                // shop.add_product(rsp, , )
                printmenu(menu, pos);
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
            default:
                std::pair<unsigned, unsigned> pos = tui::cursor::get_position();
                tui::cursor::set_position(2, 1);
                std::cout << tui::tui_string("\tHibas bemenet!").red() << "(" << ++error << "x)";
                tui::cursor::set_position(pos);
                continue;
            }
            error = 0;
        }
    }
    tui::reset_term();
}
