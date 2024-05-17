#include "product.h"
#include "shop.h"
#include <iostream>
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

  std::string name="garden gnome";
  coop.list_specific_product(name);
  std::cout << coop.get_products().at(coop. binary_search_product_index(name)).get_price();
  // std::cerr<<"found query\n";
   
  return 0;
}
