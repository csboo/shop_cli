#include <string>
#pragma once

//arucikk osztaly definialasa
class arucikk{
  public:
    arucikk(std::string&, double&, unsigned int&);
    //getters
    std::string get_name(){return this->name;}
    double get_price(){return this->price;}
    unsigned int get_instock(){return this->instock;}
    //setters
    void set_name(std::string& name){this->name = name;}
    void set_price(double price){this->price = price;}
    void set_instock(unsigned int instock){this->instock = instock;}
  private:
    std::string name; //arucikk neve
    double price; //arucikk ara, double tipus hogy nem egesz ar-nal is mukodjon
    unsigned int instock; //arucikk darabszama a boltban
};
