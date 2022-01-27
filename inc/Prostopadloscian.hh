#pragma once

#include "BrylaGeometryczna.hh"

/*!
 * \file Prostopadloscian.hh
 * \brief Ten plik zawiera definicję klasy Prostopadloscian
 */

/*!
 * \brief modeluje pojecie Prostopadloscianu
 *
 * Zawiera definicję klasy Prostopadloscian. Dziedziczy ona
 * publicznie po klasie BrylaGeometryczna. Pozwala on na
 * stworzenie instancji obiektow klasy Prostopadloscian, ktorego 
 * glowna metoda jest metoda Transformujaca Do Ukladu Rodzica.
 * Atrybutami tej klasy jest Polozenie oraz kat orientacji
 */

class Cuboid: public Figure
{

public:

    Cuboid(std::string NazwaPilku, const Wektor3D& skala);
    void CalculateLocalPosition() override;

};