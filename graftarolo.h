#ifndef GRAFTAROLO_H
#define GRAFTAROLO_H

#include "graf.h"
#include "csucs.h"
#include "memtrace.h"


class Graf;

//Grafokat tárol egy tömbben

class GrafTarolo{
    Graf** grafok; //Grafokra mutató pointerek tömbje
    size_t db; //a tárolóban tárolt Grafok száma
public:
    GrafTarolo(): grafok(NULL), db(0){}
    void hozzaad (Graf* graf); //egy Gráf pointerét hozzáadja a tárolóhoz, ha még nincs benne
    size_t meret() const {return db;}
    Graf* operator[] (size_t index); //visszaadja az indexedik Grafra mutató pointert
    ~GrafTarolo();
};

#endif
