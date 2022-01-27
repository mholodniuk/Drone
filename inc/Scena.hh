#pragma once

#include "Dron.hh"
#include "ObiektSceny.hh"
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
 * usuwanie ich, wybor drona oraz wykonanie jego lotu wraz z sprawdzeniem
 * czy miejsce ladowania jest wolne
 */

class Scena
{
    PzG::LaczeDoGNUPlota Lacze;
    unsigned int lPrzeszkod;

    std::list<std::shared_ptr<ObiektSceny>> ListaObiektow;
    std::list<std::shared_ptr<Drone>> ListaDronow;
    std::shared_ptr<Drone> Dron_wybrany;

public:

    //!\brief konstruktor bezparametryczny
    Scena();

    //!\brief Metoda tworzaca uklad sceny
    void TworzScene();

    //!\brief Metody obslugujace dzialanie sceny
    void Menu(char& wybor);
    void WyswietlMenu();
    void WyborDrona();

    //!\brief metody dodajace drony
    std::shared_ptr<Drone> DodajDrona(unsigned int ID, const Wektor3D& wek);
    void UstawDrony();
    void DodajDrona();
    void WyswietlDrony();

    //!\brief Metody animujace lot drona
    void LotDrona(std::shared_ptr<Drone> &Dr);

    //!!\brief Metody sprawdzajace czy obszar jest zajety
    bool CzyZajete(std::shared_ptr<Drone>& WDron);

};