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

class Figure
{
protected:

    std::string FinalFileName;

    Wektor3D Scale;

    double Orientation_deg;

    Matrix3x3 GlobalOrientation;

    std::vector<Wektor3D> vertices;

    Wektor3D LocalCenter;

public:

    //!\brief Konstruktor bezparametryczny 
    explicit Figure(std::string NazwaPilku, const Wektor3D& skala, const Wektor3D& center);
    //!\brief Destruktor wirtualny
    virtual ~Figure() {}

    //!\brief Metoda zwracajaca nazwe pliku docelowego
    std::string ZwrocNazwePlikuFinalnego() const { return FinalFileName; }

    //!\brief Metody Transformujace
    void SetRotation(double kat) { Orientation_deg = kat; };
    void SetGlobalOrientation(const Matrix3x3& orient) { GlobalOrientation = orient; }
    void Rotate();
    void Transform(const Wektor3D& Trans);
    bool Draw();

    virtual void CalculateLocalPosition() = 0;

    //!\brief Metoda przesuwajaca Prostopadloscian wzgledem Drona
    void Translate(const Wektor3D& Wek);

};