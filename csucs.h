#ifndef CSUCS_H
#define CSUCS_H

#include "memtrace.h"

//a Csucs a gráfnak egy csúcsát reprezentálja

class Csucs{
    unsigned int sorszam; //a Csucs azonosítója
    Csucs** elek; //Csucsból kifutó élek pointereinek tömbje
    size_t elek_szama; //Csucsból kifutó élek száma
public:
    Csucs(unsigned int sorszam = 0): sorszam(sorszam), elek(NULL), elek_szama(0){}
    void osszekot(Csucs* v); //összeköti az adott Csucsot a paraméterlént megkapott Csuccsal és viszont (irányítatlan élek)
    size_t sorszam_lekeres() const {return sorszam;}
    size_t elek_szama_lekeres() const {return elek_szama;}
    Csucs* el_lekeres (size_t index) const; //azt a csúcsot adja vissza, amelyikre az indexedik él mutat
    bool van_hurokel() const; //meghatározza, hogy az adott csúcsra illeszkedik-e hurokél
    bool operator==(const Csucs &csucs); //két Csucs egyenlõ, ha a sorszámuk azonos, és a belõle kifutó élek ugyanoda mutatnak
    ~Csucs();
};

#endif
