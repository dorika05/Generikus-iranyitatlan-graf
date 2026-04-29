#include <iostream>
#include <string.h>

#include "beolvaso.h"
#include "memtrace.h"


char* fajlbeolvaso(std::string fajlnev){
    FILE* fp;
    fp=fopen(fajlnev.c_str(),"r");
    if (fp==NULL){
        return NULL;
    }
    char aktualis_karakter;
    int hossz=1;
    char* beolvasott_adatok = new char[1];
    beolvasott_adatok[0]='\0';
    //karakterenként olvas be a fájlból
    do{
        aktualis_karakter=fgetc(fp);
        beolvasott_adatok[hossz-1]=aktualis_karakter;
        hossz++;
        char* uj = new char[hossz];
        for (int i = 0; i < hossz-1; ++i) {
            uj[i] = beolvasott_adatok[i];
        }
        uj[hossz-1]=aktualis_karakter;
        delete[] beolvasott_adatok;
        beolvasott_adatok=uj;
    }while (aktualis_karakter!=EOF);
    //végére beszúrja a lezáró 0-t
    beolvasott_adatok[hossz-2]='\0';
    fclose(fp);
    return beolvasott_adatok;
}

int** matrixba_olvas(std::string fajlnev, int& n){
    char* adataim=fajlbeolvaso(fajlnev);
    if (adataim==NULL){
        throw "Nem sikerult megnyitni a fajlt!";
    }
    //ha a karaktertömb utolsó karaktere nem "\n", akkor hozzáfûzi, így minden sor "\n"-el lezárt
    if (adataim[strlen(adataim)-1]!='\n'){
        strcat(adataim,"\n");
    }
    if (adataim==NULL){
        throw "Nem sikerult adatokat beolvasni.";
    }
    int sorok_szama=0;
    int elso_sor_oszlopok_szama=0;
    int oszlopok_szama=0;
    int i=0;
    //megszámolja a sorokat
    while (adataim[i]!='\0' && adataim[i]!=EOF){
        if (adataim[i]=='\n')
            sorok_szama++;
        i++;
    }
    i=0;
    int akt=0;
    //megszámolja az oszlopok számát és ellenõrzi, hogy minden sorban ugyanannyi van-e
    while (adataim[i]!='\0' && adataim[i]!=EOF){
        if (adataim[i]=='\t' && adataim[i+1]!='\n' && adataim[i+1]!='\t')
            oszlopok_szama++;
        if (adataim[i]=='\n'){
            oszlopok_szama++;
            if (akt==0)
                elso_sor_oszlopok_szama=oszlopok_szama;
            if (oszlopok_szama!=elso_sor_oszlopok_szama){
                delete[] adataim;
                throw "hibas fajl: nem megfeleloek a matrix parameterei, nem ugyanannyi oszlopot tartalmaz minden sor";
            }
            oszlopok_szama=0;
            akt++;
        }
        i++;
    }
    //ellenõrzi, hogy négyzetes-e a mátrix
    if (elso_sor_oszlopok_szama!=sorok_szama){
        delete[] adataim;
        throw "hibas fajl: nem negyzetes a matrix";
    }
    oszlopok_szama=elso_sor_oszlopok_szama;
    int aktualis_sor=0;
    int aktualis_oszlop=0;
    char aktualis_karakter;
    int szamjegy;
    int k=0;
    //ellenõrzi, hogy csak 0 vagy 1 szerepel-e a mátrixban
    while (adataim[k]!='\0'){
        aktualis_karakter=adataim[k];
        if (aktualis_karakter!='\t' && aktualis_karakter!='\n'){
            szamjegy = aktualis_karakter - '0';
            if (szamjegy!=0 && szamjegy!=1){
                delete[] adataim;
                throw "hibas fajl: nem megfelelo karaktereket tartalmaz";
            }
        }
        k++;
    }
    //felépíti az nxn-es int tömböt
    int** matrix = new int*[sorok_szama];
    for (int i = 0; i < sorok_szama; ++i) {
        matrix[i] = new int[oszlopok_szama];
    }
    int j=0;
    while (adataim[j]!='\0'){
        aktualis_karakter=adataim[j];
        if (aktualis_karakter!='\t' && aktualis_karakter!='\n'){
            szamjegy = aktualis_karakter - '0';
            matrix[aktualis_sor][aktualis_oszlop] = szamjegy;
            aktualis_oszlop++;
        }
        if(aktualis_karakter=='\n'){
            aktualis_sor++;
            aktualis_oszlop=0;
        }
        j++;
    }
    n=sorok_szama;
    //ellenõrzi, hogy szimmetrikus-e a mátrix
    bool jo_matrix=true;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (matrix[i][j]!=matrix[j][i])
                jo_matrix=false;
        }
    }
    delete[] adataim;
    if (!jo_matrix){
        for (int i = 0; i < n; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        throw "hibas fajl: a matrix nem szimmetrikus";
    }
    return matrix;
}

