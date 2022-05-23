#pragma once


#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include "Vector3D.hh"
#include "Matrix3x3.hh"
#include "Consts.hh"
 

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

    Vector3D Scale;

    double Orientation_deg;

    Matrix3x3 GlobalOrientation;

    std::vector<Vector3D> vertices;

    Vector3D Position;

public:

    //!\brief Konstruktor bezparametryczny 
    explicit Figure(std::string NazwaPilku, const Vector3D& skala, const Vector3D& center);
    //!\brief Destruktor wirtualny
    virtual ~Figure() {}

    //!\brief Metoda zwracajaca nazwe pliku docelowego
    std::string GetFileName() const { return FinalFileName; }

    //!\brief Metody Transformujace
    void SetRotation(double kat) { Orientation_deg = kat; };
    void SetGlobalOrientation(const Matrix3x3& orient) { GlobalOrientation = orient; }
    void Rotate();
    void Transform(const Vector3D& Trans);
    bool Draw();

    virtual void CalculateLocalPosition() = 0;

    //!\brief Metoda przesuwajaca Prostopadloscian wzgledem Drona
    void Translate(const Vector3D& Wek);

};