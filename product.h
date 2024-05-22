#include <string>
#pragma once

//product class definition
class product{
  public:
    product(std::string name = "", double price = 0, unsigned int instock = 0);
    //getters
    inline const std::string get_name() const {return this->name;}
    inline const double get_price() const {return this->price;}
    inline const unsigned int get_instock() const {return this->instock;}
    //setters
    inline void set_name(std::string& name){this->name = name;}
    inline void set_price(double price){this->price = price;}
    inline void set_instock(unsigned int instock){this->instock = instock;}
  private:
    std::string name; //name of product
    double price; //price of product, double type so it works with fractions
    unsigned int instock; //number of products in stock
};
