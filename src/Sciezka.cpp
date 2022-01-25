#include "../inc/Sciezka.hh"

/*!
 * \brief Metoda obliczajca wspolrzedne
 *
 * Metoda obliczajca wspolrzedne po zadaniu odpowienich
 * wartosci dlugosci lotu i katu skretu oraz polozenia
 * poczatkowego
 * 
 * \pre dlugosc lotu musi byc dodatnia
 * \pre kat skretu musi byc podany w stopniach
 * 
 * \param[in] dlugosc_lotu
 * \param[in] kat_skretu 
 * 
 * \return Wsp - nowe (finalne) polozenie
 * 
 */
Wektor3D Sciezka::ObliczNoweWsp(const Wektor3D& Polozenie_poczatkowe, double kat_skretu, double Dlugosc_lotu)
{
  Wektor3D Wsp;
  double kat_rad = kat_skretu*M_PI/180;
  Wsp[0] = Dlugosc_lotu * cos(kat_rad);
  Wsp[1] = Dlugosc_lotu * sin(kat_rad);

  Wsp += Polozenie_poczatkowe;

  return Wsp;
}

/*!
 * \brief Metoda ustalajaca sciezke lotu
 *
 * Metoda obliczajca  odpowiednie punkty sciezki lotu, a nastepnie
 * zapisuje je
 *
 * \pre dlugosc lotu musi byc dodatnia
 * \pre kat skretu musi byc podany w stopniach
 * 
 * \param[in] Polozenie_Poczatkowe
 * \param[in] dlugosc_lotu
 * \param[in] kat_skretu 
 * 
 * 
 */
void Sciezka::UstalSciezke(const Wektor3D& Polozenie_poczatkowe, double kat_skretu_st, double Dlugosc_lotu)
{
  Wektor3D pomoc;

  ZestawPunktow.push_back(Polozenie_poczatkowe);
  pomoc = Polozenie_poczatkowe;
  pomoc[2] += 80;
  ZestawPunktow.push_back(pomoc);
  pomoc = ObliczNoweWsp(Polozenie_poczatkowe, kat_skretu_st, Dlugosc_lotu);
  pomoc[2] += 80;
  ZestawPunktow.push_back(pomoc);
  pomoc[2] -= 80;
  ZestawPunktow.push_back(pomoc);
}

/*!
 * \brief Metoda czyszczaca sciezke lotu drona
 *
 * Kontener z Wektorami3D zostaje wyczysczony, a plik trasy
 * sciezki zostaje chwilowo wymazany
 * 
 * \param[in] LaczeDoGNUPlota
 * 
 */
void Sciezka::WyczyscSciezke(PzG::LaczeDoGNUPlota& Lacze)
{
  ZestawPunktow.clear();
  std::ofstream Plik_Trasa(PLIK_TRASY_PRZELOTU);
  
  if(!Plik_Trasa.is_open())
  {
    std::cerr << "Nie udalo sie otworzyc pliku" << PLIK_TRASY_PRZELOTU << std::endl;
  }
  Plik_Trasa << " ";

  Lacze.Rysuj();
  Plik_Trasa.close();
}

/*!
 * \brief Metoda zapisujaca wspolrzedne sciezki do pliku
 *
 * Metoda kolejno zapisuje punkty sciezki do pliku
 * wyjsciowego w celu wizualizacji ich w gnuplocie
 * 
 * \pre Strumien plikowy musi zostac uprzednio zainicjalizowany
 * 
 * \param[in] Plik - strumien plikowy docelowy
 * 
 */
void Sciezka::WyswietlSciezke(std::ofstream& Plik) const
{
  for(auto i = ZestawPunktow.cbegin(); i != ZestawPunktow.cend(); ++i)
  {
    Plik << *i;
  }
}

/*!
 * \brief Metoda planujaca sciezke lotu drona
 *
 * Metoda otwiera plik zapisu, a nastepnie zapisuje wspolrzedne
 * do niego, zeby potem je zwizualizowac na scenie
 * 
 * \param[in] LaczeDoGNUPlota
 * 
 */
void Sciezka::PlanujSciezke(PzG::LaczeDoGNUPlota& Lacze)
{
  std::ofstream Plik_Trasa(PLIK_TRASY_PRZELOTU);
  
  if(!Plik_Trasa.is_open())
  {
    std::cerr << "Nie udalo sie otworzyc pliku" << PLIK_TRASY_PRZELOTU << std::endl;
  }
  WyswietlSciezke(Plik_Trasa);

  Lacze.Rysuj();
  Plik_Trasa.close();
}