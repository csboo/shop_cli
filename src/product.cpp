//methods of product header:
#include "product.h"

product::product(std::string name, double price,unsigned int instock){
  this->name = name;
  this->price = price;
  this->instock = instock;
}
