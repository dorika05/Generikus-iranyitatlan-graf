#ifndef GRAF_H
#define GRAF_H

#include "csucs.h"
#include "graftarolo.h"
#include "memtrace.h"

//a Graf egy gráfot reprezentál, mely Csucsokat tartalmaz és a Csucsokban található élek kötik össze õket, a Graf irányítatlan

class Graf{
    Csucs** csucsok; //a Grafhoz tartozó Csucsok pointereinek tömbje
    size_t db; //Csucsok száma
public:
    Graf(): csucsok(NULL), db(0){}
    void grafepito(int** matrix, Csucs** graf_csucsai, int n);
    Graf* bejar_bfs (Csucs* v); //BFS algoritmussal bejárja a Graf egy komponensét és ezt az új Grafot adja vissza, a Csucsokat nem másolja, csak mutatókat tárol rájuk
    void hozzaad(Csucs* v); //új Csucs hozzáadása a Grafhoz
    size_t csucsok_szama() const {return this->db;}
    size_t elek_szama(); //megadja a gráf éleinek számát
    Csucs* csucs_lekeres (size_t index) const ; //visszaadja az indexedik csúcsát a gráfnak
    bool operator==(const Graf &graf); //két Graf akkor egyenlõ, ha azonos Csucsokat tartalmaz (Csucsok alapján azonos éleket)
    GrafTarolo* komponensek(); //bejárja a Grafot minden Csucsból kiindulva, és a különbözõ komponenseket (Graf) egy GrafTaroloban adja vissza
    std::string csucsok_kiir(); //kiírja a Csucsok sorszámát vesszõvel elválasztva
    ~Graf();
};

#endif
