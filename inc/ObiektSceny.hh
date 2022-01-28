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
 * wszystkich przeszkod (Plaskowyz, gora z dluga grania oraz gora z ostrym szczytem). 
 * Zdefiniowane sa metody wirtualne pozwalajace na
 * sprawdzenie czy obiekt jest dronem, czy dane miejsce jest zajete, oraz
 * metody pozwalajace odpowiednio identyfikowac obiekty
 */

class SceneObject
{
public:

    //!\brief Konstruktor i wirtualny destruktor
    SceneObject() { }
    virtual ~SceneObject() { }

    //!\brief Metoda sprawdzajaca czy dany obiekt jest obiektem klasy Dron
    virtual bool IsDrone() const { return false; }

    //!\brief Abstrakcyjna metoda sprawdzajca zajetosc obszaru
    virtual bool IsOccupied(const Wektor3D& Polozenie_drona, double Promien) const = 0;

    //!\brief Metody pozwalajce na identyfikacje obiektu
    virtual std::string Identify() const { return "obiekt sceny"; }
    virtual bool SprawdzID(unsigned int) const { return false; }
    virtual double PokazID() const { return 0; } 
    virtual const char* GetFileName() const = 0;
};