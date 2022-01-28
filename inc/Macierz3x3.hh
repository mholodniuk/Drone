#pragma once

#include "Wektor3D.hh"


/*!
 * \file Macierz3x3.hh
 * \brief Ten plik zawiera definicję klasy Macierz3x3
 */

#define WYMIAR 3

class Matrix3x3
{
    double wart[WYMIAR][WYMIAR];

public:

    enum class Axis
        {
            OX /** Oś OX układu współrzędnych */,
            OY /** Oś OY układu współrzędnych */,
            OZ /** Oś OZ układu współrzędnych */
        };

    /*!
    * \brief Konstruktory bezparamentryczny (macierz jednostkowa) i parametryczny 
    */
    Matrix3x3();
    Matrix3x3(int);
    Matrix3x3(Axis, double);

    /*!
    * \brief operator indeksowania dla odczytu
    * sprawdzane jest czy "przekroczono" zakresu macierzy
    */
    double operator () (int wiersz, int kolumna) const
    {
        assert(wiersz >= 0 && wiersz < WYMIAR);
        assert((kolumna >= 0 && kolumna < WYMIAR));
        
        return wart[wiersz][kolumna];
    }
    /*!
    * \brief operator indeksowania dla wczytania
    * sprawdzane jest czy "przekroczono" zakresu macierzy
    */
    double &operator () (int wiersz, int kolumna)
    {
        assert(wiersz >= 0 && wiersz <= WYMIAR);
        assert((kolumna >= 0 && kolumna <= WYMIAR));
        
        return wart[wiersz][kolumna];
    }

    void ObrotZ(double kat);
    
    /*!
    * \brief Operatory poszczegolnych dzialan
    */
    Wektor3D operator*(const Wektor3D& Wektor) const;
    Matrix3x3 operator*(const Matrix3x3& Macierz) const;
    
};