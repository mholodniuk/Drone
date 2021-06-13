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

class Prostopadloscian: public BrylaGeometryczna
{
    Wektor3D Polozenie;
    double Kat_Or;

public:

    //!\brief Konstruktor bezparametryczny
    Prostopadloscian();

    //!\brief Metody Transformujace
    void ZadajKatObrotu(double kat);
    void Obrot();
    void Transformacja(const Wektor3D& Trans);
    bool TworzOpisProstopadloscianu(const Wektor3D& Trans);
    
    //!\brief Metoda przesuwajaca Prostopadloscian wzgledem Drona
    bool TransDoUklRodzica(const Wektor3D& Wek);

    //virtual bool CzyZajete(const Wektor3D& Polozenie_drona, double Promien) const override;
};