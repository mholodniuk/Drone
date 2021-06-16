#pragma once

#include "Wektor3D.hh"
#include "lacze_do_gnuplota.hh"
#include <vector>
#include <iostream>
#include "Nazwy.hh"
#include <fstream>


class Sciezka
{
    std::vector<Wektor3D> sciezka;

public:

    void InicjalizujPlik(PzG::LaczeDoGNUPlota&);
    void UstalSciezke(const Wektor3D& Polozenie_poczatkowe, double kat_skretu_st, double dlugosc);
    void PlanujSciezke(PzG::LaczeDoGNUPlota& Lacze);
    void WyczyscSciezke(PzG::LaczeDoGNUPlota& Lacze);
    void WyswietlSciezke(std::ofstream& Plik) const;
    Wektor3D ObliczNoweWsp(const Wektor3D& Polozenie_poczatkowe, double kat_skretu_st, double dlugosc);

};