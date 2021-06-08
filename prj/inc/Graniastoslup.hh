#pragma once

#include "BrylaGeometryczna.hh"

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

class Graniastoslup: public BrylaGeometryczna
{
    Wektor3D Polozenie;
    double Kat_Or;

public:

    Graniastoslup();

    //!\brief Metody Transformujace
    void ZadajKatObrotu(double kat);
    void Obrot();
    void Transformacja(const Wektor3D& Trans);
    bool TworzOpisGraniastoslupu(const Wektor3D& Trans);

    //!\brief Metoda przesuwajaca Prostopadloscian wzgledem Drona
    bool TransDoUklRodzica(const Wektor3D& Wek);
};