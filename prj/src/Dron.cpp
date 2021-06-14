#include "Dron.hh"
#include "Nazwy.hh"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <unistd.h>
#include <chrono>
#include <thread>

#define BLAD_OBLICZEN 1e-8


Dron::Dron()
{
  Kat_OrDrona = 0;
  KorpusDrona = std::make_shared<Prostopadloscian>();
  for(std::shared_ptr<Graniastoslup>& Rotor : RotorDrona)
  {
    Rotor = std::make_shared<Graniastoslup>();
  }
}

/*!
 * \brief Metoda tworzaca nazwe rotora
 * 
 * W zaleznosci od ID drona i nr rotora tworzony jest
 * odpowiedni plik wynikowy
 * 
 * \param[in] id_drona - nr drona na scenie
 * \param[in] nrRotota - nr rotora drona
 * 
 * \return string - bedacy odpowiednio sformatowana nazwa pliku
 * 
 */
std::string Dron::TworzNazweRotora(unsigned int id_Drona, unsigned int nrRotora)
{
  std::stringstream StrmWy;

  StrmWy << "dat/Dron"<<id_Drona<<"/PlikWlasciwy_Dron"<<id_Drona<<"_Rotor"<<nrRotora+1<<".dat";

  return StrmWy.str();
}

/*!
 * \brief Metoda tworzaca nazwe korpusu
 * 
 * W zaleznosci od ID drona tworzony jest
 * odpowiedni plik wynikowy
 * 
 * \param[in] id_drona - nr drona na scenie
 * 
 * \return string - bedacy odpowiednio sformatowana nazwa pliku
 * 
 */
std::string Dron::TworzNazweKorpusu(unsigned int id_Drona)
{
  std::ostringstream StrmWy;

  StrmWy << "dat/Dron"<<id_Drona<<"/PlikWlasciwy_Dron"<<id_Drona<<"_Korpus.dat";

  return StrmWy.str();
}

/*!
 * \brief Metoda Podajaca wspolrzedne drona
 */
void Dron::PodajWspolrzedne() const
{
  std::cout<<"Wspolrzedna x: "<<Polozenie[0]<<std::endl;
  std::cout<<"Wspolrzedna y: "<<Polozenie[1]<<std::endl;
}

/*!
 * \brief Metoda zwracajaca aktualnie polozenie drona
 */
Wektor3D Dron::ZwrocPolozenie() const
{
  return Polozenie;
}

std::string Dron::Identyfikuj() const
{
  std::ostringstream Obiekt;

  Obiekt << "Dron (" << Polozenie[0] << ", " << Polozenie[1] <<")";

  return Obiekt.str();
}

/*!
 * \brief Metoda tworzaca odpowiedni zestaw plikow wynikowych
 * 
 * W zaleznosci od ID dronat worzony jest
 * odpowiedni zestaw plikow wynikowych
 * 
 * \param[in] ID - nr drona na scenie
 * \param[in] Lacze 
 * 
 */
void Dron::TworzDrona(unsigned int ID, PzG::LaczeDoGNUPlota & Lacze)
{
  std::string NazwaPliku;
  id = ID;

  for(int i=0; i<4; ++i)
  {
    NazwaPliku = TworzNazweRotora(ID, i);
    RotorDrona[i]->UstawNazwaPlikuWlasciwego(NazwaPliku.c_str());
    Lacze.DodajNazwePliku(NazwaPliku.c_str());
  }
  NazwaPliku = TworzNazweKorpusu(ID);
  KorpusDrona->UstawNazwaPlikuWlasciwego(NazwaPliku.c_str());
  Lacze.DodajNazwePliku(NazwaPliku.c_str());
}

/*!
 * \brief Obliczajaca wspolrzedne korpusu drona
 * 
 * Zadawana jest odpowiednia skala, kat oraz przesuniecie
 * wzgledem rodzica
 * 
 */
void Dron::Oblicz_i_Zapisz_WspKorpusu()
{
  Wektor3D Translacja = {0, 0, 2};
  Wektor3D w = Polozenie + Translacja;
  Wektor3D SkalaKorpusu = {10, 8, 4};
  KorpusDrona->ZadajKatObrotu(Kat_OrDrona);
  KorpusDrona->UstawSkale(SkalaKorpusu);
  
  KorpusDrona->TransDoUklRodzica(w);
}

/*!
 * \brief Obliczajaca wspolrzedne rotorow drona
 * 
 * Zadawana jest odpowiednia skala, kat oraz przesuniecie
 * wzgledem rodzica
 * 
 */
void Dron::Oblicz_i_Zapisz_WspRotorow()
{
  static double kat_obr = 0;
  Macierz3x3 MacierzRot;
  double Rad = Kat_OrDrona*M_PI/180;
  MacierzRot.ObrotZ(Rad);

  Wektor3D TranslacjaRotorLewyPrzedni = {5, 4, 5};
  TranslacjaRotorLewyPrzedni = MacierzRot * TranslacjaRotorLewyPrzedni;
  Wektor3D w1 = Polozenie + TranslacjaRotorLewyPrzedni;
  
  Wektor3D TranslacjaRotorPrawyPrzedni = {5, -4, 5};
  TranslacjaRotorPrawyPrzedni = MacierzRot * TranslacjaRotorPrawyPrzedni;
  Wektor3D w2 = Polozenie + TranslacjaRotorPrawyPrzedni;

  Wektor3D TranslacjaRotorLewyTylny = {-5, 4, 5};
  TranslacjaRotorLewyTylny = MacierzRot * TranslacjaRotorLewyTylny;
  Wektor3D w3 = Polozenie + TranslacjaRotorLewyTylny;

  Wektor3D TranslacjaRotorPrawyTylny = {-5, -4, 5};
  TranslacjaRotorPrawyTylny = MacierzRot * TranslacjaRotorPrawyTylny;
  Wektor3D w4 = Polozenie + TranslacjaRotorPrawyTylny;

  Wektor3D SkalaRotora = {8,8,4};
  
  for(int idx=0; idx<ILOSC_ROTOROW; ++idx)
  {
    RotorDrona[idx]->UstawSkale(SkalaRotora);
  }

  RotorDrona[0]->ZadajKatObrotu(kat_obr);
  RotorDrona[1]->ZadajKatObrotu(-kat_obr);
  RotorDrona[2]->ZadajKatObrotu(-kat_obr);
  RotorDrona[3]->ZadajKatObrotu(kat_obr);

  RotorDrona[0]->TransDoUklRodzica(w1);
  RotorDrona[1]->TransDoUklRodzica(w2);  
  RotorDrona[2]->TransDoUklRodzica(w3);
  RotorDrona[3]->TransDoUklRodzica(w4);

  kat_obr+=15;
}

/*!
 * \brief Obliczajaca wspolrzedne drona
 */
void Dron::Oblicz_i_ZapiszWspDrona()
{
  Oblicz_i_Zapisz_WspKorpusu();
  Oblicz_i_Zapisz_WspRotorow();
}

/*!
 * \brief Metoda przesuwajaca Drona wzgledem sceny
 * 
 * Tutaj dokonywane jest ostateczne przesuniecie o odpowiedni
 * Wektor i rysowanie drona
 * 
 * \param[in] Wek - Wektor Translacji
 * \param[in] lacze
 * 
 */
void Dron::TransDoUklRodzica(const Wektor3D& Wek, PzG::LaczeDoGNUPlota & Lacze)
{
  Polozenie += Wek;
  
  if(!KorpusDrona->TransDoUklRodzica(Polozenie)) std::cerr<<"Nastapil blad podczas ruchu"<<std::endl;
  for(unsigned int idx=0; idx<ILOSC_ROTOROW; ++idx)
  {
    if(!RotorDrona[idx]->TransDoUklRodzica(Polozenie)) std::cerr<<"Nastapil blad podczas ruchu"<<std::endl;
  }
  Oblicz_i_ZapiszWspDrona();
  Lacze.Rysuj();
}

/*!
 * \brief Metoda realizujaca lot drona
 *
 * \param[in] Wek_kierunkowy - jednostkowy wektor kierunkowy
 * \param[in] dlugosc_lotu - odleglosc lotu drona
 * \param[in] Lacze - lacze do gnuplota
 * 
 */
void Dron::Lec(Wektor3D& Wek_kierunkowy, const double dlugosc_lotu, PzG::LaczeDoGNUPlota& Lacze)
{
  assert(fabs(Wek_kierunkowy.ObliczDlugosc()-1) < BLAD_OBLICZEN);
  //pojedynczy_krok = 2;
  Wektor3D Wek_czastkowy = Wek_kierunkowy * pojedynczy_krok;
  Wektor3D Polozenie_startowe = Polozenie;
  double PozostalaDlugosc = dlugosc_lotu;

  PozostalaDlugosc -= pojedynczy_krok;
  while(PozostalaDlugosc > 0)
  {
    TransDoUklRodzica(Wek_czastkowy, Lacze);
    usleep(100000);
    Lacze.Rysuj();
    PozostalaDlugosc -= pojedynczy_krok;
  }
  Wektor3D WekPrzesuniecia = Wek_kierunkowy*dlugosc_lotu;
  ZmienPolozenieDrona(Polozenie_startowe + WekPrzesuniecia);
  TransDoUklRodzica({0,0,0}, Lacze);
}

/*!
 * \brief Metoda realizujaca lot do przodu drona
 *
 * \param[in] dlugosc_lotu - odleglosc lotu drona
 * 
 * \pre dlugosc_lotu musi byc liczba dodatnia
 * 
 */
void Dron::LotDoPrzodu(double dlugosc_lotu, PzG::LaczeDoGNUPlota& Lacze)
{

  Wektor3D Kierunek_lotu = {1, 0, 0};
  Macierz3x3 MacierzRot;

  double Rad = Kat_OrDrona*M_PI/180;

  MacierzRot.ObrotZ(Rad);
  Kierunek_lotu = MacierzRot * Kierunek_lotu;

  Lec(Kierunek_lotu, fabs(dlugosc_lotu), Lacze);
}

void Dron::LotPionowy(double dlugosc_lotu, PzG::LaczeDoGNUPlota& Lacze)
{
  double kierunek = 0;
  if(dlugosc_lotu>0) kierunek =  1;
  if(dlugosc_lotu<0) kierunek = -1;

  Wektor3D Kierunek_lotu = {0,0,kierunek};

  Lec(Kierunek_lotu, fabs(dlugosc_lotu), Lacze);
}

/*!
 * \brief Metoda realizujaca obrot drona    COS JEST NIE TAK
 * 
 * \pre kat obrotu musi byc podany w stopniach
 * 
 * \param[in] kat_obrotu - kat o jaki ma obrocic sie dron
 * \param[in] Lacze 
 * 
 */
void Dron::Obrot(double kat_obrotu, PzG::LaczeDoGNUPlota & Lacze)
{
  if(kat_obrotu>0)
  {
    for(; Kat_OrDrona <= kat_obrotu; Kat_OrDrona += 1)
    {
      Oblicz_i_ZapiszWspDrona();
      usleep(100000);
      Lacze.Rysuj();
    }
    Kat_OrDrona -= 1;
  }
  else
  {
    for(; Kat_OrDrona >= kat_obrotu; Kat_OrDrona -= 1)
    {
      Oblicz_i_ZapiszWspDrona();
      usleep(100000);
      Lacze.Rysuj();
    }
    Kat_OrDrona += 1;
  }
}

void Dron::Czekaj(double czas_sek, PzG::LaczeDoGNUPlota& Lacze)
{
  double licznik = 0;
  while(true)
  {
    Oblicz_i_ZapiszWspDrona();
    usleep(100000);
    Lacze.Rysuj();
    licznik += 1;
    //std::cout<< licznik/10 << std::endl;
    if(licznik/10 >= czas_sek) break;
  }
}

/*!
 * \brief Metoda obliczajca wspolrzedne drona
 *
 * Metoda obliczajca wspolrzedne drona po zadaniu odpowienich
 * wartosci dlugosci lotu i katu skretu
 * 
 * \pre dlugosc lotu musi byc dodatnia
 * \pre kat skretu musi byc podany w stopniach
 * 
 * \param[in] dlugosc_lotu
 * \param[in] kat_skretu 
 * 
 * \return Wsp - nowe (finalne) polozenie drona
 * 
 */
Wektor3D Dron::ObliczNoweWsp(double kat_skretu, double Dlugosc_lotu) const
{
  Wektor3D Wsp;
  double kat_rad = kat_skretu*M_PI/180;
  Wsp[0] = Dlugosc_lotu * cos(kat_rad);
  Wsp[1] = Dlugosc_lotu * sin(kat_rad);

  Wsp += Polozenie;

  return Wsp;
}

/*!
 * \brief Metoda ustalajaca sciezke lotu drona
 *
 * Metoda obliczajca  odpowiednie punkty sciezki lotu, a nastepnie
 * zapisuje je do kontenera vector<>
 *
 * \pre dlugosc lotu musi byc dodatnia
 * \pre kat skretu musi byc podany w stopniach
 * 
 * \param[in] dlugosc_lotu
 * \param[in] kat_skretu 
 * 
 * \return Sciezka - kontener z kolejnymi wektorami3D sciezki ruchu
 * 
 */
std::vector<Wektor3D> Dron::UstalSciezke(const Wektor3D& Polozenie_poczatkowe, double kat_skretu, double Dlugosc_lotu)
{
  std::vector<Wektor3D> Sciezka;
  Wektor3D pomoc;
  Macierz3x3 MacierzRot;

  std::cout<<std::endl<<std::endl<<"Planuje sciezke ruchu drona..."<<std::endl;

  Sciezka.push_back(Polozenie_poczatkowe);
  pomoc = ZwrocPolozenie();
  pomoc[2] += 80;
  Sciezka.push_back(pomoc);
  pomoc = ObliczNoweWsp(kat_skretu, Dlugosc_lotu);
  pomoc[2] += 80;
  Sciezka.push_back(pomoc);
  pomoc[2] -= 80;
  Sciezka.push_back(pomoc);

  return Sciezka;
}

/*!
 * \brief Metoda planujaca sciezke lotu drona
 *
 * Metoda kolejno zapisuje punkty sciezki do pliku
 * wyjsciowego w celu wizualizacji ich w gnuplocie
 * 
 * \param[in] PunktySciezki - kontener z kolejnymi punktami sciezki
 * \param[in] Lacze
 * 
 */
void Dron::PlanujSciezke(std::vector<Wektor3D>& PunktySciezki, PzG::LaczeDoGNUPlota& Lacze) const
{
  std::ofstream Plik_Trasa(PLIK_TRASY_PRZELOTU);
  if(!Plik_Trasa.is_open())
  {
    std::cerr<<"Nie udalo sie otworzyc pliku"<<PLIK_TRASY_PRZELOTU<<std::endl;
  }
  for(auto i = PunktySciezki.cbegin(); i != PunktySciezki.cend(); ++i)
  {
    Plik_Trasa<<*i;
  }
  //Lacze.DodajNazwePliku(PLIK_TRASY_PRZELOTU);
  Lacze.Rysuj();
  Plik_Trasa.close();
}

bool Dron::CzyZajete(const Wektor3D& Polozenie_drona, double Promien) const
{
  double odleglosc;
  Wektor<2> Polozenie_drona_2D = Polozenie_drona;
  Wektor<2> Polozenie_drona_this = Polozenie;

  odleglosc = (Polozenie_drona_2D - Polozenie_drona_this).ObliczDlugosc();

  if(odleglosc > Promien) return false;

  //std::cout<<"zajete przez drona"<<std::endl;
  return true;
}