#pragma once


#include <iostream>
#include <cmath>
#include <fstream>
#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include "Nazwy.hh"
#include "ObiektSceny.hh"

#define WYMIAR 3

/*!
 * \file "BrylaGeometryczna.hh"
 * \brief Ten plik zawiera definicję klasy BrylaGeometryczna
 */

/*!
 * \brief modeluje pojecie Bryly geometrycznej
 *
 * Zawiera definicję klasy BrylaGeometryczna. Uzywana jest jako 
 * rodzic klas Prostopadloscian oraz Graniastolup. Atrybutami tej
 * klasy sa nazwy plikow: wzorcowego i finalnego oraz skala bryly.
 * Umozliwione jest ustawienie nazwy pliku docelowego oraz ustawienie
 * skali bryly
 */

class BrylaGeometryczna: public ObiektSceny
{
protected:

    std::string NazwaPliku_Wzorcowy;
    std::string NazwaPliku_Finalny;
    Wektor3D Skala;

public:

    //!\brief Konstruktor bezparametryczny 
    BrylaGeometryczna() { };
    //!\brief Destruktor wirtualny
    virtual ~BrylaGeometryczna() { }
    
    //!\brief Metoda Ustawiajaca Nazwe Pliku Docelowego
    void UstawNazwaPlikuWlasciwego(const char* NazwaPliku);
    
    //!\brief Metoda ustawiajaca skale bryly
    Wektor3D UstawSkale(const Wektor3D& skala);

    //!\brief Metoda zwracajaca nazwe pliku docelowego
    virtual const char* ZwrocNazwePlikuFinalnego() const override { return NazwaPliku_Finalny.c_str(); }

    //!\brief Metoda sprawdzajaca czy obszar zajmowany przez bryle jest zajety
    virtual bool CzyZajete(const Wektor3D& Polozenie_drona, double Promien) const override;
};