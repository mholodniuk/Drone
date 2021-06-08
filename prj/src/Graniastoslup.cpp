#include "Graniastoslup.hh"


/*!
 * \brief Konstruktor bezparametryczny
 *
 * Ustawia Nazwe pliku wzorcowego i nadaje kat orientacji 0
 * 
 */
Graniastoslup::Graniastoslup()
{
    NazwaPliku_Wzorcowy = PLIK_WZORCOWEGO_GRANIASTOSLUPA6;
    Kat_Or = 0;
}

/*!
 * \brief Metoda zadajaca kat orientacji
 * 
 * Podany w argumencie kat ustawia jako Kat_Or
 * Jej wykonanie potrzebne jest w celu poprawnego
 * obrotu Graniastoslupa
 * 
 * \param[in] kat - kat obrotu
 * 
 */
void Graniastoslup::ZadajKatObrotu(double kat)
{
    Kat_Or = kat;
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

    Polozenie = MacierzRot * Polozenie;
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
    for(int i=0; i<WYMIAR; ++i)
    {
        Polozenie[i] = Polozenie[i] * Skala[i] + Trans[i];
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
    std::ifstream PlikWzorcowy(NazwaPliku_Wzorcowy);
    std::ofstream PlikFinalny(NazwaPliku_Finalny);

    if(!PlikWzorcowy.is_open())
    {
        std::cerr<<std::endl<<"Blad otwarcia pliku: "<<NazwaPliku_Wzorcowy<<std::endl;
        return false;
    }
    if(!PlikFinalny.is_open())
    {
        std::cerr<<std::endl<<"Blad otwarcia pliku: "<<NazwaPliku_Finalny<<std::endl;
        return false;
    }

    assert(PlikWzorcowy.good() && PlikFinalny.good());
    
    PlikWzorcowy >> Polozenie;

    while(!PlikWzorcowy.fail())
    {
        for(unsigned int IloscWierzch=0; IloscWierzch<ILOSC_ROTOROW; ++IloscWierzch)
        {
            Transformacja(Trans);
            PlikFinalny << Polozenie;
            //PlikFinalny << Polozenie[0] << " " << Polozenie[1] << " " << Polozenie[2] << " " <<std::endl;
            PlikWzorcowy >> Polozenie;
            
            assert(IloscWierzch == ILOSC_ROTOROW-1 || !PlikWzorcowy.fail());
        }
        PlikFinalny << std::endl;
    }
    PlikFinalny.close(); PlikWzorcowy.close();
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