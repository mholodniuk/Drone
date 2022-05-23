#pragma once

#include "Figure.hh"

/*!
 * \file Graniastoslup.hh
 * \brief Ten plik zawiera definicję klasy Graniastoslup
 */

/*!
 * \brief modeluje pojecie Graniastoslupa
 *
 * Zawiera definicję klasy Graniastoslup. Dziedziczy ona
 * publicznie po klasie BrylaGeometryczna. Pozwala on na
 * stworzenie instancji obiektow klasy Graniastoslup, ktorego 
 * glowna metoda jest metoda Transformujaca Do Ukladu Rodzica.
 * Atrybutami tej klasy jest Polozenie oraz kat orientacji
 */

class Prism: public Figure
{
    

public:

    Prism(std::string, const Vector3D&, const Vector3D& cnetr);
    void CalculateLocalPosition() override;
};