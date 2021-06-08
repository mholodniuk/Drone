#pragma once

#include "BrylaGeometryczna.hh"
#include "lacze_do_gnuplota.hh"

/*!
 * \file "GoraZDlugaGrania.hh"
 * \brief Ten plik zawiera definicję klasy GoraZDlugaGrania
 */

/*!
 * \brief modeluje pojecie Gory z podluzna grania
 *
 * Zawiera definicję klasy GoraZDlugaGrania. Metoda dziedziczy
 * publicznie po klasie BrylaGeometryczna. Atrybutami tej
 * klasy jest Polozenie, kat orientacji oraz id (?).
 * Umozliwione jest stworzenie obiektu tej klasy oraz
 * przesuniecie go we wskazane miejsce na scenie
 */
class GoraZDlugaGrania: public BrylaGeometryczna
{
    Wektor3D Polozenie;
    double kat_or;      //to na razie bezuzyteczne
    unsigned int id;

public:

    //!\brief Konstruktor bezparametryczny
    GoraZDlugaGrania();
    //!\brief Destruktor
    //~GoraZDlugaGrania() { std::cout <<" Usunieto Gore z dluga grania "<<std::endl; }

    //!\brief Metody pomocnicze
    Wektor3D UstawPolozenie(int x, int y) const;
    virtual bool SprawdzID(unsigned int _id) const override;
    virtual double PokazID() const override { return id; }

    //!\brief Metody Transformujace i obslugujace wyswietlanie gory na scenie
    void Transformacja(const Wektor3D& trans);
    bool TworzOpisGoryZDlugaGrania(const Wektor3D& Wek);
    std::string TworzNazweGoryZGrania(unsigned int ID);
    void TworzGoreZDlugaGrania(unsigned int ID, PzG::LaczeDoGNUPlota& Lacze);
    bool TransDoUklRodzica(const Wektor3D& Wek, PzG::LaczeDoGNUPlota& Lacze);

    virtual std::string Identyfikuj() const override;

    virtual bool CzyLadowac() const override { return true; }

};