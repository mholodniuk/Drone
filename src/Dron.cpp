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

  Wektor3D BodyScale = {10, 8, 4};
  Wektor3D RotorScale = {8,8,4};

  std::string file_name = CreateBodyFileName(ID);

  Body = std::make_shared<Cuboid>(file_name, BodyScale);
  Body->SetRotation(current_drone_rotation);
  lacze.DodajNazwePliku(file_name.c_str());
  
  int idx = -1;
  for(std::shared_ptr<Prism>& Rotor : Rotors) {
	file_name = CreateRotorFileName(ID, ++idx);
	Rotor = std::make_shared<Prism>(file_name, BodyScale);
	lacze.DodajNazwePliku(file_name.c_str());
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
std::string Drone::CreateRotorFileName(unsigned int id_Drona, unsigned int nrRotora)
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
std::string Drone::CreateBodyFileName(unsigned int id_Drona)
{
  std::ostringstream StrmWy;

  StrmWy << "dat/Dron"<<id_Drona<<"/PlikWlasciwy_Dron"<<id_Drona<<"_Korpus.dat";

  return StrmWy.str();
}

std::string Drone::Identify() const
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
const char* Drone::GetFileName() const
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
void Drone::CalcAndSaveBody()
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
void Drone::SpinRotors()
{
  static double kat_obr = 0;

  for(int i=0; i<4; ++i) {
	double temp = i==0 || i==3 ? kat_obr : -kat_obr; 
	Rotors[i]->SetRotation(temp);
  }
  kat_obr+=15;
}

/*!
 * \brief Metoda obliczajaca polozenie rotorow
 * 
 * Obliczane jest polozenie kazdego z rotorow wzgledem
 * srodka polozenia drona
 * 
 */
void Drone::SetRotors(double kat_rad)
{
  Macierz3x3 MacierzRot;
  MacierzRot.ObrotZ(kat_rad);
  std::vector<Wektor3D> wektory;

  for(int i=0; i<4; ++i) {
	Wektor3D w({(double)(i>1 ? -5 : 5), (double)(i==1 || i==3 ? 4 : -4), 5});
	w = MacierzRot * w;
	w += Position;
	Rotors[i]->Translate(w);
  }
}

/*!
 * \brief Obliczajaca wspolrzedne rotorow drona
 * 
 * Zadawana jest odpowiednia skala, kat oraz przesuniecie
 * wzgledem rodzica
 * 
 */
void Drone::CalcAndSaveRotors()
{
  double Rad = current_drone_rotation*M_PI/180;
  SetRotors(Rad);
  SpinRotors();
}

/*!
 * \brief Obliczajaca wspolrzedne drona
 */
void Drone::CalcAndSavePostion()
{
  CalcAndSaveBody();
  CalcAndSaveRotors();
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
void Drone::Translate(const Wektor3D& Wek, PzG::LaczeDoGNUPlota& Lacze)
{
  Position += Wek;
  if(!Body->Translate(Position)) std::cerr<<"Nastapil blad podczas ruchu"<<std::endl;
  for(unsigned int idx=0; idx<ILOSC_ROTOROW; ++idx) {
	  if(!Rotors[idx]->Translate(Position)) std::cerr<<"Nastapil blad podczas ruchu"<<std::endl;
  }
  CalcAndSavePostion();
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
	Translate(Wek_czastkowy, Lacze);
	usleep(delay*1'000);
	Lacze.Rysuj();
	PozostalaDlugosc -= pojedynczy_krok;
  }
  Wektor3D WekPrzesuniecia = Wek_kierunkowy*dlugosc_lotu;
  ZmienPolozenieDrona(Polozenie_startowe + WekPrzesuniecia);
  Translate({0,0,0}, Lacze);
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
	  CalcAndSavePostion();
	  usleep(100000);
	  Lacze.Rysuj();
	}
	current_drone_rotation -= 1;
  }
  else
  {
	for(; current_drone_rotation >= kat_obrotu; current_drone_rotation -= 1)
	{
	  CalcAndSavePostion();
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
	CalcAndSavePostion();
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