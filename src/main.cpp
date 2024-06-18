#include "external/cpptui/tui.hpp"
#include "menu.h"
#include "shop.h"
#include "tools.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <utility>
#include <vector>

void app(shop &shop);

// main function
int main() {
    reset_log();
    tui::init_term(false, true);

    shop shop;
    try {
        app(shop);
    } catch (...) {
        tui::cursor::visible(false);
        tui::screen::clear();
        print_msg("App crashed due to an unknown error", {tui::screen::size().first / 2, tui::screen::size().second / 2 - 35 / 2}); //yam    
        print_msg("Press any key to quit.", {tui::screen::size().first / 2 + 1, tui::screen::size().second / 2 - 22 / 2}); //yam
        std::cin.clear();
        std::cin.get();
    }

    tui::reset_term();
    return 0;
}
void app(shop &shop){
    //TODO make case handling shit temp, instead of global(ish)
    //TODO trim whitespaces from reading strings mayybe
    //TODO handel cases where the shit is empty or doesnt exist
    //TODO Handel whitespaces
    //TODO more translation
    //TODO fzf
    //TODO MAYBE print_another_msg() prints msg and \r\n\t
    //TODO TUI_HPP tui_string().rawsize()
    //TODO pretty print formating, ESC to cancel anything
    //TODO load on start, file name, overwrite support, dont save/load empty, CONFIRMATION Y/n style
    //TODO error handling
    //TODO arrow handling could be a while()
    std::vector<std::string> menu;
    init_menu(menu);
    printmenu(menu);
    input opt;
    int pos=0;
    while (opt.value() != 'q'){
        print_log(concat("Last known state was(Def, Arr, Ent, Bad, Esc): ", opt.get_state()));
        opt.get();
        clear_msg();
        
        custom_keys(opt, {
                    {'k', {input::States::Arrow, '\0', input::Arrows::Up} }, 
                    {'j', {input::States::Arrow, '\0', input::Arrows::Down} },
                    {'h', {input::States::Arrow, '\0', input::Arrows::Left} },
                    {'l', {input::States::Arrow, '\0', input::Arrows::Right} }
        });
        if(opt.get_state() == input::States::Arrow) {
            switch (opt.get_arrow_state()) {
            case input::Arrows::Up:
                if (--pos < 0) {
                    pos = menu.size()-1;
                }
                printmenu(menu, pos);
                opt.set();
                continue;            
            case input::Arrows::Down:
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
                opt.set(input::States::Bad);
                break;
            };
        }
        if (opt.get_state() == input::States::Enter) {
            opt.set(input::States::Default, pos + 1 + 48); //int to char convertion, numeric chars start at char(48), which is 0
        } 
        if(opt.get_state() == input::States::Default){
            tui::tui_string msg = "";
            tui::tui_string msg2 = "";
            std::string str_rsp = "";
            std::string str_rsp2 = "";
            int int_rsp = 0;
            int int_rsp2 = 0;
            switch (opt.value()) {
            case '1':
                tui::screen::clear();
                tui::cursor::home();

                msg = "What product would you like to add?";
                case_handling::make_prompt_string(str_rsp, msg,  {6, tui::screen::size().second / 2 - msg.size() / 2});
                std::cin.ignore();
                if (str_rsp == "\0") {
                    printmenu(menu, pos);
                    break;
                }

                msg = concat("Enter the price for '", str_rsp, "'");
                case_handling::make_prompt_int(str_rsp2, int_rsp, msg, {tui::cursor::get_position().first + 2, tui::cursor::get_position().second});

                msg = concat("Enter the amount to add of '", str_rsp, "'");
                case_handling::make_prompt_int(str_rsp2, int_rsp2, msg, {tui::cursor::get_position().first + 2, tui::cursor::get_position().second});

                shop.add_product(str_rsp, int_rsp, int_rsp2);
                printmenu(menu, pos);
                print_msg(tui::tui_string(concat("\t", str_rsp, " added successfully")).green());
                break;
            case '2':
                tui::screen::clear();
                tui::cursor::home();

                msg = "Which product would you like to delete?";
                case_handling::get_valid_name(shop, str_rsp, msg, {6, tui::screen::size().second / 2 - msg.size() / 2});

                shop.delete_product(str_rsp);
                printmenu(menu, pos);
                print_msg(tui::tui_string(concat("\t", str_rsp, " deleted successfully")).green());
                break;
            case '3':
                tui::screen::clear();
                tui::cursor::home();

                msg = "Which product would you like to sell?";
                str_rsp = case_handling::get_valid_name(shop, str_rsp, msg, {6, tui::screen::size().second / 2 - msg.size() / 2});

                msg = "Please enter the amount to sell:";
                case_handling::get_valid_amount(shop, str_rsp, str_rsp2, int_rsp, msg, {tui::cursor::get_position().first + 2, tui::screen::size().second / 2 - msg.size() / 2});

                shop.sell(str_rsp, int_rsp);
                printmenu(menu, pos);
                print_msg(tui::tui_string(concat("\tSuccessfully sold ", int_rsp, " of " ,str_rsp)).green());
                break;
            case '4':
                tui::screen::clear();
                tui::cursor::home();

                msg = "Which product would you like to restock?";
                str_rsp = case_handling::get_valid_name(shop, str_rsp, msg, {6, tui::screen::size().second / 2 - msg.size() / 2});

                msg = "Please enter the amount to restock:";
                case_handling::get_valid_amount(shop, str_rsp, str_rsp2, int_rsp, msg, {tui::cursor::get_position().first + 2, tui::screen::size().second / 2 - msg.size() / 2});

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
                case_handling::get_valid_name(shop, str_rsp, msg, {tui::cursor::get_position().first + 6, tui::screen::size().second / 2 - msg.size() / 2});
                
                tui::screen::clear();
                shop.list_specific_product(str_rsp);
                std::cin.get();
                printmenu(menu, pos);
                break;
            case '7':
                shop.save_data(); 
                print_msg(tui::tui_string("\tFile saved successfully").green());
                break;
            case '8':
                shop.load_data();
                print_msg(tui::tui_string("\tFile loaded successfully").green());
                break;
            case '9':
                opt.set(input::States::Default, 'q');
                continue;
            default:
                opt.switch_state(input::States::Bad);
                break;
            };
        }
        if (opt.get_state() == input::States::Bad) {
            print_msg(tui::tui_string("\tWrong input").red());
            continue;
        }   
        if (opt.get_state() == input::States::Esc) {
            print_msg(tui::tui_string("\tOperation canceled").blue());
            continue;
        }
    }
}
