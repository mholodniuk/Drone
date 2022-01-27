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

class Prism: public Figure
{
    double Orientation_deg;
    std::vector<Wektor3D> vertices;

public:

    Prism(std::string, const Wektor3D&);

    //!\brief Metody Transformujace
    void SetRotation(double kat) { Orientation_deg = kat; };
    void Rotate();
    void Transform(const Wektor3D& Trans);
    bool SaveToFile(const Wektor3D& Trans);

    void CalculateLocalPosition();

    //!\brief Metoda przesuwajaca Prostopadloscian wzgledem Drona
    bool Translate(const Wektor3D& Wek);

    //virtual bool CzyZajete(const Wektor3D& Polozenie_drona, double Promien) const override;
};