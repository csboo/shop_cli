#include <cstdlib>
#include <vector>
#include "arucikk.h" 
#pragma once

class kisbolt{
  public:
    kisbolt() = default;
    void arucikk_hozzaadas(std::string name, double price, unsigned int instock);
    void arucikk_torlese(std::string name);
    void eladas(std::string mibol, unsigned int mennyit);
    void feltoltes(std::string mibol, unsigned int mennyit);
    
    void arucikkek_listazasa();
    void specifikus_arucikk_listazasa(std::string name);

    void adatok_betoltese();
    void adatok_mentese();
    
    //getters
    inline std::vector<arucikk> get_arucikkek(){return this->arucikkek;}
    //setters
    inline void set_arucikkek(std::vector<arucikk> arucikkek){this->arucikkek = arucikkek;}

    
    
  private:
    int binaris_arukereso(std::string &keresett_aru);
    std::vector<arucikk> arucikkek; //a bolt arucikkeit tartalmazo vektor
    
};
