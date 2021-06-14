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

/*!
 * \brief Metoda przesuwajaca Gore z ostrym szczytem o odpowiedni wektor
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
bool GoraZOstrymSzczytem::TransDoUklRodzica(const Wektor3D& Wek, PzG::LaczeDoGNUPlota& Lacze)
{
    if(!TworzOpisGoryZOstrymSzczytem(Wek)) return false;
    Lacze.Rysuj();
    return true;
}

/*!
 * \brief Metoda pozwalajaca zidentyfikowac obiekt - jako przeszkode
 * 
 * W strumienu znajduje sie nazwa typu przeszkody, oraz jego polozenie
 * 
 * \return Obiekt - napis identyfikacyjny
 * 
 */
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

/*!
 * \brief Metoda obliczajaca wspolrzedne wierzcholkow Plaskowyzu
 * 
 * W zwracanym wektorze znajduja sie kolejno Wektory polozenia
 * wierzcholkow, zgodnie z ponizszym rysunkiem (x_min, y_max, x_max, y_min)
 * Jednoczesnie, niejawnie zostaje dokonana konwersja z wektorow 3D na 2D
 * 
 *    4.------------2.
 *    |             |
 *    |             |
 *    1.----------- 3.
 * 
 * \return wsp_wierzcholkow - vector zawierajacy wspolrzedne wierzcholkow
 * 
 */
std::vector<Wektor<2>> GoraZOstrymSzczytem::ObliczeGraniczneWsp() const
{
    std::vector<Wektor<2>> wsp_wierzcholkow;

    Wektor<2> x_min, x_max, y_min, y_max;
    x_min[0] = Polozenie[0] - Skala[0]/2;
    x_min[1] = Polozenie[1] - Skala[1]/2;

    y_max[0] = Polozenie[0] + Skala[0]/2;
    y_max[1] = Polozenie[1] + Skala[1]/2;

    x_max[0] = Polozenie[0] + Skala[0]/2;
    x_max[1] = x_min[1];

    y_min[0] = Polozenie[0] - Skala[0]/2;
    y_min[1] = y_max[1];

    wsp_wierzcholkow.push_back(x_min);
    wsp_wierzcholkow.push_back(y_max);
    wsp_wierzcholkow.push_back(x_max);
    wsp_wierzcholkow.push_back(y_min);

    return wsp_wierzcholkow;
}

bool GoraZOstrymSzczytem::CzyZajete(const Wektor3D& Polozenie_drona, double Promien) const
{
    std::vector<Wektor<2>> wsp_wierzcholkow_2D =  ObliczeGraniczneWsp();
    double odleglosc, x, y; //x to zmienna pomocnicza
    //double max, min;
    Wektor<2> Polozenie_drona_2D = Polozenie_drona;
    Wektor<2> Polozenie_Plaskowyzu_2D = Polozenie;

    odleglosc = (Polozenie_drona_2D - Polozenie_Plaskowyzu_2D).ObliczDlugosc();

    //case 1,2: lewo/prawo i gore/dol
    x = Promien + Skala[0]/2;
    y = Promien + Skala[1]/2;
    if(odleglosc >= x && odleglosc >= y)
    {
        std::cout<<"Wolne na osi x i y gzos"<<std::endl;
        return false;
    }
/*
    min = wsp_wierzcholkow_2D[0][1];
    max = wsp_wierzcholkow_2D[1][1];
    x = Promien + odleglosc;

    if(x < max && x < min)
    {
        std::cout<<"Dron jest w srodku gzos"<<std::endl;
        return true;
    }
*/
    //case 3,4,5,6: odleglosci od wierzcholkow
    for(unsigned int idx=0; idx<wsp_wierzcholkow_2D.size(); ++idx)
    {
        odleglosc = (Polozenie_drona_2D - wsp_wierzcholkow_2D[idx]).ObliczDlugosc();
        if(odleglosc <= Promien) return true;
        std::cout<<"Wolne, odleglosc gzos"<< odleglosc <<std::endl;
    }

    //case 7: srodek
    
    
    return true;
}