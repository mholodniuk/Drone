#pragma once


#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include "Wektor3D.hh"
#include "Macierz3x3.hh"
#include "Nazwy.hh"
 

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

class BrylaGeometryczna
{
protected:

    std::string NazwaPliku_Finalny;
    Wektor3D Skala;

public:

    //!\brief Konstruktor bezparametryczny 
    BrylaGeometryczna(std::string NazwaPilku, const Wektor3D& skala);
    //!\brief Destruktor wirtualny
    virtual ~BrylaGeometryczna() {}

    //!\brief Metoda zwracajaca nazwe pliku docelowego
    std::string ZwrocNazwePlikuFinalnego() const { return NazwaPliku_Finalny; }

};