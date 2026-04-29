#include <iostream>

#include "graf.h"
#include "csucs.h"

void Graf::grafepito(int** matrix, Csucs** graf_csucsai, int n){
    //hozzáadja az összes csúcsot
    for (int i=0; i<n; i++){
        hozzaad(graf_csucsai[i]);
    }
    //a mátrix alapján összeköti a csúcsokat
    for (int i=0; i<n; i++){
        for (int j=i; j<n; j++){
            if (matrix[i][j]==1){
                Csucs* csucs1=csucs_lekeres(i);
                Csucs* csucs2=csucs_lekeres(j);
                csucs1->osszekot(csucs2);
            }
        }
    }
}


Graf* Graf::bejar_bfs (Csucs* v){
    //ellenõrzi, hogy a csúcs része-e a gráfnak
    bool benne = false;
    for (size_t i=0; i<db; i++){
        if (csucsok[i] == v){
            benne = true;
            break;
        }
    }
    if (!benne){
        return NULL;
    }
    Graf* bfs_fa = new Graf;
    //a bfs_fa-hoz hozzáadja a kiindulócsúcsot
    bfs_fa->hozzaad(v);
    for (size_t i=0; i<bfs_fa->csucsok_szama(); i++){
        Csucs* aktualis_csucs=bfs_fa->csucs_lekeres(i);
        //az aktuális csúcsból elérhetõ összes csúcsot hozzáadja a bfs_fa-hoz (szélességi bejárás)
        for (size_t j=0; aktualis_csucs->el_lekeres(j)!=NULL; j++){
            bfs_fa->hozzaad(aktualis_csucs->el_lekeres(j));
        }
    }
    return bfs_fa;
}



void Graf::hozzaad(Csucs* v){
    //ha már a csúcs része a gráfnak, akkor nem adja újra hozzá
    for (size_t i=0; i<(this->db); i++){
        if (csucsok[i]->sorszam_lekeres() == v->sorszam_lekeres())
            return;
    }
    //bõvíti a csucsok tömböt és a végére beszúrja az új csúcsot
    Csucs** uj = new Csucs*[this->db+1];
    (this->db)++;
    for (size_t i=0; i<(this->db-1); i++){
        uj[i]=csucsok[i];
    }
    uj[this->db-1]=v;
    if (csucsok!=NULL)
        delete[] csucsok;
    csucsok=uj;
}

size_t Graf::elek_szama(){
    size_t elszam=0;
    //minden élet kétszer számolunk (mert mindkét csúcs felõl beleszámolódnak)
    //kivéve a hurokél, ami csak egyszer számolódik
    for (size_t i=0; i<db; i++){
        elszam+=csucsok[i]->elek_szama_lekeres();
        if(csucsok[i]->van_hurokel())
            //ezzel a hurokélet is duplán számoljuk
            elszam+=1;
    }
    elszam=elszam/2;
    return elszam;
}


Csucs* Graf::csucs_lekeres (size_t index) const {
    if (index>this->db-1)
        return NULL;
    return csucsok[index];
}

std::string Graf::csucsok_kiir(){
    std::string szoveg;
    if (csucsok!=NULL){
        szoveg=std::to_string(csucsok[0]->sorszam_lekeres());
        for (size_t i=1; i<db; i++){
            szoveg.append(", ");
            szoveg.append(std::to_string(csucsok[i]->sorszam_lekeres()));
        }
    }
    return szoveg;
}

bool Graf::operator==(const Graf &graf){
    //csúcsok számának egyenlõnek kell lennie
    if (this->csucsok_szama()!=graf.csucsok_szama()){
        return false;
    }
    //minden csúcsnak és éleiknek egyezni kell
    for (size_t i=0; i<graf.csucsok_szama(); i++){
        bool benne = false;
        for (size_t j=0; j<this->csucsok_szama(); j++){
            if (csucsok[j]==graf.csucs_lekeres(i)){
                benne = true;
                break;
            }
        }
        if (benne == false)
            return false;
    }
    return true;
}

GrafTarolo* Graf::komponensek(){
    GrafTarolo* tarolo = new GrafTarolo;
    //végigmegy az összes csúcson
    for (size_t i=0; i<this->db; i++){
        Graf* aktualis_graf = bejar_bfs(this->csucs_lekeres(i));
        bool benne = false;
        //hozzáadja a tárolóhoz, ha a gráf még nincs benne a tárolóban
        for (size_t j=0; j<tarolo->meret(); j++){
            if (*((*tarolo)[j])==(*aktualis_graf)){
                benne=true;
                break;
            }
        }
        if (!benne){
            tarolo->hozzaad(aktualis_graf);
        }
        else
            delete aktualis_graf;
    }
    return tarolo;
}



Graf::~Graf(){
    if (csucsok!=NULL)
        delete[] csucsok;
}
