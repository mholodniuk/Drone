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
    double Orientation_deg;
    std::vector<Wektor3D> vertices;

public:

    Cuboid(std::string NazwaPilku, const Wektor3D& skala);
    void CalculateLocalPosition();

    //!\brief Metody Transformujace
    inline void SetRotation(double kat) { Orientation_deg = kat; }
    void Rotate();
    void Transform(const Wektor3D& Trans);
    bool SaveToFile(const Wektor3D& Trans);
    
    //!\brief Metoda przesuwajaca Prostopadloscian wzgledem Drona
    bool Translate(const Wektor3D& Wek);

    //virtual bool CzyZajete(const Wektor3D& Polozenie_drona, double Promien) const override;
};