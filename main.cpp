#include "product.h"
#include "shop.h"
#include <iostream>

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

  coop.list_specific_product("Garden Gnome");
  // std::cerr<<"found query\n";
   
  return 0;
}
