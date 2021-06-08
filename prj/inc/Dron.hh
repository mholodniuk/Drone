#pragma once

#include "Wektor3D.hh"
#include "Prostopadloscian.hh"
#include "Graniastoslup.hh"
#include "ObiektSceny.hh"
#include <iostream>
#include "lacze_do_gnuplota.hh"

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

class Dron: public ObiektSceny
{
  Wektor3D Polozenie;
  double Kat_OrDrona;
  Prostopadloscian KorpusDrona;
  Graniastoslup RotorDrona[4];
  unsigned int id;
  int pojedynczy_krok = 1;

  void Oblicz_i_Zapisz_WspKorpusu();
  void Oblicz_i_Zapisz_WspRotorow();
  // Metoda przesuwajaca drona o zadany wektor przesuniecia
  void PrzesunDrona(const Wektor3D& Wek) { Polozenie += Wek; }
  // Metoda przemieszczajaca drona do zadanego wektora polozenia
  void ZmienPolozenieDrona(const Wektor3D& nPolozenie) { Polozenie = nPolozenie; }

public:

  // Konstruktor bezparametryczny 
  Dron() { Kat_OrDrona = 0; }
  //Destrkutor
  virtual ~Dron() { }

  // Metody zwracajace kat orientacji oraz ID
  double ZwrocKat_st() { return Kat_OrDrona; }
  double ZwrocID() { return id; }
  virtual bool CzyDron() const override { return true; }

  // Metody generujace nazwy plikow
  std::string TworzNazweRotora(unsigned int id_Drona, unsigned int nrRotora);
  std::string TworzNazweKorpusu(unsigned int id_Drona);

  // Metody zwracajace/wyswietlajace polozenie
  void PodajWspolrzedne() const;
  Wektor3D ZwrocPolozenie() const;

  //Metoda tworzaca zestaw plikow ze wspolrzednymi
  void TworzDrona(unsigned int ID, PzG::LaczeDoGNUPlota & Lacze);
  
  //! Metoda transformujaca 
  void TransDoUklRodzica(const Wektor3D& Wek, PzG::LaczeDoGNUPlota& Lacze);

  //Metoda zapisujaca polozenie poszczegolnych wierzcholkow
  void Oblicz_i_ZapiszWspDrona();

  //Metody Ocliczajace i generujace sciezke lotu 
  void PlanujPoczatkowaSciezke(std::vector<Wektor3D>& PunktySciezki, PzG::LaczeDoGNUPlota& Lacze) const;
  std::vector<Wektor3D> UstalSciezke(double kat_skretu, double Dlugosc_lotu);
  Wektor3D ObliczNoweWsp(double kat_skretu, double Dlugosc_lotu) const;

  //Metody Animujace ruch drona
  void Obrot(double kat_obrotu, PzG::LaczeDoGNUPlota& Lacze);
  void Lot(PzG::LaczeDoGNUPlota& Lacze);
  void Lec(Wektor3D& Wek_kierunkowy, const double dlugosc_lotu, PzG::LaczeDoGNUPlota& Lacze);
  void LotDoPrzodu(double dlugosc_lotu, double kat_skretu,  PzG::LaczeDoGNUPlota& Lacze);
  void LotPionowy(double dlugosc_lout, PzG::LaczeDoGNUPlota& Lacze);

  //Metoda sprawdzajaca czy pod dronem jest wolne miejsce
  virtual bool CzyLadowac() const override;

};