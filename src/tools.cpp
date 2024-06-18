#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include "shop.h"

std::string sajat_to_lower(std::string string) {
    std::transform(string.begin(), string.end(), string.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    // this function iterates through the characters of the parameter string,
    // and runs a function on all characters, which converts any character to
    // lowercase form using std::tolower, and stores the converted values in
    // their original place in the string, than returns the string
    return string;
}

int shop::binary_search_product_index(std::string &wanted_product) {
    int index = -1;
    int begin = 0, end = this->products.size() - 1, mid = 0;
    // std::cerr << "start while for search\n";
    while (begin <= end && index == -1) {
        mid = begin + (end - begin) / 2;
        if (sajat_to_lower(this->products.at(mid).get_name()) ==
            sajat_to_lower(wanted_product)) {
            index = mid;
        } else if (sajat_to_lower(wanted_product) >
                   sajat_to_lower(this->products.at(mid).get_name())) {
            begin = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    // std::cerr<<"end while for search, index : " << index << "\n";

    return index;
}

void shop::sort_products_by_name() {
    int min = 0;

    for (int i = 0; i < this->products.size() - 1; i++) {
        min = i;
        for (int j = i + 1; j < this->products.size(); j++) {
            if (sajat_to_lower(this->products.at(j).get_name()) <
                sajat_to_lower(this->products.at(min).get_name())) {
                min = j;
            }
        }
        std::swap(this->products.at(i), this->products.at(min));
    }
}
bool global_logging = true;
void print_log(std::string text){
    if (!global_logging) {
        return;
    }
    std::ofstream fout("log.txt", std::ios::app);
    fout << text << "\n";
    fout.close();
}
void reset_log(){
    std::ofstream fout("log.txt");
    fout.close();
}
