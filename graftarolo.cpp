#include <iostream>

#include "graf.h"
#include "csucs.h"
#include "graftarolo.h"


void GrafTarolo::hozzaad (Graf* graf){
    //ha már benne van a gráf, akkor nem adja hozzá
    for (size_t i=0; i<(this->db); i++){
        if (grafok[i]==graf)
            return;
    }
    //bõvíti a tömböt és hozzáadja az új gráfot
    Graf** uj = new Graf*[this->db+1];
    (this->db)++;
    for (size_t i=0; i<(this->db-1); i++){
        uj[i]=grafok[i];
    }
    uj[this->db-1]=graf;
    if (grafok!=NULL){
        delete[] grafok;
    }
    grafok=uj;
}

Graf* GrafTarolo::operator[](size_t index){
    if (index<db)
        return grafok[index];
    return NULL;
}


GrafTarolo::~GrafTarolo(){
    if (grafok!=NULL){
        for (size_t i=0; i<this->meret(); i++){
            delete (*this)[i];
        }
        delete[] grafok;
    }
}
