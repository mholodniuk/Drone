#pragma once

#include "Vector3D.hh"
#include "lacze_do_gnuplota.hh"
#include <vector>
#include <iostream>
#include "Consts.hh"
#include <fstream>


/*!
 * \file "Sciezka.hh"
 * \brief Ten plik zawiera definicję klasy Sciezka
 */

/*!
 * \brief modeluje pojecie Sciezki lotu Drona
 *
 * Zawiera definicję klasy Sciezka. Uzywana jest glownie, aby
 * zwizualizowac sciezke, po ktorej bedzie lecial Dron.
 * Zdefiniowane sa metody pozwalajace na Obliczeniu wspolrzednych
 * punktow sciezki oraz pozwalajace na wyswietleniu drogi lotu
 * na Scenie.
 * 
 * \note Sciezka kazdego dron dodanegi lub istniejacego, bedzie zapisywana do tego samego pliku
 * To rozwiazanie sprawdzi sie, jezeli tylko jeden dron bedzie sie ruszal.
 * 
 */
class Path
{
    std::vector<Vector3D> Points;

public:

    //!\brief Metoda obliczajace punkty sciezki
    void CreatePath(const Vector3D& Startin_pos, double angle, double length);
    
    //!\brief Metody odpowiedzialne za wizualizacje
    void PlanPath(PzG::LaczeDoGNUPlota& Lacze);
    void ShowPath(std::ofstream& Plik) const;
    
    //!\brief Metoda czyszczaca sciezke
    void ClearPath(PzG::LaczeDoGNUPlota& Lacze);
    
    //!\brief Metoda obliczajace punkt koncowy sciezki
    Vector3D CalcNewPos(const Vector3D& Starting_pos, double angle, double length);

};