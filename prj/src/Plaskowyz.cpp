#include "Plaskowyz.hh"


/*!
 * \brief Konstruktor bezparamtetryczny
 *
 * ustawia nazwe pliku wzorcowego oraz kat orientacji gory
 */
Plaskowyz::Plaskowyz()
{
    NazwaPliku_Wzorcowy = "bryly_wzorcowe/szescian_na_powierzchni.dat";
    kat_or = 0;
}

/*!
 * \brief Metoda transformujaca gore z dluga grania
 * 
 * gora transformowana jest wzgledem wektora i dodatkowo
 * jest odpowiednio skalowana
 * 
 * \param[in] Trans - Wektor translacji
 * 
 */
void Plaskowyz::Transformacja(const Wektor3D& trans)
{
    for(int i=0; i<WYMIAR; ++i)
    {
        Polozenie[i] = Polozenie[i] * Skala[i] + trans[i];
    }
}

/*!
 * \brief Metoda tworzaca opis gory z dluga grania
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
bool Plaskowyz::TworzOpisPlaskowyzu(const Wektor3D& Wek)
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
 * \brief Metoda tworzaca nazwe gory z dluga grania
 * 
 * W zaleznosci od ID drona tworzony jest
 * odpowiedni plik wynikowy
 * 
 * \param[in] ID - nr obiektu tej klasy na liscie
 * 
 * \return string - bedacy odpowiednio sformatowana nazwa pliku
 * 
 */
std::string Plaskowyz::TworzNazwePlaskowyzu(unsigned int ID)
{
    std::ostringstream strmwy;

    strmwy << "dat/przeszkody/PlikWlasciwy_Plaskowyz_(przeszkoda_nr" << ID << ").dat";

    return strmwy.str();
}

/*!
 * \brief Metoda ustawiajaca polozenie gory z dluga grania
 * 
 * \param[in] x - wspolrzedna na osi OX
 * \param[in] y - wspolrzedna na osi OY
 * 
 * \return nPolozenie - wektor, ktory pozniej zostanie
 *                      do ustawienia gory na scenie
 * 
 */
Wektor3D Plaskowyz::UstawPolozenie(int x, int y) const
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
 * W zaleznosci od ID gory worzony jest
 * odpowiedni plik wynikowy
 * 
 * \param[in] ID - nr drona na scenie
 * \param[in] Lacze 
 * 
 */
void Plaskowyz::TworzPlaskowyz(unsigned int ID, PzG::LaczeDoGNUPlota& Lacze)
{
    std::string NazwaPliku;
    id = ID;

    NazwaPliku = TworzNazwePlaskowyzu(ID);
    UstawNazwaPlikuWlasciwego(NazwaPliku.c_str());
    Lacze.DodajNazwePliku(NazwaPliku.c_str());
}

bool Plaskowyz::TransDoUklRodzica(const Wektor3D& Wek, PzG::LaczeDoGNUPlota& Lacze)
{
    if(!TworzOpisPlaskowyzu(Wek)) return false;
    Lacze.Rysuj();
    return true;
}

std::string Plaskowyz::Identyfikuj() const
{
    std::ostringstream Obiekt;

    Obiekt << "Plaskowyz (" << Polozenie[0] << ", " << Polozenie[1] <<")";

    return Obiekt.str();
}

bool Plaskowyz::SprawdzID(unsigned int _id) const
{
    if(id == _id)
        return true;
    else
        return false;
}