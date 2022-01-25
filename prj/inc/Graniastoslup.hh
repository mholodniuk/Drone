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
    double Kat_Or;
    std::vector<Wektor3D> wierzcholki;

public:

    Graniastoslup(std::string NazwaPilku, const Wektor3D& skala);

    //!\brief Metody Transformujace
    void ZadajKatObrotu(double kat) { Kat_Or = kat; };
    void Obrot();
    void Transformacja(const Wektor3D& Trans);
    bool TworzOpisGraniastoslupu(const Wektor3D& Trans);

    //!\brief Metoda przesuwajaca Prostopadloscian wzgledem Drona
    bool TransDoUklRodzica(const Wektor3D& Wek);

    //virtual bool CzyZajete(const Wektor3D& Polozenie_drona, double Promien) const override;
};