#include "arucikk.h"
#include "kisbolt.h"
#include <iostream>

// main fuggveny
int main() {

  // std::cerr<<"PROGRAM STARTS\n";
  kisbolt coop;
  // std::cerr <<"init class\n";
  coop.adatok_betoltese();
  // std::cerr << "load data\n";

  
  // try {
  //   coop.specifikus_arucikk_listazasa("Garden Gnome");         
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

  coop.specifikus_arucikk_listazasa("Garden Gnome");
  // std::cerr<<"found query\n";
   
  return 0;
}
