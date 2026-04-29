#ifndef BEOLVASO_H
#define BEOLVASO_H

#include "memtrace.h"

char* fajlbeolvaso(std::string fajlnev); //egy karaktertömbbe beolvassa a fájl tartalmát
int** matrixba_olvas(std::string fajlnev, int& n); //a karaktertömbbõl egy nxn-es int tömböt készít

#endif
