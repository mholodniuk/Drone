#pragma once

#include "Wektor3D.hh"
#include "lacze_do_gnuplota.hh"
#include <vector>
#include <iostream>
#include "Nazwy.hh"
#include <fstream>


/*!
 * \file "Sciezka.hh"
 * \brief Ten plik zawiera definicję klasy Sciezka
 */

/*!
 * \brief modeluje pojecie Sciezki lotu Drona
 *
 * Zawiera definicję klasy Sciezka. Uzywana jest glownie, aby
 * zwizualizowac sciezke, po ktorej bedzie lecial Dron.
 * Zdefiniowane sa metody pozwalajace na Obliczeniu wspolrzednych
 * punktow sciezki oraz pozwalajace na wyswietleniu drogi lotu
 * na Scenie.
 * 
 * \note Sciezka kazdego dron dodanegi lub istniejacego, bedzie zapisywana do tego samego pliku
 * To rozwiazanie sprawdzi sie, jezeli tylko jeden dron bedzie sie ruszal.
 * 
 */
class Sciezka
{
    std::vector<Wektor3D> ZestawPunktow;

public:

    //!\brief Metoda obliczajace punkty sciezki
    void UstalSciezke(const Wektor3D& Polozenie_poczatkowe, double kat_skretu_st, double dlugosc);
    
    //!\brief Metody odpowiedzialne za wizualizacje
    void PlanujSciezke(PzG::LaczeDoGNUPlota& Lacze);
    void WyswietlSciezke(std::ofstream& Plik) const;
    
    //!\brief Metoda czyszczaca sciezke
    void WyczyscSciezke(PzG::LaczeDoGNUPlota& Lacze);
    
    //!\brief Metoda obliczajace punkt koncowy sciezki
    Wektor3D ObliczNoweWsp(const Wektor3D& Polozenie_poczatkowe, double kat_skretu_st, double dlugosc);

};