#include "../inc/Graniastoslup.hh"


/*!
 * \brief Konstruktor bezparametryczny
 *
 * Ustawia Nazwe pliku wzorcowego i nadaje kat orientacji 0
 * 
 */
Graniastoslup::Graniastoslup(std::string NazwaPilku, const Wektor3D& skala)
    : BrylaGeometryczna(NazwaPilku, skala), Kat_Or(0) {

    std::ifstream PlikWzorcowy(PLIK_WZORCOWEGO_GRANIASTOSLUPA6);

    if(!PlikWzorcowy.is_open()) {
        std::cerr<<std::endl<<"Blad otwarcia pliku: "<<NazwaPliku_Wzorcowy<<std::endl;
    }
    wierzcholki.reserve(28);

    for(Wektor3D& wierzcholek : wierzcholki) {
        PlikWzorcowy >> wierzcholek;
        std::cout<<wierzcholek;
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
void Graniastoslup::Obrot()
{
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
void Graniastoslup::Transformacja(const Wektor3D& Trans)
{
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
bool Graniastoslup::TworzOpisGraniastoslupu(const Wektor3D& Trans)
{
    std::ofstream PlikFinalny(NazwaPliku_Finalny);

    if(!PlikFinalny.is_open())
    {
        std::cerr<<std::endl<<"Blad otwarcia pliku: "<<NazwaPliku_Finalny<<std::endl;
        return false;
    }

    for(const Wektor3D& wierzcholek : wierzcholki) {
        Transformacja(Trans);
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
bool Graniastoslup::TransDoUklRodzica(const Wektor3D& Wek)
{   
    if(!TworzOpisGraniastoslupu(Wek)) return false;
    return true;
}