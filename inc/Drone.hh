#pragma once

#include "Vector3D.hh"
#include "Cuboid.hh"
#include "Prism.hh"
#include "SceneObject.hh"
#include <iostream>
#include <memory>
#include "lacze_do_gnuplota.hh"
#include "Path.hh"

/*!
 * \file Dron.hh
 * \brief Ten plik zawiera definicję klasy Dron
 */

/*!
 * \brief modeluje pojecie Drona
 *
 * Zawiera definicję klasy Dron. Jej skladowymi sa
 * cztery rotory(graniatoslupy), korpus(prostopadloscian),
 * id oraz kat orientacji. Pozwala on na
 * stworzenie obiektow klasy Dron, ktory jest wizualizacja
 * odpowiednio ulozonych skladowych. Zdefiniowane sa metody
 * tworzace drona, transformujace jego polozenie, 
 * planujace sciezke jego lotu oraz animujace jego lot
 */

class Drone: public SceneObject {

    Vector3D Position;
    double current_drone_rotation;
    std::shared_ptr<Cuboid> Body;
    std::shared_ptr<Prism> Rotors[4];
    Path path;
    
    unsigned int id;
    int single_step = 1;
    unsigned int DroneRadius = 10;

    //! \brief Metody generujace nazwy plikow
    inline std::string CreateRotorFileName(unsigned int id_Drona, unsigned int nrRotora);
    inline std::string CreateBodyFileName(unsigned int id_Drona);


public:

    //! \brief Metody Obliczajace i generujace sciezke lotu 
    void InitPath(PzG::LaczeDoGNUPlota& Lacze) const;
    void PlanPath(PzG::LaczeDoGNUPlota& Lacze);
    void CreatePath(const Vector3D& Polozenie_poacztkowe, double kat_skretu, double Dlugosc_lotu);
    void ClearPath(PzG::LaczeDoGNUPlota& Lacze) { path.ClearPath(Lacze); }
    void ShowPath(std::ofstream& Plik) const;

    //! \brief Metody Animujace ruch drona
    void Rotation(double kat_obrotu, PzG::LaczeDoGNUPlota& Lacze);
    void Fly(Vector3D& direction_vector, const double length, PzG::LaczeDoGNUPlota& Lacze);
    void FlyHorizontal(double dlugosc_lotu, PzG::LaczeDoGNUPlota& Lacze);
    void FlyVertical(double dlugosc_lout, PzG::LaczeDoGNUPlota& Lacze);
    void Wait(double czas, PzG::LaczeDoGNUPlota& Lacze);


    //! \brief Konstruktor bezparametryczny 
    explicit Drone(unsigned int id, PzG::LaczeDoGNUPlota& lacze);
    
    //!\brief Destrkutor wirtualny
    virtual ~Drone() { }

    //! \brief Metody zwracajace oraz ustawiajace kat orientacji oraz ID
    inline double GetRadius() { return DroneRadius; }
    inline double GetID() { return id; }
    virtual bool IsDrone() const override { return true; }

    //! \brief Metody zwracajace/wyswietlajace polozenie
    inline void PrintPosition() const { std::cout << Position[0] << " " <<Position[1] <<std::endl; }
    inline Vector3D GetPosition() const { return Position; }
    
    //!! \brief Metoda transformujaca 
    void Draw(PzG::LaczeDoGNUPlota&);
    void Translate(const Vector3D&);

    //! \brief Metoda zapisujaca polozenie poszczegolnych wierzcholkow
    void CalcAndSaveElements();

    //! \brief Metoda sprawdzajaca czy pod dronem jest wolne miejsce
    virtual bool IsOccupied(const Vector3D& Polozenie_drona, double Promien) const override;
    
    //! \brief Metody identyfikujace
    virtual std::string Identify() const override;
    virtual const char* GetFileName() const override { return std::string("Dron"+id).c_str(); }

};