#include <string>
#pragma once

//product class definition
class product{
  public:
    product(std::string name = "", double price = 0, unsigned int instock = 0);
    //getters
    inline std::string get_name(){return this->name;}
    inline double get_price(){return this->price;}
    inline unsigned int get_instock(){return this->instock;}
    //setters
    inline void set_name(std::string& name){this->name = name;}
    inline void set_price(double price){this->price = price;}
    inline void set_instock(unsigned int instock){this->instock = instock;}
  private:
    std::string name; //name of product
    double price; //price of product, double type so it works with fractions
    unsigned int instock; //number of products in stock
};
