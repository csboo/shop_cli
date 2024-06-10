#include "shop.h"
#include "external/cpptui/tui.hpp"
#include "product.h"
#include "tools.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void shop::sell(std::string from, unsigned int amount) {
    this->products.at(this->binary_search_product_index(from))
        .set_instock(this->products.at(this->binary_search_product_index(from))
                         .get_instock() -
                     amount);
    // we look for the product in the vector with the this->binary search method
    // than we set the instock amount to the difference of the current value and
    // the sold amount
}
void shop::restock(std::string from, unsigned int amount) {
    this->products.at(this->binary_search_product_index(from))
        .set_instock(this->products.at(this->binary_search_product_index(from))
                         .get_instock() +
                     amount);
    // we look for the product in the vector with the this->binary search method
    // than set the instock amount to the sum of the current value and the
    // restocked amount
}

/// "Láttátok mit csináltam?"
void shop::add_product(const std::string& name, double price, unsigned int instock) {
     // finds the value `name` in `products` vector, lowerbound position of name
    std::vector<product>::iterator iter =
        std::lower_bound(this->products.begin(), this->products.end(), sajat_to_lower(name),
                         [](const product& p, const std::string &name) {
                             return sajat_to_lower(p.get_name()) < sajat_to_lower(name);
                         });
    this->products.insert(iter, product(name, price, instock));
}

void shop::list_products() {
    std::string line;
    for (auto arucikk : this->products) {
        std::cout << "\n";
        line = concat(arucikk.get_name(), " - ", arucikk.get_price(), "Ft,    Raktaron: ", arucikk.get_instock(), " db");
        tui::cursor::set_position(tui::cursor::get_position().first, tui::screen::size().second / 2 - line.size() / 2);
        std::cout << line << "\n";
    }
}

void shop::list_specific_product(std::string &name) {
    std::string line;
    // std::cerr << "before this->binary search\n";
    product wanted_product =
        this->products.at(this->binary_search_product_index(name));
    // std::cerr << "found\n";
    line = concat(wanted_product.get_name(), " - ", wanted_product.get_price(), "Ft,\tRaktaron: ", wanted_product.get_instock(), " db");
    tui::cursor::set_position(tui::screen::size().first / 2, tui::screen::size().second / 2 - line.size() / 2);
    std::cout << line;
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
    this->sort_products_by_name();
}
void shop::save_data() {
    // this->sort_products_by_name();
    // We don't have to sort here, because
    // 1) the vector should be sorted already, and
    // 2) the loader function will sort anyways

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
