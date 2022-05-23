#include <iostream>

#include "../inc/Vector3D.hh"
#include "../inc/Menu.hh"
#include <unistd.h>
#include "../inc/Scene.hh"

using namespace std;

int main()
{
  Scene S;
  char input = 'm';
  
  Vector3D::GetNumberOfVectors();

  while (input != 'k')
  {
    std::cout<<"Twoj wybor (m - menu) > ";
    cin>>input;
    S.Menu(input);
  }

  return 0;
}
