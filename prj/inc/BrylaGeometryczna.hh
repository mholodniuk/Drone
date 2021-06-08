#pragma once

#include <string>
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
 * \brief Ten plik zawiera definicję klasy Prostopadloscian
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
    
    //!\brief Metoda Ustawiajaca Nazwe Pliku Docelowego
    void UstawNazwaPlikuWlasciwego(const char* NazwaPliku);
    
    //!\brief Metoda ustawiajaca skale bryly
    Wektor3D UstawSkale(const Wektor3D& skala);

    virtual std::string Identyfikuj() const { return "Bryla Geometryczna"; }
    virtual bool SprawdzID(unsigned int) const { return true; }
    virtual double PokazID() const { return 0; }
    const char* ZwrocNazwePlikuFinalnego() const { return NazwaPliku_Finalny.c_str(); }

    virtual bool CzyLadowac() const override { return false; }
};