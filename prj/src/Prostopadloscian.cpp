#include "../inc/Prostopadloscian.hh"

/*!
 * \brief Konstruktor bezparametryczny
 *
 * Ustawia Nazwe pliku wzorcowego i nadaje kat orientacji 0
 * 
 */
Prostopadloscian::Prostopadloscian(std::string NazwaPilku, const Wektor3D& skala)
    : BrylaGeometryczna(NazwaPilku, skala), Kat_Or(0) {
    
    std::ifstream PlikWzorcowy(PLIK_WZORCOWEGO_SZESCIANU);
    std::stringstream buffer;
    buffer << PlikWzorcowy.rdbuf();

    if(!PlikWzorcowy.is_open()) {
        std::cerr << std::endl << "Blad otwarcia pliku: " << PLIK_WZORCOWEGO_SZESCIANU << std::endl;
    }

    Wektor3D tmp;
    while(buffer>>tmp) {
        //std::cout<<tmp;
        wierzcholki.push_back(tmp);
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
void Prostopadloscian::Obrot() {
    double KatRad = Kat_Or*M_PI/180;
    Macierz3x3 MacierzRot;
    MacierzRot.ObrotZ(KatRad);

    for(Wektor3D& wierzcholek : wierzcholki) {
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
void Prostopadloscian::Transformacja(const Wektor3D& Trans) {
    Obrot();
    for(Wektor3D& wierzcholek : wierzcholki) {
        for(int i=0; i<WYMIAR; ++i) {
            wierzcholek[i] = wierzcholek[i] * Skala[i] + Trans[i];
        }
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
bool Prostopadloscian::TworzOpisProstopadloscianu(const Wektor3D& Trans)
{
    std::ofstream PlikFinalny(NazwaPliku_Finalny);

    if(!PlikFinalny.is_open())
    {
        std::cerr<<std::endl<<"Blad otwarcia pliku: "<<NazwaPliku_Finalny<<std::endl;
        return false;
    }
    Transformacja(Trans);
    int i=0;
    for(const auto& wierzcholek : wierzcholki) { 
        if(i != 0 && i % 4 == 0) PlikFinalny << "\n";
        i++;
        PlikFinalny << wierzcholek;
    }

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
bool Prostopadloscian::TransDoUklRodzica(const Wektor3D& Wek)
{   
    for(auto &wierzcholek : wierzcholki) {
        std::cout << wierzcholek << std::endl;
    }

    if(!TworzOpisProstopadloscianu(Wek)) return false;
    return true;
}