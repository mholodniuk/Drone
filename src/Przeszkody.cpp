#include "../inc/Przeszkody.hh"


/*!
 * \brief Konstruktor bezparametryczny
 *
 * Ustawia Nazwe pliku wzorcowego i nadaje kat orientacji 0
 * 
 */
Obstacle::Obstacle(std::string NazwaPilku, const Wektor3D& skala, const Wektor3D& center, Type _type)
    : Figure(NazwaPilku, skala, center), type(_type) { }


void Obstacle::CalculateLocalPosition() 
{
    std::ifstream PlikWzorcowy("bryly_wzorcowe/szescian_na_powierzchni.dat");
    std::stringstream buffer;
    buffer << PlikWzorcowy.rdbuf();

    if(!PlikWzorcowy.is_open()) {
        std::cerr << std::endl << "Blad otwarcia pliku: bryly_wzorcowe/szescian_na_powierzchni.dat" << std::endl;
    }

    Wektor3D tmp;
    while(buffer>>tmp) {

        switch(type) {
            case Ridge:
                if(tmp[2] > 0.5)
                    if(tmp[0] < 0)
                        tmp[0] = fabs(tmp[0]);
                break;

            case Pyramid:
                if(tmp[2] > 0.5)
                    tmp[0] = tmp[1] = 0;
                else if(tmp[2] == 0.5) {
                    tmp[0] /= 2;
                    tmp[1] /= 2;
                }
                break;

            case Plateau:
                break;

            default: std::cerr << "wybrano zly typ przeszkody" <<std::endl; break;
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

void Obstacle::Draw(PzG::LaczeDoGNUPlota& Lacze)
{
    Figure::Draw();
    Lacze.DodajNazwePliku(FinalFileName.c_str()).ZmienKolor(4);
    Lacze.Rysuj();
}