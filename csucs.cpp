#include <iostream>

#include "csucs.h"

void Csucs::osszekot(Csucs* v){
    //ha már van ilyen él, akkor nem köti össze újra
    for (size_t i=0; i<(this->elek_szama); i++){
        if (elek[i]->sorszam == v->sorszam)
            return;
    }
    //kibõvíti a tömböt és a végére beszúrja az új élet
    Csucs** uj = new Csucs*[this->elek_szama+1];
    (this->elek_szama)++;
    for (size_t i=0; i<(this->elek_szama-1); i++){
        uj[i]=elek[i];
    }
    uj[this->elek_szama-1]=v;
    if (elek!=NULL)
        delete[] elek;
    elek=uj;
    //a másik csúcsot is összeköti ezzel (hiszen irányítatlan gráf)
    v->osszekot(this);
}

Csucs* Csucs::el_lekeres(size_t index) const {
    if (index+1>this->elek_szama)
        return NULL;
    return elek[index];
}

bool Csucs::van_hurokel() const{
    bool van=false;
    for (size_t j=0; j<elek_szama_lekeres(); j++){
        if (el_lekeres(j)->sorszam_lekeres()==sorszam){
            van=true;
            break;
        }
    }
    return van;
}



bool Csucs::operator==(const Csucs &csucs){
    //az élek számának egyezni kell
    if (csucs.elek_szama_lekeres()!=this->elek_szama_lekeres())
        return false;
    //a sorszámnak egyezni kell
    if (csucs.sorszam_lekeres()!=this->sorszam_lekeres())
        return false;
    //minden egyes élnek egyezni kell
    for (size_t i=0; i<csucs.elek_szama_lekeres(); i++){
        bool benne = false;
        for (size_t j=0; j<this->elek_szama_lekeres(); j++){
            if (elek[j]==csucs.el_lekeres(i)){
                benne = true;
                break;
            }
        }
        if (benne == false)
            return false;
    }
    return true;
}


Csucs::~Csucs(){
    if (elek!=NULL)
        delete[] elek;
}
