#include "shop.h"
#include "product.h"
#include <fstream>
#include <iostream>
#include <string>

int shop::binary_search_product_index(std::string &wanted_product) {
    int index = -1;
    int begin = 0, end = this->products.size() - 1, mid = 0;
    // std::cerr << "start while for search\n";
    while (begin <= end && index == -1) {
        mid = begin + (end - begin) / 2;

        if (this->products.at(mid).get_name() == wanted_product) {
            index = mid;
        } else if (wanted_product > this->products.at(mid).get_name()) {
            begin = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    // std::cerr<<"end while for search, index : " << index << "\n";

    return index;
}

void shop::sell(std::string from, unsigned int amount) {
    this->products.at(this->binary_search_product_index(from))
        .set_instock(this->products.at(this->binary_search_product_index(from))
                         .get_instock() -
                     amount);
    // we look for the product in the vector with the binary search method
    // than we set the instock amount to the difference of the current value and
    // the sold amount
}
void shop::restock(std::string from, unsigned int amount) {
    this->products.at(this->binary_search_product_index(from))
        .set_instock(this->products.at(this->binary_search_product_index(from))
                         .get_instock() +
                     amount);
    // we look for the product in the vector with the binary search method
    // than set the instock amount to the sum of the current value and the
    // restocked amount
}

void shop::list_products() {
    for (auto arucikk : this->products) {
        std::cout << "\n\n\n";
        std::cout << arucikk.get_name() << " - " << arucikk.get_price()
                  << "Ft,\tRaktaron: " << arucikk.get_instock() << " db\n";
    }
}

void shop::list_specific_product(std::string &name) {
    // std::cerr << this->products.size() << "\n";
    product wanted_product =
        this->products.at(this->binary_search_product_index(name));
    // std::cerr << "found\n";
    std::cout << wanted_product.get_name() << " - "
              << wanted_product.get_price()
              << "Ft,\tRaktaron: " << wanted_product.get_instock() << " db\n";
}

void shop::load_data() {
    // std::cerr << "initing...\n";
    std::ifstream fin("storage.txt");
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
        name.pop_back(); // had to drop a damn space character :/
        this->products.push_back(product(name, price, instock));
        fin.get(); // needed to skip '\n' character at the end of the "instock"
                   // number
        fin.get(); // needed to skip the empty line between records
    }
    // std::cerr << "while done\n";
    fin.close();
    // std::cerr << "function load end\n";
}
void shop::save_data() {
    std::ofstream fout("storage.txt");
    if (!fout.is_open()) {
        throw 404;
    }

    for (auto i : this->products) {
        fout << i.get_name() << "\n"
             << i.get_price() << "\n"
             << i.get_instock() << "\n"
             << "\n";
    }

    fout.close();
}
