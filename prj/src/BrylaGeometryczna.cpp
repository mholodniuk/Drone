#include "BrylaGeometryczna.hh"
#include <string.h>
#include <fstream>
#include <cmath>


/*!
 * \brief Metoda ustawiajaca nazwe pliku docelowego
 * 
 * \param[in] NazwaPliku - Nazwa jaka ma byc ustawiona jako finalna
 * 
 */
void BrylaGeometryczna::UstawNazwaPlikuWlasciwego(const char* NazwaPliku)
{
    NazwaPliku_Finalny = NazwaPliku;
}

/*!
 * \brief Metoda ustawiajaca skale Bryly
 * 
 * \pre Skala musi byc dodatnia
 * 
 * \param[in] SkalaZadana
 * 
 * \return Skala - skala z jaka rysowana jest bryla 
 * 
 */
Wektor3D BrylaGeometryczna::UstawSkale(const Wektor3D& SkalaZadana)
{
    Skala = SkalaZadana;
    return Skala;
}
