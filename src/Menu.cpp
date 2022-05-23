#include "../inc/Menu.hh"

#include <iostream>
#include "../inc/Consts.hh"

/*!
 * \brief Funckja ustwiajaca odpowiednie parametry gnuplota
 */
void GnuplotSetUp(PzG::LaczeDoGNUPlota & Lacze)
{
  Lacze.DodajNazwePliku("bryly_wzorcowe/plaszczyzna.dat");

  Lacze.ZmienTrybRys(PzG::TR_3D);
  Lacze.Inicjalizuj();

  Lacze.UstawZakresX(0, 200);
  Lacze.UstawZakresY(0, 200);
  Lacze.UstawZakresZ(0, 120);

  Lacze.UstawRotacjeXZ(64,65);
}