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

class Drone: public ObiektSceny
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
  void Oblicz_i_Zapisz_WspKorpusu();
  void Oblicz_i_Zapisz_WspRotorow();
  void ZakrecRotorami();
  void UstawRotory(double kat_rad);

  //! \brief Metoda przesuwajaca drona o zadany wektor przesuniecia
  void PrzesunDrona(const Wektor3D& Wek) { Position += Wek; }

  //! \brief Metoda przemieszczajaca drona do zadanego wektora polozenia
  void ZmienPolozenieDrona(const Wektor3D& nPolozenie) { Position = nPolozenie; }

  //! \brief Metody generujace nazwy plikow
  inline std::string TworzNazweRotora(unsigned int id_Drona, unsigned int nrRotora);
  inline std::string TworzNazweKorpusu(unsigned int id_Drona);

public:

  //! \brief Konstruktor bezparametryczny 
  Drone(unsigned int id, PzG::LaczeDoGNUPlota& lacze);
  
  //!\brief Destrkutor wirtualny
  virtual ~Drone() { }

  //! \brief Metody zwracajace oraz ustawiajace kat orientacji oraz ID
  inline double ZwrocKat_st() { return current_drone_rotation; }
  inline double ZwrocPromien() { return Promien_drona; }
  inline double ZwrocID() { return id; }
  inline void ZadajKat_st(double kat) { current_drone_rotation = kat; }
  virtual bool CzyDron() const override { return true; }

  //! \brief Metody zwracajace/wyswietlajace polozenie
  void PodajWspolrzedne() const;
  inline Wektor3D ZwrocPolozenie() const { return Position; }

  //! \brief Metoda tworzaca zestaw plikow ze wspolrzednymi
  void TworzDrona(unsigned int ID, PzG::LaczeDoGNUPlota & Lacze);
  
  //!! \brief Metoda transformujaca 
  void TransDoUklRodzica(const Wektor3D& Wek, PzG::LaczeDoGNUPlota& Lacze);

  //! \brief Metoda zapisujaca polozenie poszczegolnych wierzcholkow
  void Oblicz_i_ZapiszWspDrona();

  //! \brief Metody Obliczajace i generujace sciezke lotu 
  void InicjalizujSciezke(PzG::LaczeDoGNUPlota& Lacze) const;
  void PlanujSciezke(PzG::LaczeDoGNUPlota& Lacze);
  void UstalSciezke(const Wektor3D& Polozenie_poacztkowe, double kat_skretu, double Dlugosc_lotu);
  void WyczyscSciezke(PzG::LaczeDoGNUPlota& Lacze);
  void WyswietlSciezke(std::ofstream& Plik) const;

  //! \brief Metody Animujace ruch drona
  void Obrot(double kat_obrotu, PzG::LaczeDoGNUPlota& Lacze);
  void Lec(Wektor3D& Wek_kierunkowy, const double dlugosc_lotu, PzG::LaczeDoGNUPlota& Lacze);
  void LotDoPrzodu(double dlugosc_lotu, PzG::LaczeDoGNUPlota& Lacze);
  void LotPionowy(double dlugosc_lout, PzG::LaczeDoGNUPlota& Lacze);
  void Czekaj(double czas, PzG::LaczeDoGNUPlota& Lacze);

  //! \brief Metoda sprawdzajaca czy pod dronem jest wolne miejsce
  virtual bool CzyZajete(const Wektor3D& Polozenie_drona, double Promien) const override;
  
  //! \brief Metody identyfikujace
  virtual std::string Identyfikuj() const override;
  virtual const char* ZwrocNazwePlikuFinalnego() const override;

};