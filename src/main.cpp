#include "external/cpptui/tui.hpp"
#include "menu.h"
#include "shop.h"
#include "tools.h"
#include <iostream>
#include <stdexcept>
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
    while (opt.value() != 'q'){
        print_log(concat("On: ", iter++));
        opt.get();
        print_log(concat("opt was: '", int(opt.value()), "'" ));
        print_log(concat("state was: '", opt.get_state(), "'" ));
        clear_msg();
        
        if (opt.get_state() == input::States::Bad) {
            opt.set();
        }
        if (opt.value() == 'k') {
            opt.set(input::States::Arrow, '\0', input::Arrows::Up);
        }
        if (opt.value() == 'j') {
            opt.set(input::States::Arrow, '\0', input::Arrows::Down);
        }
        if (opt.value() == 'h') {
            opt.set(input::States::Arrow, '\0', input::Arrows::Left);
        }
        if (opt.value() == 'l') {
            opt.set(input::States::Arrow, '\0', input::Arrows::Right);
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
            case input::Arrows::Right:
                opt.switch_state(input::States::Enter);
                break;
            case input::Arrows::Left:
            case input::Arrows::Ctrl:
            default:
                print_log(concat("On: ", iter, " Arrow, but NOT up NOR down"));
                opt.set(input::States::Bad);
                break;
            };
        }
        if (opt.get_state() == input::States::Enter) {
            opt.set(input::States::Default, pos + 1 + 48); //int to char convertion, numeric chars start at char(48), which is 0
        } 
        if(opt.get_state() == input::States::Default){
            tui::tui_string msg = "";
            std::string str_rsp = "";
            std::string str_rsp2 = "";
            int int_rsp = 0;
            int int_rsp2 = 0;
            switch (opt.value()) {
            case '1':
                tui::screen::clear();
                tui::cursor::home();

                msg = "Adja meg a hozzaadni kivant termek nevet:";
                print_msg(msg.bold(), {6, tui::screen::size().second / 2 - msg.size() / 2}, false);
                tui::cursor::set_position(tui::cursor::get_position().first + 2, tui::cursor::get_position().second - (msg.size()) + 4);
                read_rsp(str_rsp);

                msg = "Adja meg az arat:";
                print_msg(msg.bold(), {tui::cursor::get_position().first + 2, tui::screen::size().second /2 - msg.size()/2}, false);
                tui::cursor::set_position(tui::cursor::get_position().first + 2, tui::cursor::get_position().second - (msg.size()) + 4);
                read_rsp(str_rsp2);
                while (int_rsp == 0) {
                    try {
                        int_rsp = stoi(str_rsp2);
                    } catch (std::invalid_argument) {
                        print_msg(tui::tui_string("Ervenytelen szam").red(), {2, tui::screen::size().second / 2 - 8}); //magicnumber
                        tui::cursor::set_position(tui::cursor::get_position().first, tui::cursor::get_position().second - str_rsp2.size());
                        tui::screen::clear_line_right();
                        str_rsp2 = "";
                        read_rsp(str_rsp2);
                    };
                }

                msg = "Adja meg mennyiseget:";
                print_msg(msg.bold(), {tui::cursor::get_position().first + 2, tui::screen::size().second /2 - msg.size()/2}, false);
                tui::cursor::set_position(tui::cursor::get_position().first + 2, tui::cursor::get_position().second - (msg.size()) + 4);
                read_rsp(str_rsp2);
                while (int_rsp2 == 0) {
                    try {
                        int_rsp2 = stoi(str_rsp2);
                    } catch (std::invalid_argument) {
                        print_msg(tui::tui_string("Ervenytelen szam").red(), {2, tui::screen::size().second / 2 - 8}); //magicnumber
                        tui::cursor::set_position(tui::cursor::get_position().first, tui::cursor::get_position().second - str_rsp2.size());
                        tui::screen::clear_line_right();
                        str_rsp2 = "";
                        read_rsp(str_rsp2);
                    };
                }

                shop.add_product(str_rsp, int_rsp, int_rsp2);
                printmenu(menu, pos);
                print_msg(tui::tui_string(concat("\t", str_rsp, " added successfully")).green());
                break;
            case '2':
                tui::screen::clear();
                tui::cursor::home();

                msg = "Which product would you like to delete?";
                print_msg(msg.bold(), {6, tui::screen::size().second / 2 - msg.size() / 2}, false);
                tui::cursor::set_position(tui::cursor::get_position().first + 2, tui::cursor::get_position().second - (msg.size()) + 4);
                read_rsp(str_rsp);

                shop.delete_product(str_rsp);
                printmenu(menu, pos);
                print_msg(tui::tui_string(concat("\t", str_rsp, " deleted successfully")).green());
                break;
            case '3':
                tui::screen::clear();
                tui::cursor::home();

                msg = "Which product would you like to sell?";
                print_msg(msg.bold(), {6, tui::screen::size().second / 2 - msg.size() / 2}, false);
                tui::cursor::set_position(tui::cursor::get_position().first + 2, tui::cursor::get_position().second - (msg.size()) + 4);
                read_rsp(str_rsp);

                msg = "Please enter the amount to sell:";
                print_msg(msg.bold(), {tui::cursor::get_position().first + 2, tui::screen::size().second /2 - msg.size()/2}, false);
                tui::cursor::set_position(tui::cursor::get_position().first + 2, tui::cursor::get_position().second - (msg.size()) + 4);
                read_rsp(str_rsp2);
                while (int_rsp == 0) {
                    try {
                        int_rsp = stoi(str_rsp2);
                    } catch (std::invalid_argument) {
                        print_msg(tui::tui_string("Invalid number").red(), {2, tui::screen::size().second / 2 - 8}); //magicnumber
                        tui::cursor::set_position(tui::cursor::get_position().first, tui::cursor::get_position().second - str_rsp2.size());
                        tui::screen::clear_line_right();
                        str_rsp2 = "";
                        read_rsp(str_rsp2);
                    };
                }

                shop.sell(str_rsp, int_rsp);
                printmenu(menu, pos);
                print_msg(tui::tui_string(concat("\tSuccessfully sold ", int_rsp, " of " ,str_rsp)).green());
                break;
            case '4':
                tui::screen::clear();
                tui::cursor::home();

                msg = "Which product would you like to restock?";
                print_msg(msg.bold(), {6, tui::screen::size().second / 2 - msg.size() / 2}, false);
                tui::cursor::set_position(tui::cursor::get_position().first + 2, tui::cursor::get_position().second - (msg.size()) + 4);
                read_rsp(str_rsp);

                msg = "Please enter the amount to restock:";
                print_msg(msg.bold(), {tui::cursor::get_position().first + 2, tui::screen::size().second /2 - msg.size()/2}, false);
                tui::cursor::set_position(tui::cursor::get_position().first + 2, tui::cursor::get_position().second - (msg.size()) + 4);
                read_rsp(str_rsp2);
                while (int_rsp == 0) {
                    try {
                        int_rsp = stoi(str_rsp2);
                    } catch (std::invalid_argument) {
                        print_msg(tui::tui_string("Invalid number").red(), {2, tui::screen::size().second / 2 - 8}); //magicnumber
                        tui::cursor::set_position(tui::cursor::get_position().first, tui::cursor::get_position().second - str_rsp2.size());
                        tui::screen::clear_line_right();
                        str_rsp2 = "";
                        read_rsp(str_rsp2);
                    };
                }

                shop.restock(str_rsp, int_rsp);
                printmenu(menu, pos);
                print_msg(tui::tui_string(concat("\tSuccessfully restocked ", int_rsp, " of " ,str_rsp)).green());
                break;
            case '5':
                tui::screen::clear();
                tui::cursor::home();

                shop.list_products();
                std::cin.get();
                printmenu(menu, pos);
                break;
            case '6':
                tui::screen::clear();
                tui::cursor::home();

                msg = "Which product would you like list?";
                print_msg(msg.bold(), {6, tui::screen::size().second / 2 - msg.size() / 2}, false);
                tui::cursor::set_position(tui::cursor::get_position().first + 2, tui::cursor::get_position().second - (msg.size()) + 4);
                read_rsp(str_rsp);
                
                tui::screen::clear();
                shop.list_specific_product(str_rsp);
                std::cin.get();
                printmenu(menu, pos);
                break;
            case '7':
                shop.load_data();
                print_msg(tui::tui_string("\tFile loaded successfully").green());
                break;
            case '8':
                opt.set(input::States::Default, 'q');
                continue;
            default:
                opt.switch_state(input::States::Bad);
                break;
            };
        }
        if (opt.get_state() == input::States::Bad) {
            print_msg(tui::tui_string("\tHibas bemenet!").red());
            continue;
        }   
    }
    tui::reset_term();
}
