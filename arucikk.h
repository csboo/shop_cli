#include <string>
#pragma once

//arucikk osztaly definialasa
class arucikk{
  public:
    arucikk(std::string name = "", double price = 0, unsigned int instock = 0);
    //getters
    inline std::string get_name(){return this->name;}
    inline double get_price(){return this->price;}
    inline unsigned int get_instock(){return this->instock;}
    //setters
    inline void set_name(std::string& name){this->name = name;}
    inline void set_price(double price){this->price = price;}
    inline void set_instock(unsigned int instock){this->instock = instock;}
  private:
    std::string name; //arucikk neve
    double price; //arucikk ara, double tipus hogy nem egesz ar-nal is mukodjon
    unsigned int instock; //arucikk darabszama a boltban
};
