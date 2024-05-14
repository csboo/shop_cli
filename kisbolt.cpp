#include "kisbolt.h"
#include "arucikk.h"
#include <fstream>
#include <iostream>
#include <string>

// kisbolt::kisbolt() { this->set_arucikkek(adatok_betoltese()); }

void kisbolt::arucikk_hozzaadas(std::string name, double price,
                                unsigned int instock) {
  arucikk uj_aru(name, price, instock);
  this->arucikkek.push_back(uj_aru);
}

void kisbolt::arucikk_torlese(std::string name) {
  this->arucikkek.erase(this->arucikkek.begin() + this->binaris_arukereso(name));
}

int kisbolt::binaris_arukereso(std::string &keresett_aru) {
  int index = -1;
  int begin = 0, end = this->arucikkek.size() - 1, mid = 0;
  // std::cerr << "start while for search\n";
  while (begin <= end && index == -1) {
    mid = begin+(end-begin)/2;
    
    if(this->arucikkek.at(mid).get_name() == keresett_aru){
      index = mid;
    } else if (keresett_aru > this->arucikkek.at(mid).get_name()){
      begin = mid + 1;
    } else {
      end = mid - 1;
    }
  }
  // std::cerr<<"end while for search, index : " << index << "\n";

  // if(this->arucikkek.at(index).get_name() != keresett_aru){
    // std::cerr << "nicsmeg";
  // }
  
  return index;
}

void kisbolt::eladas(std::string mibol, unsigned int mennyit) {
  this->arucikkek.at(this->binaris_arukereso(mibol))
      .set_instock(this->arucikkek.at(this->binaris_arukereso(mibol)).get_instock() -
                   mennyit);
  // a vektorben megkeressuk az arucikket az arukereso fuggvennyel,
  // majd beallitjuk a mennyiseget a jelenlegi ertek es az eladni kivant
  // mennyiseg kulonbsegere
}
void kisbolt::feltoltes(std::string mibol, unsigned int mennyit) {
  this->arucikkek.at(this->binaris_arukereso(mibol))
      .set_instock(this->arucikkek.at(this->binaris_arukereso(mibol)).get_instock() +
                   mennyit);
  // a vektorben megkeressuk az arucikket az arukereso fuggvennyel,
  // majd beallitjuk a mennyiseget a jelenlegi ertek es a feltolteni kivant
  // mennyiseg osszegere
}

void kisbolt::arucikkek_listazasa() {
  for (auto arucikk : this->arucikkek) {
    std::cout << "\n\n\n";
    std::cout << arucikk.get_name() << " - " << arucikk.get_price()
              << "Ft,\tRaktaron: " << arucikk.get_instock() << " db\n";
  }
}

void kisbolt::specifikus_arucikk_listazasa(std::string name) {
  // std::cerr << this->arucikkek.size() << "\n";
  arucikk keresett = this->arucikkek.at(this->binaris_arukereso(name));
  // std::cerr << "keresve\n";
  std::cout << keresett.get_name() << " - " << keresett.get_price()
            << "Ft,\tRaktaron: " << keresett.get_instock() << " db\n";
}

void kisbolt::adatok_betoltese() {
  // std::cerr << "initing...\n";
  std::ifstream fin("raktar.txt");
  if (!fin.is_open()) {
    throw 404;
  }

  std::string name;
  double price = 0;
  unsigned int instock = 0;
  // std::cerr << "while start\n";
  while (getline(fin, name)) {
    fin >> price;
    fin >> instock;
    name.pop_back(); //egy franya space karaktert ki kell szedni :/
    this->arucikkek.push_back(arucikk(name, price, instock));
    fin.get(); // a sorvegi "\n" karaktert eldobja, hogy a kovetkezo iteracioban
               // a getline a kovetkezo sor vegeig olvasson be
    fin.get(); // a termekek kozotti ures sor kihagyasa miatt kell
  }
  // std::cerr << "while done\n";
  fin.close();
  // std::cerr << "function load end\n";
}
void kisbolt::adatok_mentese() {
  std::ofstream fout("raktar.txt");
  if (!fout.is_open()) {
    throw 404;
  }

  for (auto i : this->arucikkek) {
    fout << i.get_name() << "\n"
         << i.get_price() << "\n"
         << i.get_instock() << "\n"
         << "\n";
  }

  fout.close();
}
