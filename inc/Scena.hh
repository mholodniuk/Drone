#pragma once

#include "Dron.hh"
#include "ObiektSceny.hh"
#include "lacze_do_gnuplota.hh"
#include "BrylaGeometryczna.hh"
#include "Przeszkody.hh"
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

class Scene
{
    PzG::LaczeDoGNUPlota Lacze;
    unsigned int ObstacleCounter;

    std::list<std::shared_ptr<SceneObject>> ObjectList;
    std::list<std::shared_ptr<Drone>> DroneList;
    std::shared_ptr<Drone> ChosenDrone;

public:

    //!\brief konstruktor bezparametryczny
    Scene();

    //!\brief Metody obslugujace dzialanie sceny
    void Menu(char& wybor);
    void WyswietlMenu();
    void WyborDrona();

    //!\brief metody dodajace drony
    std::shared_ptr<Drone> AddDrone(unsigned int ID, const Wektor3D& wek);
    void AddDrone();
    void PrintDrones();

    void AddRidge();
    void AddPyramid();
    void AddPlateau();

    //!\brief Metody animujace lot drona
    void Animate(std::shared_ptr<Drone> &Dr);

    //!!\brief Metody sprawdzajace czy obszar jest zajety
    bool IsOccupied(std::shared_ptr<Drone>& WDron);

};