#include <iostream>

#include "csucs.h"
#include "memtrace.h"
#include "gtest_lite.h"
#include "graf.h"
#include "graftarolo.h"
#include "beolvaso.h"
#include "tesztek.h"


int main(int argc, char *argv[]){
    if (argc<=1){
        std::cout<<"Nem adtal meg fajlt, a tesztek futnak"<<std::endl;
        tesztek();
        return 0;
    }
    std::cout<<std::endl<<"Parancssorbol meghivott matrix: "<< argv[1] <<std::endl;
    int n;
    int** matrix;
    try{
        matrix = matrixba_olvas(argv[1], n);
    }catch(char const* e){
        std::cout<<"Hiba lepett fel"<<std::endl;
        std::cout<<e<<std::endl;
        return -1;
    }
    if (matrix==NULL){
        return -1;
    }
    else{
        //felépítjük a gráfot
        Graf graf1;
        Csucs* csucsok[n];
        for (int i=0; i<n; i++){
            csucsok[i] = new Csucs(i);
        }
        graf1.grafepito(matrix,csucsok,n);
        GrafTarolo* tarolo;
        tarolo = graf1.komponensek();
        //ha egy komponens van, akkor a gráf összefüggõ
        if (tarolo->meret()==1){
            std::cout<<"Csomopontok szama: "<<graf1.csucsok_szama()<<std::endl;
            std::cout<<"Elek szama: "<<graf1.elek_szama()<<std::endl;
            std::cout<<"A graf osszefuggo"<<std::endl;
        }
        //ha nem összefüggõ, akkor kiírjuk a komponenseket
        else{
            std::cout<<"A graf nem osszefuggo"<<std::endl;
            int csucsszam=0;
            for (size_t i=0; i<tarolo->meret(); i++){
                csucsszam+=(*tarolo)[i]->csucsok_szama();
            }
            std::cout<<"Csomopontok szama: "<<csucsszam<<std::endl;

            int elszam=graf1.elek_szama();
            std::cout<<"Elek szama: "<<elszam<<std::endl;
            for (size_t i=0; i<tarolo->meret(); i++){
                std::string szoveg=(*tarolo)[i]->csucsok_kiir();
                std::cout<<i+1<<". komponens: "<<szoveg<<std::endl;
            }
        }

        delete tarolo;
        for (int i = 0; i < n; i++) {
            delete csucsok[i];
        }
        for (int i = 0; i < n; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    return 0;
}
