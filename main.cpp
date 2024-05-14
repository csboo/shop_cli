#include "arucikk.h"
#include "kisbolt.h"
#include <iostream>

// main fuggveny
int main() {
  kisbolt coop;
  coop.adatok_betoltese();
  try {
    coop.binaris_arukereso("Garden Shears Sharpener");
  } 
  catch (std::string s) {
    std::cerr << "string error: " << s;
  } 
  catch (int e) {
    std::cerr << "int error" << e;
  }
  catch (...) {
    std::cerr << "other error";
  }
  

   
  return 0;
}
