#include <iostream>

#include "Wektor3D.hh"

#include "Scena.hh"

using namespace std;

int main()
{
  Scena S;
  char input = 'm';

  S.TworzScene();
  Wektor3D::ZwrocIloscWektorow();

  while (input != 'k')
  {
    std::cout<<"Twoj wybor (m - menu) > ";
    cin>>input;
    S.Menu(input);
  }

  return 0;
}
