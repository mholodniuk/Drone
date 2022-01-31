#include "../inc/Przeszkody.hh"


/*!
 * \brief Konstruktor bezparametryczny
 *
 * Ustawia Nazwe pliku wzorcowego i nadaje kat orientacji 0
 * 
 */
Ridge::Ridge(std::string NazwaPilku, const Wektor3D& skala, const Wektor3D& center)
    : Figure(NazwaPilku, skala, center) { }


void Ridge::CalculateLocalPosition() 
{
    std::ifstream PlikWzorcowy("bryly_wzorcowe/szescian_na_powierzchni.dat");
    std::stringstream buffer;
    buffer << PlikWzorcowy.rdbuf();

    if(!PlikWzorcowy.is_open()) {
        std::cerr << std::endl << "Blad otwarcia pliku: bryly_wzorcowe/szescian_na_powierzchni.dat" << std::endl;
    }

    Wektor3D tmp;
    while(buffer>>tmp) {
        if(tmp[2]>0.5) {
            if(tmp[0]<0)
                tmp[0] = fabs(tmp[0]);
        }
        vertices.push_back(tmp);
    }

    for(Wektor3D& vertex : vertices) {
        for(int i=0; i<WYMIAR; ++i) {
            vertex[i] = vertex[i] * Scale[i];
        }
    }
    PlikWzorcowy.close();
}

void Ridge::Draw(PzG::LaczeDoGNUPlota& Lacze)
{
    Figure::Draw();
    Lacze.DodajNazwePliku(FinalFileName.c_str()).ZmienKolor(4);
    Lacze.Rysuj();
}