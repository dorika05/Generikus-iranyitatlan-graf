#include <iostream>


#include "csucs.h"
#include "memtrace.h"
#include "gtest_lite.h"
#include "graf.h"
#include "graftarolo.h"
#include "beolvaso.h"



void tesztek(){
    TEST(Csucs, osszekot){
        Csucs csucs1(1);
        Csucs csucs2(2);
        csucs1.osszekot(&csucs2);
        EXPECT_EQ(&csucs2, csucs1.el_lekeres(0));
        EXPECT_EQ(&csucs1, csucs2.el_lekeres(0));
        EXPECT_TRUE(csucs1.el_lekeres(2)==NULL);
    }ENDM


    TEST(Graf, hozzaad){
        Graf graf1;
        Csucs csucs1(1);
        Csucs csucs2(2);
        graf1.hozzaad(&csucs1);
        graf1.hozzaad(&csucs2);
        EXPECT_EQ(&csucs1, graf1.csucs_lekeres(0));
        EXPECT_EQ(&csucs2, graf1.csucs_lekeres(1));
        EXPECT_TRUE(graf1.csucs_lekeres(2)==NULL);
    }ENDM


    TEST(Csucs, hurokel){
        Csucs csucs1(1);
        csucs1.osszekot(&csucs1);
        EXPECT_EQ(&csucs1, csucs1.el_lekeres(0));
        EXPECT_TRUE(csucs1.el_lekeres(1)==NULL);
    }ENDM


    TEST(Graf, csucsok_kiir){
        Graf graf1;
        Csucs csucs1(1);
        Csucs csucs2(2);
        Csucs csucs3(3);
        Csucs csucs4(4);
        Csucs csucs5(5);
        graf1.hozzaad(&csucs1);
        graf1.hozzaad(&csucs2);
        graf1.hozzaad(&csucs4);
        graf1.hozzaad(&csucs3);
        graf1.hozzaad(&csucs5);
        std::string szoveg=graf1.csucsok_kiir();
        EXPECT_TRUE (szoveg == "1, 2, 4, 3, 5");
    }ENDM



     TEST(Csucs, bfs_2csucs_osszefugg){
        Csucs csucs1(1);
        Csucs csucs2(2);
        csucs1.osszekot(&csucs2);
        Graf graf1;
        graf1.hozzaad(&csucs1);
        graf1.hozzaad(&csucs2);
        Graf* graf2 = graf1.bejar_bfs(&csucs1);
        std::string szoveg=graf2->csucsok_kiir();
        EXPECT_TRUE (szoveg == "1, 2");
        delete graf2;
    }ENDM


    TEST(Csucs, bfs_3csucs_nem_fugg_ossze){
        Csucs csucs1(1);
        Csucs csucs2(2);
        Csucs csucs3(3);
        csucs1.osszekot(&csucs2);
        Graf graf1;
        graf1.hozzaad(&csucs1);
        graf1.hozzaad(&csucs2);
        graf1.hozzaad(&csucs3);
        Graf* graf2 = graf1.bejar_bfs(&csucs1);
        std::string szoveg=graf2->csucsok_kiir();
        EXPECT_TRUE (szoveg == "1, 2");
        Graf* graf3 = graf1.bejar_bfs(&csucs2);
        szoveg=graf3->csucsok_kiir();
        EXPECT_TRUE (szoveg == "2, 1");
        Graf* graf4 = graf1.bejar_bfs(&csucs3);
        szoveg=graf4->csucsok_kiir();
        EXPECT_TRUE (szoveg == "3");
        delete graf2;
        delete graf3;
        delete graf4;
    }ENDM

    TEST(Csucs, komponensek_azonos_egyszer){
        Csucs csucs1(1);
        Csucs csucs2(2);
        csucs1.osszekot(&csucs2);
        Graf graf1;
        graf1.hozzaad(&csucs1);
        graf1.hozzaad(&csucs2);
        GrafTarolo* tarolo;
        tarolo = graf1.komponensek();
        EXPECT_EQ(1, tarolo->meret());
        delete tarolo;
    }ENDM

    TEST(Csucs, komponensek_3csucs_nem_fugg_ossze){
        Csucs csucs1(1);
        Csucs csucs2(2);
        Csucs csucs3(3);
        csucs1.osszekot(&csucs2);
        Graf graf1;
        graf1.hozzaad(&csucs1);
        graf1.hozzaad(&csucs2);
        graf1.hozzaad(&csucs3);
        GrafTarolo* tarolo;
        tarolo = graf1.komponensek();
        EXPECT_EQ(2, tarolo->meret());
        std::string szoveg=((*tarolo)[0])->csucsok_kiir();
        EXPECT_TRUE (szoveg == "1, 2");
        szoveg=((*tarolo)[1])->csucsok_kiir();
        EXPECT_TRUE (szoveg == "3");
        delete tarolo;
    }ENDM

    TEST(Graf, matrix_3csucs_nem_fugg_ossze){
        int matrix[3][3] = {
            {0, 1, 0},
            {1, 0, 0},
            {0, 0, 0}
        };
        Graf graf1;
        Csucs* csucsok[3];
        for (int i=0; i<3; i++){
            csucsok[i] = new Csucs(i);
            graf1.hozzaad(csucsok[i]);
        }
        for (int i=0; i<3; i++){
            for (int j=i; j<3; j++){
                if (matrix[i][j]==1){
                    Csucs* csucs1=graf1.csucs_lekeres(i);
                    Csucs* csucs2=graf1.csucs_lekeres(j);
                    csucs1->osszekot(csucs2);
                }
            }
        }
        GrafTarolo* tarolo;
        tarolo = graf1.komponensek();
        EXPECT_EQ(2, tarolo->meret());
        std::string szoveg=((*tarolo)[0])->csucsok_kiir();
        EXPECT_TRUE (szoveg == "0, 1");
        szoveg=((*tarolo)[1])->csucsok_kiir();
        EXPECT_TRUE (szoveg == "2");
        delete tarolo;
        for (int i=0; i<3; i++){
            delete csucsok[i];
        }
    }ENDM

    TEST(Graf, matrix_2komponens_6csucs_nem_fugg_ossze_fajlbol){
        std::string fajlnev = "matrix_2komponens_6csucs.txt";
        int n;
        int** matrix = matrixba_olvas(fajlnev, n);
        Graf graf1;
        Csucs* csucsok[n];
        for (int i=0; i<n; i++){
            csucsok[i] = new Csucs(i);
        }
        graf1.grafepito(matrix,csucsok,n);
        GrafTarolo* tarolo;
        tarolo = graf1.komponensek();
        EXPECT_EQ(2, tarolo->meret());
        std::string szoveg=((*tarolo)[0])->csucsok_kiir();
        EXPECT_TRUE (szoveg == "0, 1, 2, 3, 4");
        szoveg=((*tarolo)[1])->csucsok_kiir();
        EXPECT_TRUE (szoveg == "5");
        delete tarolo;
        for (int i = 0; i < n; i++) {
            delete csucsok[i];
        }
        for (int i = 0; i < n; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }ENDM

    TEST(Graf, matrix_teljes_graf_10csucsu_fajlbol){
        std::string fajlnev = "matrix_telejs_graf_10csucsu.txt";
        int n;
        int** matrix = matrixba_olvas(fajlnev, n);
        Graf graf1;
        Csucs* csucsok[n];
        for (int i=0; i<n; i++){
            csucsok[i] = new Csucs(i);
        }
        graf1.grafepito(matrix,csucsok,n);
        EXPECT_EQ(45, graf1.elek_szama());
        GrafTarolo* tarolo;
        tarolo = graf1.komponensek();
        EXPECT_EQ(1, tarolo->meret());
        std::string szoveg=((*tarolo)[0])->csucsok_kiir();
        EXPECT_TRUE (szoveg == "0, 1, 2, 3, 4, 5, 6, 7, 8, 9");
        delete tarolo;
        for (int i = 0; i < n; i++) {
            delete csucsok[i];
        }
        for (int i = 0; i < n; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }ENDM

    TEST(Graf, matrix_10csucsu_csak_hurokel_fajlbol){
        std::string fajlnev = "matrix_10csucsu_csak_hurokel.txt";
        int n;
        int** matrix = matrixba_olvas(fajlnev, n);
        Graf graf1;
        Csucs* csucsok[n];
        for (int i=0; i<n; i++){
            csucsok[i] = new Csucs(i);
        }
        graf1.grafepito(matrix,csucsok,n);
        EXPECT_EQ(10, graf1.elek_szama());
        GrafTarolo* tarolo;
        tarolo = graf1.komponensek();
        EXPECT_EQ(10, tarolo->meret());
        std::string szoveg=((*tarolo)[0])->csucsok_kiir();
        EXPECT_TRUE (szoveg == "0");
        szoveg=((*tarolo)[1])->csucsok_kiir();
        EXPECT_TRUE (szoveg == "1");
        szoveg=((*tarolo)[2])->csucsok_kiir();
        EXPECT_TRUE (szoveg == "2");
        szoveg=((*tarolo)[3])->csucsok_kiir();
        EXPECT_TRUE (szoveg == "3");
        szoveg=((*tarolo)[4])->csucsok_kiir();
        EXPECT_TRUE (szoveg == "4");
        szoveg=((*tarolo)[5])->csucsok_kiir();
        EXPECT_TRUE (szoveg == "5");
        szoveg=((*tarolo)[6])->csucsok_kiir();
        EXPECT_TRUE (szoveg == "6");
        szoveg=((*tarolo)[7])->csucsok_kiir();
        EXPECT_TRUE (szoveg == "7");
        szoveg=((*tarolo)[8])->csucsok_kiir();
        EXPECT_TRUE (szoveg == "8");
        szoveg=((*tarolo)[9])->csucsok_kiir();
        EXPECT_TRUE (szoveg == "9");
        delete tarolo;
        for (int i = 0; i < n; i++) {
            delete csucsok[i];
        }
        for (int i = 0; i < n; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }ENDM

    TEST(Graf, matrix_osszefuggo_10csucsu_fajlbol){
        std::string fajlnev = "matrix_osszefuggo_10csucs.txt";
        int n;
        int** matrix = matrixba_olvas(fajlnev, n);
        Graf graf1;
        Csucs* csucsok[n];
        for (int i=0; i<n; i++){
            csucsok[i] = new Csucs(i);
        }
        graf1.grafepito(matrix,csucsok,n);
        GrafTarolo* tarolo;
        tarolo = graf1.komponensek();
        EXPECT_EQ(1, tarolo->meret());
        std::string szoveg=((*tarolo)[0])->csucsok_kiir();
        EXPECT_TRUE (szoveg == "0, 1, 2, 3, 4, 5, 6, 7, 8, 9");
        delete tarolo;
        for (int i = 0; i < n; i++) {
            delete csucsok[i];
        }
        for (int i = 0; i < n; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }ENDM

    TEST(Graf, matrix_hibas_nem_oszlopok_fajlbol){
        std::string fajlnev = "matrix_hibas_oszlopok.txt";
        int n;
        try{
            matrixba_olvas(fajlnev, n);
        }catch(char const* e){
            EXPECT_STREQ("hibas fajl: nem megfeleloek a matrix parameterei, nem ugyanannyi oszlopot tartalmaz minden sor", e);
        }
    }ENDM

    TEST(Graf, matrix_hibas_nem_negyzetes_fajlbol){
        std::string fajlnev = "matrix_hibas_nem_negyzetes.txt";
        int n;
        try{
            matrixba_olvas(fajlnev, n);
        }catch(char const* e){
            EXPECT_STREQ("hibas fajl: nem negyzetes a matrix", e);
        }
    }ENDM

    TEST(Graf, matrix_hibas_karakter_fajlbol){
        std::string fajlnev = "matrix_hibas_karakter.txt";
        int n;
        try{
            matrixba_olvas(fajlnev, n);
        }catch(char const* e){
            EXPECT_STREQ("hibas fajl: nem megfelelo karaktereket tartalmaz", e);
        }
    }ENDM

    TEST(Graf, matrix_hibas_nem_szimmetrikus_fajlbol){
        std::string fajlnev = "matrix_hibas_nem_szimmetrikus.txt";
        int n;
        try{
            matrixba_olvas(fajlnev, n);
        }catch(char const* e){
            EXPECT_STREQ("hibas fajl: a matrix nem szimmetrikus", e);
        }
    }ENDM

}
