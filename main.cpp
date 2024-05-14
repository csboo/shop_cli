#include <iostream>
#include <vector>
#include "kisbolt.h"


//main fuggveny
int main(){
  kisbolt coop;
  coop.arucikk_hozzaadas("csoki", 50, 3);
  coop.arucikk_hozzaadas("alma", 333, 4);
  coop.arucikk_hozzaadas("bela", 200, 6);

  coop.arucikkek_listazasa();
  coop.specifikus_arucikk_listazasa("alma");
  
  std::cout << coop.get_arucikkek().at(coop.arukereso("csoki")).get_instock();  
  coop.feltoltes("csoki", 3);
  std::cout << coop.get_arucikkek().at(coop.arukereso("csoki")).get_instock();  
  std::cout << std::endl;
  std::cout << coop.get_arucikkek().at(0).get_name();  
  coop.arucikk_torlese("csoki");
  std::cout << coop.get_arucikkek().at(0).get_name(); 

  
  return 0;
}
