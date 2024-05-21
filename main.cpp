#include "product.h"
#include "shop.h"
#include <iostream>
#include <stdexcept>
#include <string>

// main function
int main() {

    // std::cerr<<"PROGRAM STARTS\n";
    shop coop;
    // std::cerr <<"init class\n";
    coop.load_data();
    // std::cerr << "load data\n";

    // try {
    //   coop.list_specific_product("Garden Gnome");
    // }
    // catch (std::string s) {
    // std::cerr << "string error: " << s;
    // }
    // catch (int e) {
    // std::cerr << "int error" << e;
    // }
    // catch (...) {
    // std::cerr << "other error";
    // }

    std::string name = "garden gnome";
    try {
        coop.list_specific_product(name);
    }
    catch (std::out_of_range) {
        std::cerr << "no such product found\n";
    } 
    catch (...) {
        std::cerr << "some error occured\n";
    }

    return 0;
}
