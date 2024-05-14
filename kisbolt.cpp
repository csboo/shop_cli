#include "kisbolt.h"
#include "arucikk.h"
#include <iostream>
#include <string>

kisbolt::kisbolt() { this->arucikkek.shrink_to_fit(); }

void kisbolt::arucikk_hozzaadas(std::string name, double price, unsigned int instock) {
  arucikk uj_aru(name, price, instock);
  this->arucikkek.push_back(uj_aru);
}

void kisbolt::arucikk_torlese(std::string name){
  this->arucikkek.erase(this->arucikkek.begin()+this->arukereso(name)); 
}

int kisbolt::arukereso(std::string keresett_aru) {
  int index = 0;
  while (index < arucikkek.size() &&
         this->arucikkek.at(index).get_name() != keresett_aru) {
    ++index;
  }
  if (index == arucikkek.size())
    throw "product_not_found"; // nem a legjobb hibakezelo modszer de legalabb
                               // fejbol irtam :D
  else
    return index;
}

void kisbolt::eladas(std::string mibol, unsigned int mennyit) {
  try {
    this->arucikkek.at(arukereso(mibol))
        .set_instock(this->arucikkek.at(arukereso(mibol)).get_instock() - mennyit);
    // a vektorben megkeressuk az arucikket az arukereso fuggvennyel,
    // majd beallitjuk a mennyiseget a jelenlegi ertek es az eladni kivant
    // mennyiseg kulonbsegere
  } catch (std::string error) {//TODO
    if (error == "product_not_found") {
      std::cerr << "A termek nem talalhato!"; // a hibakod kezelese, hiba eseten
    }
  }
}
void kisbolt::feltoltes(std::string mibol, unsigned int mennyit) {
  try {
    this->arucikkek.at(arukereso(mibol))
        .set_instock(this->arucikkek.at(this->arukereso(mibol)).get_instock() + mennyit);
    // a vektorben megkeressuk az arucikket az arukereso fuggvennyel,
    // majd beallitjuk a mennyiseget a jelenlegi ertek es a feltolteni kivant
    // mennyiseg osszegere
  } catch (std::string error) {//TODO
    if (error == "product_not_found") {
      std::cerr << "A termek nem talalhato!"; // a hibakod kezelese, hiba eseten
    }
  }
}

void kisbolt::arucikkek_listazasa(){
  for (auto arucikk : this->arucikkek) {
    std::cout << "\n\n\n";
    std::cout << arucikk.get_name() << " - " << arucikk.get_price() << "Ft,\tRaktaron: " << arucikk.get_instock() << " db\n";
  }
}

void kisbolt::specifikus_arucikk_listazasa(std::string name){
  std::cout<<"\n\n\n";
  arucikk keresett = this->arucikkek.at(this->arukereso(name));
  std::cout << keresett.get_name() << " - " << keresett.get_price() << "Ft,\tRaktaron: " << keresett.get_instock() << " db\n";
}

