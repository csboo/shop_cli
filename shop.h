#include <cstdlib>
#include <vector>
#include "product.h" 
#pragma once

class shop{
  public:
    shop() = default;
    void add_product(std::string name, double price, unsigned int instock);
    void delete_product(std::string name);
    void sell(std::string mibol, unsigned int mennyit);
    void restock(std::string mibol, unsigned int mennyit);

    void list_products();
    void list_specific_product(std::string name);

    void load_data();
    void save_data();
    
    //getters
    inline std::vector<product> get_products(){return this->products;}
    //setters
    inline void set_products(std::vector<product> products){this->products = products;}

    
    
  private:
    int binary_search_product_index(std::string &keresett_aru);
    std::vector<product> products; //a vector that contains the products of the shop
    
};
