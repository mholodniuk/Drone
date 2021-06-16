#include "Sciezka.hh"

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
Wektor3D Sciezka::ObliczNoweWsp(const Wektor3D& Polozenie_poczatkowe, double kat_skretu, double Dlugosc_lotu)
{
  Wektor3D Wsp;
  double kat_rad = kat_skretu*M_PI/180;
  Wsp[0] = Dlugosc_lotu * cos(kat_rad);
  Wsp[1] = Dlugosc_lotu * sin(kat_rad);

  Wsp += Polozenie_poczatkowe;

  return Wsp;
}

void Sciezka::UstalSciezke(const Wektor3D& Polozenie_poczatkowe, double kat_skretu_st, double Dlugosc_lotu)
{
  Wektor3D pomoc;

  sciezka.push_back(Polozenie_poczatkowe);
  pomoc = Polozenie_poczatkowe;
  pomoc[2] += 80;
  sciezka.push_back(pomoc);
  pomoc = ObliczNoweWsp(Polozenie_poczatkowe, kat_skretu_st, Dlugosc_lotu);
  pomoc[2] += 80;
  sciezka.push_back(pomoc);
  pomoc[2] -= 80;
  sciezka.push_back(pomoc);
}

void Sciezka::WyczyscSciezke(PzG::LaczeDoGNUPlota& Lacze)
{
  sciezka.clear();
  std::ofstream Plik_Trasa(PLIK_TRASY_PRZELOTU);
  
  if(!Plik_Trasa.is_open())
  {
    std::cerr << "Nie udalo sie otworzyc pliku" << PLIK_TRASY_PRZELOTU << std::endl;
  }
  Plik_Trasa << " ";

  Lacze.Rysuj();
  Plik_Trasa.close();
}

void Sciezka::WyswietlSciezke(std::ofstream& Plik) const
{
  for(auto i = sciezka.cbegin(); i != sciezka.cend(); ++i)
  {
    Plik << *i;
  }
}

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