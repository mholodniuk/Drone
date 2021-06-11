#pragma once

#include <iostream>
#include <cassert>
#include <iomanip>
#include <cmath>


/*!
 * \file "Wektor.hh"
 * \brief Ten plik zawiera definicję szablonu Wektor<>
 */

/*!
 * \brief modeluje pojecie Wektora o dowolnym rozmiarze

 * Zawiera definicję szablonu Wektor. Pozwala on na
 * stworzenie instancji klasy wektor o dowolnym wymiarze, dla
 * których zdefiniowane są podstawowe działania arytmetyczne.
 * 
 * \tparam wymiar - rozmiar wektora
 */
template <int wymiar>
class Wektor
{
  double wsp[wymiar];
  static int AktualnaIloscWektorow;
  static int OgolnaIloscWektorow;

public:

  /*!
   * \brief Konstruktory bezparamentryczny (inicjalizuje zerami) i parametryczny 
   */
  Wektor();
  ~Wektor();
  Wektor(const std::initializer_list<double> &rListWsp);
  Wektor(const Wektor & wektor);

  /*!
   * \brief przeciazenie operatora indeksowania dla odczytu
   * sprawdzane jest czy nie wykroczono poza zakres wektora
   */
  double operator [] (int idx)const
  {
    assert(idx < wymiar); 
    return wsp[idx];
  }
  /*!
   * \brief przeciazenie operatora indeksowania dla wczytania
   * sprawdzane jest czy nie wykroczono poza zakres wektora
   */
  double &operator [] (int idx)
  {
    assert(idx < wymiar);
    return wsp[idx];
  }

  /*!
   * \brief przeciazenia operatorow
   */
  Wektor& operator=(const Wektor&);
  Wektor operator +(Wektor &)const; 
  Wektor operator -(Wektor &) const;
  Wektor operator+= (const Wektor &);
  bool operator!= (const Wektor &) const;
  bool operator== (const Wektor &) const;
  Wektor operator* (double mnoznik);

  /*!
   * \brief Metoda obliczajaca dlugosc wektora
   */
  double ObliczDlugosc();

  /*!
   * \brief Konwerter wektora o danym wymiarze na wektor o jeden wymiar mniejszy
   */
  operator Wektor<wymiar-1> () const
  {
    Wektor<wymiar-1> Wynik;
    for(unsigned int idx=0; idx < wymiar-1; ++idx)  Wynik[idx] = (*this)[idx]; 
    return Wynik;
  }

  /*!
   * \brief Metody zwracajace ilosc obiektow
   */
  static void ZwrocIloscWektorow()
  {
    std::cout<<"Aktualna ilosc wektorow: "<<AktualnaIloscWektorow<<std::endl;
    std::cout<<"Ogolna ilosc wektorow: "<<OgolnaIloscWektorow<<std::endl;
  }

};
//!\brief inicjalizacja pol statycznych
template <int wymiar>
int Wektor<wymiar>::AktualnaIloscWektorow = 0;

template <int wymiar>
int Wektor<wymiar>::OgolnaIloscWektorow = 0;


/*!
 * \brief Konstruktor bezparametryczny obiektu Wektor
 * 
 * tworzy obiekt Wektor i inicjalizuje jego pole wartoscia 0 oraz zlicza powstaly obiekt
 */
template <int wymiar>
Wektor<wymiar>::Wektor()
{
  ++OgolnaIloscWektorow;
  ++AktualnaIloscWektorow;
  for(int i=0; i<wymiar; ++i)
  {
    wsp[i] = 0;
  } 
}

/*!  
 * \brief Konstruktor kopiujacy
 */
template <int wymiar>
Wektor<wymiar>::Wektor(const Wektor<wymiar> & wektor)
{
  ++OgolnaIloscWektorow;
  ++AktualnaIloscWektorow;
  for(int i=0; i<wymiar; ++i)
  {
    wsp[i] = wektor.wsp[i];
  }
}

/*!  
 * \brief Operator podstawienia
 */
template<int wymiar>
Wektor<wymiar>& Wektor<wymiar>::operator=(const Wektor<wymiar> & wektor)
{
  for(int i=0; i<wymiar; ++i)
  {
    wsp[i] = wektor.wsp[i];
  }
  return *this;
}

/*!
 * \brief Destruktor obiektu Wektor
 * 
 * zmniejsza aktualna ilosc obiektow klasy wektor
 */
template <int wymiar>
Wektor<wymiar>::~Wektor()
{
  --AktualnaIloscWektorow;
}

/*!
 * \brief Konstruktor parametryczny obiektu Wektor
 * 
 * tworzy obiekt Wektor i inicjalizuje jego pole zadanymi wartosciami
 * 
 * \param[in] rListaWsp - lista wartosci, ktore maja byc przypisane wektorowi 
 */
template <int wymiar>
Wektor<wymiar>::Wektor(const std::initializer_list<double> & rListaWsp): Wektor()
{
  //++AktualnaIloscWektorow; ++OgolnaIloscWektorow;
  assert(rListaWsp.size() <= wymiar);
  int Ind = -1;
  for (double Wsp_i : rListaWsp) 
    wsp[++Ind] = Wsp_i;
}

/*!
 * \brief Przeciazenie operatora dodawania obiektow klasy Wektor
 * 
 * Opis
 * 
 * \param[in] czynnik - Wektor dodawany
 * 
 * \return Wynik - wektor, bedacy suma this i wektora podanego
 * 
 */
template<int wymiar>
Wektor<wymiar> Wektor<wymiar>::operator+(Wektor<wymiar> & czynnik) const
{
  Wektor<wymiar> Wynik;
  for(int i=0; i < wymiar; ++i)
  {
    Wynik[i] = wsp[i] + czynnik[i];
  }
  return Wynik;
}

/*!
 * \brief Przeciazenie operatora odejmowania obiektow klasy Wektor
 * 
 * \tparam wymiar - rozmiar wektorow
 * 
 * \param[in] czynnik - Wektor odejmowany
 * 
 * \return Wynik - wektor, bedacy roznica this i wektora podanego
 * 
 */
template<int wymiar>
Wektor<wymiar> Wektor<wymiar>::operator-(Wektor<wymiar> & czynnik) const
{
  Wektor<  wymiar> Wynik;
  for(int i=0; i < wymiar; ++i)
  {
    Wynik[i] = wsp[i] - czynnik[i];
  }
  return Wynik;
}

/*!
 * \brief Przeciazenie operatora sumowania obiektow klasy Wektor
 * 
 * \tparam wymiar - rozmiar wektorow
 * 
 * \param[in] czynnik - Wektor sumowany
 * 
 * \return Wynik - wektor, bedacy suma this i wektora podanego
 * 
 */
template<int wymiar>
Wektor<wymiar> Wektor<wymiar>::operator+=(const Wektor<wymiar> & wektor)
{
  for(int i=0; i<wymiar; ++i)
  {
    wsp[i] += wektor[i];
  }
  return (*this);
}

/*!
 * \brief Przeciazenie operatora (nie)porownania obiektow klasy Wektor
 * 
 * \tparam wymiar - rozmiar wektorow
 * 
 * \param[in] czynnik - Wektor porownywany
 * 
 * \return true - jesli wektory sa inne
 * \return false - jesli wektory sa takie same
 * 
 */
template<int wymiar>
bool Wektor<wymiar>::operator!= (const Wektor<wymiar>& wektor) const
{
  int licznik = 0;
  for(int i=0; i<wymiar; ++i)
  {
    if(wsp[i] == wektor[i])
      ++licznik;
  }
  if(licznik == wymiar)
    return false;
  else
    return true;
}

/*!
 * \brief Przeciazenie operatora porownania obiektow klasy Wektor
 * 
 * \tparam wymiar - rozmiar wektorow
 * 
 * \param[in] czynnik - Wektor porownywany
 * 
 * \return true - jesli wektory sa takie same
 * \return false - jesli wektory sa innne
 * 
 */
template<int wymiar>
bool Wektor<wymiar>::operator== (const Wektor<wymiar>& wektor) const
{
  for(int i=0; i<wymiar; ++i)
  {
    if(wsp[i] != wektor[i])
      return false;
  }
  return true;
}

/*!
 * \brief Przeciazenie operatora mnozenia obiektu klasy Wektor przez liczbe zmiennopzecinkowa
 * 
 * \tparam wymiar - rozmiar wektorow
 * 
 * \param[in] czynnik - Wektor mnozony
 * 
 * \return Wynik - wektor, bedacy iloczynem this i wektora podanego
 * 
 */
template<int wymiar>
Wektor<wymiar> Wektor<wymiar>::operator*(double mnoznik)
{
  Wektor<wymiar> wynik;
  for(int i=0; i < wymiar; ++i)
  {
    wynik[i] = wsp[i] * mnoznik;
  }
  return wynik;
}

/*!
 * \brief Metoda obliczajaca dlugosc wektora
 * 
 * Dlugosc jako suma kwadratow wartosci pod pierwiastkiem
 * 
 * \tparam wymiar - rozmiar wektorow
 * 
 * \return suma - dlugosc wektora this
 * 
 */
template<int wymiar>
double Wektor<wymiar>::ObliczDlugosc()
{
  double suma = 0;
  for(int i=0; i<wymiar; ++i)
  {
    suma += pow(wsp[i], 2);
  }
  suma = sqrt(suma);
  return suma;
}

/*!
 * \brief Przeciazenie operatora przesuniecia bitowego w lewo dla obiektow klasy Wektor
 * 
 * \tparam wymiar - rozmiar
 * 
 * \param[in] Strm - strumien
 * \param[in] Wek - wektor do wypisania
 * 
 * \return strumien z odpowiednio sformatowanym wektorem
 * 
 */
template <int wymiar>
std::ostream& operator << (std::ostream &Strm, const Wektor<wymiar> &Wek)
{
  for(int i=0; i<wymiar; ++i)
  {
      Strm << std::setw(16) << std::fixed << std::setprecision(10) << Wek[i];
  }
  Strm<<std::endl;
  return Strm;
}

/*!
 * \brief Przeciazenie operatora przesuniecia bitowego w prawo dla obiektow klasy Wektor
 * 
 * \tparam wymiar - rozmiar
 * 
 * \param[in] Strm - strumien
 * \param[in] Wek - wektor do wczytania
 * 
 * \return strumien z odpowiednio sformatowanym wektorem
 * 
 */
template <int wymiar>
std::istream& operator >> (std::istream &Strm, Wektor<wymiar> &Wek)
{
  for(int i=0; i<wymiar; ++i)
  {
    Strm >> Wek[i];
    if(Strm.fail())
      return Strm;
  }
  return Strm;
}