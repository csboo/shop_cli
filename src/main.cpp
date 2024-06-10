#include "external/cpptui/tui.hpp"
#include "menu.h"
#include "shop.h"
#include "tools.h"
#include <iostream>
#include <string>
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
    std::vector<std::string> menu;
    init_menu(menu);
    printmenu(menu);
    input opt;
    int pos=0;
    int iter = 0;
    while (opt.get_state() != input::States::Quit){
        print_log(concat("On: ", iter++));
        opt.get();
        print_log(concat("opt was: '", int(opt.value()), "'" ));
        print_log(concat("state was: '", opt.get_state(), "'" ));
        clear_msg();
        
        if (opt.get_state() == input::States::Quit){
            break;
        }
        if (opt.get_state() == input::States::Enter) {
            opt.set(input::States::Default, pos + 1 + 48); //int to char convertion, numeric chars start at char(48), which is 0
        } 
        if (opt.get_state() == input::States::Bad) {
            opt.set();
        }
        if(opt.get_state() == input::States::Arrow) {
            print_log(concat("Arrow detected, should be: ", opt.get_arrow_state()));
            switch (opt.get_arrow_state()) {
            case input::Arrows::Up:
                print_log("Arrow up");
                if (--pos < 0) {
                    pos = menu.size()-1;
                }
                printmenu(menu, pos);
                opt.set();
                continue;            
            case input::Arrows::Down:
                print_log("Arrow down");
                if (++pos == menu.size()) {
                    pos = 0;
                }
                printmenu(menu, pos);
                opt.set();
                continue;
            case input::Arrows::Left:
            case input::Arrows::Right:
            case input::Arrows::Ctrl:
            default:
                print_log(concat("On: ", iter, " Arrow, but NOT up NOR down"));
                opt.set(input::States::Bad);
                break;
            };
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
                opt.switch_state(input::States::Bad);
                break;
            };
        }
        if (opt.get_state() == input::States::Bad) {
            print_msg(tui::tui_string("Hibas bemenet!").red());
            continue;
        }   
    }
    tui::reset_term();
}
