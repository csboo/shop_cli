#include "product.h"
#include <cstdlib>
#include <vector>
#pragma once

class shop {
public:
  shop() = default;
  inline void add_product(std::string name, double price,
                          unsigned int instock) {
    this->products.push_back(product(name, price, instock));
  }
  inline void delete_product(std::string name) {
    this->products.erase(this->products.begin() +
                         this->binary_search_product_index(name));
  }
  void sell(std::string mibol, unsigned int mennyit);
  void restock(std::string mibol, unsigned int mennyit);

  void list_products();
  void list_specific_product(std::string &name);
  int binary_search_product_index(std::string &keresett_aru);

  void load_data();
  void save_data();

  // getters
  inline std::vector<product> get_products() { return this->products; }
  // setters
  inline void set_products(std::vector<product> products) {
    this->products = products;
  }

private:
  std::vector<product>
      products; // a vector that contains the products of the shop
};
