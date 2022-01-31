#include "../inc/Prostopadloscian.hh"

/*!
 * \brief Konstruktor bezparametryczny
 *
 * Ustawia Nazwe pliku wzorcowego i nadaje kat orientacji 0
 * 
 */
Cuboid::Cuboid(std::string NazwaPilku, const Wektor3D& skala, const Wektor3D& center)
    : Figure(NazwaPilku, skala, center) { }


void Cuboid::CalculateLocalPosition() 
{
    std::ifstream PlikWzorcowy(PLIK_WZORCOWEGO_SZESCIANU);
    std::stringstream buffer;
    buffer << PlikWzorcowy.rdbuf();

    if(!PlikWzorcowy.is_open()) {
        std::cerr << std::endl << "Blad otwarcia pliku: " << PLIK_WZORCOWEGO_SZESCIANU << std::endl;
    }

    Wektor3D tmp;
    while(buffer>>tmp) {
        //std::cout<<tmp;
        vertices.push_back(tmp);
    }

    for(Wektor3D& vertex : vertices) {
        for(int i=0; i<WYMIAR; ++i) {
            vertex[i] = vertex[i] * Scale[i];
        }
    }
    PlikWzorcowy.close();
}