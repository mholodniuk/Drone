#include <iostream>

#include "../inc/Wektor3D.hh"
#include "../inc/Menu.hh"
#include <unistd.h>
#include "../inc/Scena.hh"

using namespace std;

int main()
{
  PzG::LaczeDoGNUPlota lacze;

  UstawGNUPlot(lacze);

  Prostopadloscian P("test.dat", {10,10,10});
  P.TransDoUklRodzica({50,50,50});

  lacze.DodajNazwePliku("test.dat");

  lacze.Rysuj();

  while(true) {

  }
  

  return 0;
}
