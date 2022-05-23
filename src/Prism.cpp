#include "../inc/Prism.hh"


/*!
 * \brief Konstruktor bezparametryczny
 *
 * Ustawia Nazwe pliku wzorcowego i nadaje kat orientacji 0
 * 
 */
Prism::Prism(std::string NazwaPilku, const Vector3D& skala, const Vector3D& center)
    : Figure(NazwaPilku, skala, center) { }

void Prism::CalculateLocalPosition()
{
    std::ifstream PlikWzorcowy(PLIK_WZORCOWEGO_GRANIASTOSLUPA6);
    std::stringstream buffer;
    buffer << PlikWzorcowy.rdbuf();

    if(!PlikWzorcowy.is_open()) {
        std::cerr << std::endl << "Blad otwarcia pliku: " << PLIK_WZORCOWEGO_GRANIASTOSLUPA6 << std::endl;
    }

    Vector3D tmp;
    while(buffer>>tmp) {
        //std::cout<<tmp;
        vertices.push_back(tmp);
    }

    for(Vector3D& wierzcholek : vertices) {
        for(int i=0; i<WYMIAR; ++i) {
            wierzcholek[i] = wierzcholek[i] * Scale[i];
        }
    }
    PlikWzorcowy.close();
}