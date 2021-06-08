#include "GoraZOstrymSzczytem.hh"

/*!
 * \brief Konstruktor bezparamtetryczny
 *
 * ustawia nazwe pliku wzorcowego oraz kat orientacji gory
 */
GoraZOstrymSzczytem::GoraZOstrymSzczytem()
{
    NazwaPliku_Wzorcowy = "bryly_wzorcowe/szescian_na_powierzchni.dat";
    kat_or = 0;
}

/*!
 * \brief Metoda transformujaca gore z ostrym szczytem
 * 
 * gora transformowana jest wzgledem wektora i dodatkowo
 * jest odpowiednio skalowana
 * 
 * \param[in] Trans - Wektor translacji
 * 
 */
void GoraZOstrymSzczytem::Transformacja(const Wektor3D& trans)
{
    for(int i=0; i<WYMIAR; ++i)
    {
        Polozenie[i] = Polozenie[i] * Skala[i] + trans[i];
    }
}

/*!
 * \brief Metoda tworzaca opis gory z ostrym szczytem
 * 
 * Wykonywane sa odpowiednie operacje przeksztalcajace,
 * wraz z jednosczesnym zapisaniem go w odpowiedniej formie
 * do pliku wynikowego
 * 
 * \pre musza uprzednio zostac nadane: skala oraz nazwa pliku finalnego
 * 
 * \param[in] Trans - Wektor translacji
 * 
 * \retval true - gdy operacja sie uda
 * \retval false - gdy operacja sie nie uda
 * 
 */
bool GoraZOstrymSzczytem::TworzOpisGoryZOstrymSzczytem(const Wektor3D& Wek)
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
    
    for(unsigned int ind_krawedzi = 0; ind_krawedzi < 5; ++ind_krawedzi)
    {
        for(unsigned int ind_wierz = 0; ind_wierz < 4; ++ind_wierz)
        {
            PlikWzorcowy >> Polozenie;
            if(PlikWzorcowy.fail()) return false;

            if(Polozenie[2] > 0.5)
            {
                Polozenie[0] = Polozenie[1] = 0;
            }
            else if(Polozenie[2] == 0.5)
            {
                Polozenie[0] /= 2;
                Polozenie[1] /= 2;
            }
            Transformacja(Wek);
            PlikFinalny << Polozenie;
            if(PlikFinalny.fail()) return false;
        }
        PlikFinalny << std::endl;
    }
    Polozenie = Wek;
    return !PlikFinalny.fail();
}

/*!
 * \brief Metoda tworzaca nazwe gory z ostrym szczytem
 * 
 * W zaleznosci od ID gory tworzony jest
 * odpowiedni plik wynikowy
 * 
 * \param[in] ID - nr obiektu tej klasy na liscie
 * 
 * \return string - bedacy odpowiednio sformatowana nazwa pliku
 * 
 */
std::string GoraZOstrymSzczytem::TworzNazweGoryZeSzczytem(unsigned int ID)
{
    std::ostringstream strmwy;

    strmwy << "dat/przeszkody/PlikWlasciwy_GoraZOstrymSzczytem_(przeszkoda_nr" << ID << ").dat";

    return strmwy.str();
}

/*!
 * \brief Metoda ustawiajaca polozenie gory z ostrym szczytem
 * 
 * \param[in] x - wspolrzedna na osi OX
 * \param[in] y - wspolrzedna na osi OY
 * 
 * \return nPolozenie - wektor, ktory pozniej zostanie
 *                      do ustawienia gory na scenie
 * 
 */
Wektor3D GoraZOstrymSzczytem::UstawPolozenie(int x, int y) const
{
    Wektor3D nPolozenie;
    nPolozenie[0] = x;
    nPolozenie[1] = y;
    nPolozenie[2] = 0;

    return nPolozenie;
}

/*!
 * \brief Metoda tworzaca odpowiedni plik wynikowy
 * 
 * W zaleznosci od ID gory tworzony jest
 * odpowiedni plik wynikowy
 * 
 * \param[in] ID - nr drona na scenie
 * \param[in] Lacze 
 * 
 */
void GoraZOstrymSzczytem::TworzGoreZOstrymSzczytem(unsigned int ID, PzG::LaczeDoGNUPlota& Lacze)
{
    std::string NazwaPliku;
    id = ID;

    NazwaPliku = TworzNazweGoryZeSzczytem(ID);
    UstawNazwaPlikuWlasciwego(NazwaPliku.c_str());
    Lacze.DodajNazwePliku(NazwaPliku.c_str());
}

bool GoraZOstrymSzczytem::TransDoUklRodzica(const Wektor3D& Wek, PzG::LaczeDoGNUPlota& Lacze)
{
    if(!TworzOpisGoryZOstrymSzczytem(Wek)) return false;
    Lacze.Rysuj();
    return true;
}

std::string GoraZOstrymSzczytem::Identyfikuj() const
{
    std::ostringstream Obiekt;

    Obiekt << "Gora z ostrym szczytem (" << Polozenie[0] << ", " << Polozenie[1] <<")";

    return Obiekt.str();
}

bool GoraZOstrymSzczytem::SprawdzID(unsigned int _id) const
{
    if(id == _id)
        return true;
    else
        return false;
}