#include "../inc/Graniastoslup.hh"


/*!
 * \brief Konstruktor bezparametryczny
 *
 * Ustawia Nazwe pliku wzorcowego i nadaje kat orientacji 0
 * 
 */
Prism::Prism(std::string NazwaPilku, const Wektor3D& skala)
    : Figure(NazwaPilku, skala), Orientation_deg(0) { }

void Prism::CalculateLocalPosition()
{
    std::ifstream PlikWzorcowy(PLIK_WZORCOWEGO_GRANIASTOSLUPA6);
    std::stringstream buffer;
    buffer << PlikWzorcowy.rdbuf();

    if(!PlikWzorcowy.is_open()) {
        std::cerr << std::endl << "Blad otwarcia pliku: " << PLIK_WZORCOWEGO_GRANIASTOSLUPA6 << std::endl;
    }

    Wektor3D tmp;
    while(buffer>>tmp) {
        //std::cout<<tmp;
        vertices.push_back(tmp);
    }

    for(Wektor3D& wierzcholek : vertices) {
        for(int i=0; i<WYMIAR; ++i) {
            wierzcholek[i] = wierzcholek[i] * Skala[i];
        }
    }
    PlikWzorcowy.close();
}


/*!
 * \brief Metoda Obracajaca Prostopadloscian
 * 
 * Obliczana jest macierz obrotu dla danego kata
 * i na jej podstawie obliczane jest polozenie po obrocie
 *
 */
void Prism::Rotate()
{
    double KatRad = Orientation_deg*M_PI/180;
    Macierz3x3 MacierzRot;
    MacierzRot.ObrotZ(KatRad);

    for(Wektor3D& wierzcholek : vertices) {
        wierzcholek = MacierzRot * wierzcholek;
    }
}

/*!
 * \brief Metoda transformujaca prostopadloscia
 * 
 * Metoda transformujaca prostopadloscian wzgledem
 * katu i wektora
 * 
 * \param[in] Trans - Wektor translacji
 * 
 */
void Prism::Transform(const Wektor3D& Trans)
{
    for(Wektor3D& wierzcholek : vertices) {
        wierzcholek += Trans;
    }
}

/*!
 * \brief Metoda tworzaca opis prostopadloscianu
 * 
 * Wykonywane sa odpowiednie operacje przeksztalcajace,
 * wraz z jednosczesnym zapisaniem go w odpowiedniej formie
 * do pliku wynikowego
 * 
 * \param[in] Trans - Wektor translacji
 * 
 * \retval true - gdy operacja sie uda
 * \retval false - gdy operacja sie nie uda
 * 
 */
bool Prism::SaveToFile(const Wektor3D& Trans)
{
    std::ofstream PlikFinalny(NazwaPliku_Finalny);

    if(!PlikFinalny.is_open())
    {
        std::cerr<<std::endl<<"Blad otwarcia pliku: "<<NazwaPliku_Finalny<<std::endl;
        return false;
    }
    CalculateLocalPosition();
    Rotate();
    Transform(Trans);
    int i=0;
    for(const auto& wierzcholek : vertices) { 
        if(i != 0 && i % 4 == 0) PlikFinalny << "\n";
        i++;
        PlikFinalny << wierzcholek;
    }
    vertices.clear();
    PlikFinalny.close();
    return !PlikFinalny.fail();
}
/*!
 * \brief Metoda przesuwajaca Prostopadloscian wzgledem Drona
 * 
 * Tutaj dokonywane jest ostateczne przesuniecie o odpowiedni
 * Wektor
 * 
 * \param[in] Wek - Wektor Translacji
 * 
 * \retval true - jesli operacja sie powiedzie
 * \retval false - jesli operacja sie nie powiedzie
 * 
 */
bool Prism::Translate(const Wektor3D& Wek)
{   
    if(!SaveToFile(Wek)) return false;
    return true;
}