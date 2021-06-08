#pragma once

#include "Dron.hh"
#include "ObiektSceny.hh"
#include "GoraZDlugaGrania.hh"
#include "GoraZOstrymSzczytem.hh"
#include "Plaskowyz.hh"
#include "lacze_do_gnuplota.hh"
#include "BrylaGeometryczna.hh"
#include <list>
#include <memory>

/*!
 * \file Scena.hh
 * \brief Ten plik zawiera definicję klasy Scena
 */

/*!
 * \brief modeluje pojecie Sceny
 *
 * Zawiera definicję klasy Scena. Jej elementami sa:
 * LaczeDoGNUPlota, listy poszczegolnych jej elementow
 * (drony oraz przeszkody) oraz jeden wskaznik na aktualnie
 * aktywnego drona. Umozliwione jest dodawanie nowych przeszkod,
 * usuwanie ich, wybor drona oraz wykonanie jego lotu.
 */

class Scena
{
    PzG::LaczeDoGNUPlota Lacze;
    unsigned int lPrzeszkod;

    std::list<std::shared_ptr<ObiektSceny>> ListaObiektow;
    std::list<std::shared_ptr<BrylaGeometryczna>> ListaPrzeszkod;
    std::list<std::shared_ptr<Dron>> ListaDronow;
    std::shared_ptr<Dron> Dron_wybrany;

public:

    // konstruktor bezparametryczny
    Scena() { };

    // Metoda tworzaca uklad sceny
    void TworzScene();

    // Metody obslugujace dzialanie sceny
    void Menu(char& wybor);
    void WyswietlMenu();
    void WyborDrona();

    //Metody dodajace przeszkody
    void DodajGoreZDlugaGrania(unsigned int ID);
    void DodajGoreZOstrymSzczytem(unsigned int ID);
    void DodajPlaskowyz(unsigned int ID);
    void DodajPrzeszkode();

    //metoda ustawiajaca poczatkowy zestaw przeszkod
    void UstawPrzeszkody();

    //Metody usuwajace przeszkody
    void PokazPrzeszkody();
    void UsunPrzeszkode();

    //metody dodajace drony
    std::shared_ptr<Dron> DodajDrona(unsigned int ID, const Wektor3D& wek);
    void UstawDrony();

};