#pragma once
#include "product.h"
#include <cstdlib>
#include <vector>

class shop {
public:
  shop() = default;
  void add_product(const std::string& name, double price, unsigned int instock);
  inline void delete_product(std::string name) {
    this->products.erase(this->products.begin() +
                         this->binary_search_product_index(name));
  }
  void sell(std::string mibol, unsigned int mennyit);
  void restock(std::string mibol, unsigned int mennyit);

  void list_products();
  void list_specific_product(std::string &name);
  void sort_products_by_name();
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
