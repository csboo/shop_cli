#include "product.h"
#include "shop.h"
#include <iostream>
#include <string>

// main function
int main() {

    // std::cerr<<"PROGRAM STARTS\n";
    shop coop;
    // std::cerr <<"init class\n";
    // coop.load_data();
    // std::cerr << "load data\n";

    coop.add_product("FEri", 0, 0);
    coop.add_product("feri", 0, 0);
    coop.add_product("feRI", 0, 0);
    coop.add_product("feco", 0, 0);

    std::cout << "\n\n" << "before sort: " << "\n\n";
    coop.list_products();
    std::cout << "\n\n" << "after sort: " << "\n\n";
    coop.sort_products_by_name();
    coop.list_products();    

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
    // std::string name = "garden gnome";
    // try {
    //     coop.list_specific_product(name);
    // }
    // catch (std::out_of_range) {
    //     std::cerr << "no such product found\n";
    // } 
    // catch (...) {
    //     std::cerr << "some error occured\n";
    // }

    return 0;
}
