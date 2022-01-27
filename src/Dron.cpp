#include "../inc/Dron.hh"
#include "../inc/Nazwy.hh"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <unistd.h>
#include <chrono>
#include <thread>

#define BLAD_OBLICZEN 1e-8


Drone::Drone(unsigned int ID, PzG::LaczeDoGNUPlota& lacze)
 : Position({0,0,0}), current_drone_rotation(0), id(ID) {

  Wektor3D SkalaKorpusu = {10, 8, 4};
  Wektor3D SkalaRotorow = {8,8,4};

  std::string NazwaPliku = TworzNazweKorpusu(ID);

  Body = std::make_shared<Cuboid>(NazwaPliku, SkalaKorpusu);
  Body->SetRotation(current_drone_rotation);
  lacze.DodajNazwePliku(NazwaPliku.c_str());
  
  int idx = -1;
  for(std::shared_ptr<Prism>& Rotor : Rotors)
  {
    NazwaPliku = TworzNazweRotora(ID, ++idx);
    Rotor = std::make_shared<Prism>(NazwaPliku, SkalaKorpusu);
    lacze.DodajNazwePliku(NazwaPliku.c_str());
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
std::string Drone::TworzNazweRotora(unsigned int id_Drona, unsigned int nrRotora)
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
std::string Drone::TworzNazweKorpusu(unsigned int id_Drona)
{
  std::ostringstream StrmWy;

  StrmWy << "dat/Dron"<<id_Drona<<"/PlikWlasciwy_Dron"<<id_Drona<<"_Korpus.dat";

  return StrmWy.str();
}

/*!
 * \brief Metoda Podajaca wspolrzedne drona
 */
void Drone::PodajWspolrzedne() const
{
  std::cout<<"Wspolrzedna x: "<<Position[0]<<std::endl;
  std::cout<<"Wspolrzedna y: "<<Position[1]<<std::endl;
  std::cout<<"Wspolrzedna z: "<<Position[2]<<std::endl;
}


std::string Drone::Identyfikuj() const
{
  std::ostringstream Obiekt;

  Obiekt << "Dron (" << Position[0] << ", " << Position[1] <<")";

  return Obiekt.str();
}

/*!
 * \brief Metoda zwracajca nazwe folderu docelowego
 * 
 * \note Zamiast nazwy pliku, metoda podaje nazwe folderu, w ktorym znajduje zestwa plikow
 * 
 * \return NazwaPlikuFinalnego
 */
const char* Drone::ZwrocNazwePlikuFinalnego() const
{
  std::string NazwaFolderu = "Dron" + id;
  return NazwaFolderu.c_str(); 
}

/*!
 * \brief Obliczajaca wspolrzedne korpusu drona
 * 
 * Zadawana jest odpowiednia skala, kat oraz przesuniecie
 * wzgledem rodzica
 * 
 */
void Drone::Oblicz_i_Zapisz_WspKorpusu()
{
  Wektor3D Translacja = {0, 0, 2};
  Wektor3D w = Position + Translacja;
  Body->SetRotation(current_drone_rotation);
  
  Body->Translate(Position);
}

/*!
 * \brief Metoda realizujaca obrot rotorow wokol wlasnej osi
 * 
 * Co klatke rotory obracaja sie o 15 stopni
 * 
 */
void Drone::ZakrecRotorami()
{
  static double kat_obr = 0;

  Rotors[0]->SetRotation(kat_obr);
  Rotors[1]->SetRotation(-kat_obr);
  Rotors[2]->SetRotation(-kat_obr);
  Rotors[3]->SetRotation(kat_obr);

  kat_obr+=15;
}

/*!
 * \brief Metoda obliczajaca polozenie rotorow
 * 
 * Obliczane jest polozenie kazdego z rotorow wzgledem
 * srodka polozenia drona
 * 
 */
void Drone::UstawRotory(double kat_rad)
{
  Macierz3x3 MacierzRot;
  MacierzRot.ObrotZ(kat_rad);

  std::vector<Wektor3D> wektory;

  Wektor3D TranslacjaRotorLewyPrzedni = {5, 4, 5};
  TranslacjaRotorLewyPrzedni = MacierzRot * TranslacjaRotorLewyPrzedni;
  Wektor3D w1 = TranslacjaRotorLewyPrzedni + Position;


  
  Wektor3D TranslacjaRotorPrawyPrzedni = {5, -4, 5};
  TranslacjaRotorPrawyPrzedni = MacierzRot * TranslacjaRotorPrawyPrzedni;
  Wektor3D w2 = TranslacjaRotorPrawyPrzedni + Position;


  Wektor3D TranslacjaRotorLewyTylny = {-5, 4, 5};
  TranslacjaRotorLewyTylny = MacierzRot * TranslacjaRotorLewyTylny;
  Wektor3D w3 = TranslacjaRotorLewyTylny + Position;


  Wektor3D TranslacjaRotorPrawyTylny = {-5, -4, 5};
  TranslacjaRotorPrawyTylny = MacierzRot * TranslacjaRotorPrawyTylny;
  Wektor3D w4 = TranslacjaRotorPrawyTylny + Position;


  Rotors[0]->Translate(w1);
  Rotors[1]->Translate(w2);  
  Rotors[2]->Translate(w3);
  Rotors[3]->Translate(w4);
}

/*!
 * \brief Obliczajaca wspolrzedne rotorow drona
 * 
 * Zadawana jest odpowiednia skala, kat oraz przesuniecie
 * wzgledem rodzica
 * 
 */
void Drone::Oblicz_i_Zapisz_WspRotorow()
{

  double Rad = current_drone_rotation*M_PI/180;

  UstawRotory(Rad);
  ZakrecRotorami();
}

/*!
 * \brief Obliczajaca wspolrzedne drona
 */
void Drone::Oblicz_i_ZapiszWspDrona()
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
void Drone::TransDoUklRodzica(const Wektor3D& Wek, PzG::LaczeDoGNUPlota& Lacze)
{
  Position += Wek;
  
  if(!Body->Translate(Position)) std::cerr<<"Nastapil blad podczas ruchu"<<std::endl;
  for(unsigned int idx=0; idx<ILOSC_ROTOROW; ++idx)
  {
    if(!Rotors[idx]->Translate(Position)) std::cerr<<"Nastapil blad podczas ruchu"<<std::endl;
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
void Drone::Lec(Wektor3D& Wek_kierunkowy, const double dlugosc_lotu, PzG::LaczeDoGNUPlota& Lacze)
{
  const double czestotliwosc = 24;
  const u_int16_t delay = 1000./czestotliwosc;
  assert(fabs(Wek_kierunkowy.ObliczDlugosc()-1) < BLAD_OBLICZEN);
  //pojedynczy_krok = 2;
  Wektor3D Wek_czastkowy = Wek_kierunkowy * pojedynczy_krok;
  Wektor3D Polozenie_startowe = Position;
  double PozostalaDlugosc = dlugosc_lotu;

  PozostalaDlugosc -= pojedynczy_krok;
  while(PozostalaDlugosc > 0)
  {
    TransDoUklRodzica(Wek_czastkowy, Lacze);
    usleep(delay*1'000);
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
 * \param[in] LaczeDoGNUPlota
 * 
 * \pre dlugosc_lotu musi byc liczba dodatnia
 * 
 */
void Drone::LotDoPrzodu(double dlugosc_lotu, PzG::LaczeDoGNUPlota& Lacze)
{

  Wektor3D Kierunek_lotu = {1, 0, 0};
  Macierz3x3 MacierzRot;

  double Rad = current_drone_rotation*M_PI/180;

  MacierzRot.ObrotZ(Rad);
  Kierunek_lotu = MacierzRot * Kierunek_lotu;

  Lec(Kierunek_lotu, fabs(dlugosc_lotu), Lacze);
}

/*!
 * \brief Metoda realizujaca lot pionowy drona
 *
 * \param[in] dlugosc_lotu - odleglosc lotu drona
 * \param[in] LaczeDoGNUPlota
 * 
 */
void Drone::LotPionowy(double dlugosc_lotu, PzG::LaczeDoGNUPlota& Lacze)
{
  double kierunek = 0;
  if(dlugosc_lotu>0) kierunek =  1;
  if(dlugosc_lotu<0) kierunek = -1;

  Wektor3D Kierunek_lotu = {0,0,kierunek};

  Lec(Kierunek_lotu, fabs(dlugosc_lotu), Lacze);
}

/*!
 * \brief Metoda realizujaca obrot drona
 * 
 * \pre kat obrotu musi byc podany w stopniach
 * 
 * \param[in] kat_obrotu - kat o jaki ma obrocic sie dron
 * \param[in] Lacze 
 * 
 */
void Drone::Obrot(double kat_obrotu, PzG::LaczeDoGNUPlota & Lacze)
{
  kat_obrotu += current_drone_rotation;

  if(kat_obrotu>0)
  {
    for(; current_drone_rotation <= kat_obrotu; current_drone_rotation += 1)
    {
      Oblicz_i_ZapiszWspDrona();
      usleep(100000);
      Lacze.Rysuj();
    }
    current_drone_rotation -= 1;
  }
  else
  {
    for(; current_drone_rotation >= kat_obrotu; current_drone_rotation -= 1)
    {
      Oblicz_i_ZapiszWspDrona();
      usleep(100000);
      Lacze.Rysuj();
    }
    current_drone_rotation += 1;
  }
}

/*!
 * \brief Metoda animujaca lot w miejscu
 *
 * Dron bedzie unosil sie w powietrzu przez zadana ilosc czasu
 * 
 * \param[in] czas_sek - czas w sekundach, jak dlugo drona ma sie unosic
 * \param[in] LaczeDoGNUPlota
 * 
 */
void Drone::Czekaj(double czas_sek, PzG::LaczeDoGNUPlota& Lacze)
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
 * \brief Metoda ustalajaca sciezke lotu drona
 * 
 * Wykorzystywany do tego jest argument typu Sciezka
 * i jej jego metoda \e UstalSciezke po uprzednim
 * odpowiednim zsumowaniu katow
 * 
 */
void Drone::UstalSciezke(const Wektor3D& Polozenie_poczatkowe, double kat_skretu, double Dlugosc_lotu)
{
  kat_skretu += current_drone_rotation;
  path.UstalSciezke(Polozenie_poczatkowe, kat_skretu, Dlugosc_lotu);
}

/*!
 * \brief Metoda czyszczaca sciezke lotu drona
 *
 * Wykorzystywany do tego jest argument typu Sciezka
 * i jego metoda \e WyczyscSciezke
 * 
 */
void Drone::WyczyscSciezke(PzG::LaczeDoGNUPlota& Lacze)
{
  path.WyczyscSciezke(Lacze);
}

/*!
 * \brief Metoda planujaca sciezke lotu drona
 *
 * Wykorzystywany do tego jest argument typu Sciezka
 * i jego metoda \e PlanujSciezke
 * 
 */
void Drone::PlanujSciezke(PzG::LaczeDoGNUPlota& Lacze)
{
  path.PlanujSciezke(Lacze);
}

/*!
 * \brief Metoda wyswietlajaca Sciezke lotu
 *
 * Wykorzystywany do tego jest argument typu Sciezka
 * i jego metoda \e WyswietlSciezke
 * 
 */
void Drone::WyswietlSciezke(std::ofstream& Plik) const
{
  path.WyswietlSciezke(Plik);
}

/*!
 * \brief Metoda inicjalizujaca sciezke lotu drona
 *
 * Do plikow sledzonych przez GNUPlota dodawany jest plik
 * zawierajacy sciezke
 */
void Drone::InicjalizujSciezke(PzG::LaczeDoGNUPlota& Lacze) const
{
  Lacze.DodajNazwePliku(PLIK_TRASY_PRZELOTU);
}

/*!
 * \brief Metoda sprawdzajaca czy dane polozenie jest zajete przez obiekt klasy Dron
 *
 * Sprawdzane jest czy odleglosc miedzy srodkami dronow jest wieksza od
 * dwoch promieni - czy drona na siebie nie nachodza
 * 
 * \param[in] Polozenie_drona - wektor polozenia aktualnie poruszanego drona
 * \param[in] Promien - promien aktualnie poruszanego drona
 * 
 * \retval false - jesli dane miejsce nie jest zajete przez obiekt klasy Dron
 * \retval true - jesli dane miejsce jest zajete przez obiekt klasy Dron
 * 
 */
bool Drone::CzyZajete(const Wektor3D& Polozenie_drona, double Promien) const
{
  double odleglosc;
  Wektor<2> Polozenie_drona_2D = Polozenie_drona;
  Wektor<2> Polozenie_drona_this = Position;

  odleglosc = (Polozenie_drona_2D - Polozenie_drona_this).ObliczDlugosc();

  if(odleglosc > 2 * Promien) return false;

  return true;
}