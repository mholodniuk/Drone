#pragma once

#include "Wektor3D.hh"
#include "Prostopadloscian.hh"
#include "Graniastoslup.hh"
#include "ObiektSceny.hh"
#include <iostream>
#include <memory>
#include "lacze_do_gnuplota.hh"
#include "Sciezka.hh"

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

class Drone: public SceneObject
{
    Wektor3D Position;
    double current_drone_rotation;
    std::shared_ptr<Cuboid> Body;
    std::shared_ptr<Prism> Rotors[4];
    Sciezka path;
    
    unsigned int id;
    int pojedynczy_krok = 2;
    unsigned int Promien_drona = 10;

    //!\brief Metody ustawiajace poszczegolne elementy
    void CalcAndSaveBody();
    void CalcAndSaveRotors();
    void SpinRotors();
    void SetRotors();

    //! \brief Metoda przesuwajaca drona o zadany wektor przesuniecia
    void Move(const Wektor3D& Wek) { Position += Wek; }

    //! \brief Metoda przemieszczajaca drona do zadanego wektora polozenia
    void ChangePosition(const Wektor3D& nPolozenie) { Position = nPolozenie; }

    //! \brief Metody generujace nazwy plikow
    inline std::string CreateRotorFileName(unsigned int id_Drona, unsigned int nrRotora);
    inline std::string CreateBodyFileName(unsigned int id_Drona);

public:

    //! \brief Konstruktor bezparametryczny 
    Drone(unsigned int id, PzG::LaczeDoGNUPlota& lacze);
    
    //!\brief Destrkutor wirtualny
    virtual ~Drone() { }

    //! \brief Metody zwracajace oraz ustawiajace kat orientacji oraz ID
    inline double GetRotatation_deg() { return current_drone_rotation; }
    inline double GetRadius() { return Promien_drona; }
    inline double GetID() { return id; }
    inline void SetRotateion_deg(double kat) { current_drone_rotation = kat; }
    virtual bool IsDrone() const override { return true; }

    //! \brief Metody zwracajace/wyswietlajace polozenie
    inline void PrintPosition() const { std::cout << Position[0] << " " <<Position[1] <<std::endl; }
    inline Wektor3D GetPosition() const { return Position; }
    
    //!! \brief Metoda transformujaca 
    void Translate(const Wektor3D& Wek, PzG::LaczeDoGNUPlota& Lacze);

    //! \brief Metoda zapisujaca polozenie poszczegolnych wierzcholkow
    void CalcAndSavePostion();

    //! \brief Metody Obliczajace i generujace sciezke lotu 
    void InitPath(PzG::LaczeDoGNUPlota& Lacze) const;
    void PlanujSciezke(PzG::LaczeDoGNUPlota& Lacze);
    void PlanPath(const Wektor3D& Polozenie_poacztkowe, double kat_skretu, double Dlugosc_lotu);
    void ClearPath(PzG::LaczeDoGNUPlota& Lacze) { path.WyczyscSciezke(Lacze); }
    void ShowPath(std::ofstream& Plik) const;

    //! \brief Metody Animujace ruch drona
    void Obrot(double kat_obrotu, PzG::LaczeDoGNUPlota& Lacze);
    void Lec(Wektor3D& Wek_kierunkowy, const double dlugosc_lotu, PzG::LaczeDoGNUPlota& Lacze);
    void LotDoPrzodu(double dlugosc_lotu, PzG::LaczeDoGNUPlota& Lacze);
    void LotPionowy(double dlugosc_lout, PzG::LaczeDoGNUPlota& Lacze);
    void Czekaj(double czas, PzG::LaczeDoGNUPlota& Lacze);

    //! \brief Metoda sprawdzajaca czy pod dronem jest wolne miejsce
    virtual bool IsOccupied(const Wektor3D& Polozenie_drona, double Promien) const override;
    
    //! \brief Metody identyfikujace
    virtual std::string Identify() const override;
    virtual const char* GetFileName() const override;

};