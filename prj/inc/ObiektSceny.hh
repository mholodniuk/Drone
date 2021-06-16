#pragma once

#include <string>
#include "Wektor3D.hh"

/*!
 * \file "ObiektSceny.hh"
 * \brief Ten plik zawiera definicję klasy ObiektSceny
 */

/*!
 * \brief modeluje pojecie Obiektu Sceny
 *
 * Zawiera definicję klasy ObiektSceny Uzywana jest, aby zdefiniowac
 * liste obiektow w klasie Scena. Jest rodzicem klasy Dron oraz
 * BrylaGeometryczna. Zdefiniowane sa metody wirtualne pozwalajace na
 * sprawdzenie czy obiekt jest dronem, czy dane miejsce jest zajete, oraz
 * metody pozwalajace odpowiednio identyfikowac obiekty
 */

class ObiektSceny
{
public:

    ObiektSceny() { }
    virtual ~ObiektSceny() { }
    virtual bool CzyDron() const { return false; }
    virtual bool CzyZajete(const Wektor3D& Polozenie_drona, double Promien) const = 0;

    virtual std::string Identyfikuj() const { return "obiekt sceny"; }
    virtual bool SprawdzID(unsigned int) const { return false; }
    virtual double PokazID() const { return 0; } 
    virtual const char* ZwrocNazwePlikuFinalnego() const { return "obiekt sceny"; }
};