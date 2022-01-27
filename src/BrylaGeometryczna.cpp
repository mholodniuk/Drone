#include "../inc/BrylaGeometryczna.hh"
#include <string.h>
#include <fstream>
#include <cmath>


Figure::Figure(std::string NazwaPilku,const Wektor3D& skala)
    : NazwaPliku_Finalny(NazwaPilku), Skala(skala){ }
