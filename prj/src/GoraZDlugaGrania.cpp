#include "GoraZDlugaGrania.hh"

/*!
 * \brief Konstruktor bezparamtetryczny
 *
 * ustawia nazwe pliku wzorcowego oraz kat orientacji gory
 */
GoraZDlugaGrania::GoraZDlugaGrania()
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
void GoraZDlugaGrania::Transformacja(const Wektor3D& trans)
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
bool GoraZDlugaGrania::TworzOpisGoryZDlugaGrania(const Wektor3D& Wek)
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
                if(Polozenie[0] < 0)
                    Polozenie[0] = fabs(Polozenie[0]);
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
std::string GoraZDlugaGrania::TworzNazweGoryZGrania(unsigned int ID)
{
    std::ostringstream strmwy;

    strmwy << "dat/przeszkody/PlikWlasciwy_GoraZDlugaGrania_(przeszkoda_nr" << ID << ").dat";

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
Wektor3D GoraZDlugaGrania::UstawPolozenie(int x, int y) const
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
void GoraZDlugaGrania::TworzGoreZDlugaGrania(unsigned int ID, PzG::LaczeDoGNUPlota& Lacze)
{
    std::string NazwaPliku;
    id = ID;
    
    NazwaPliku = TworzNazweGoryZGrania(ID);
    UstawNazwaPlikuWlasciwego(NazwaPliku.c_str());
    Lacze.DodajNazwePliku(NazwaPliku.c_str());
}

/*!
 * \brief Metoda przesuwajaca Gore z dluga grania wzgledem sceny
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
bool GoraZDlugaGrania::TransDoUklRodzica(const Wektor3D& Wek, PzG::LaczeDoGNUPlota& Lacze)
{
    if(!TworzOpisGoryZDlugaGrania(Wek)) return false;
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
std::string GoraZDlugaGrania::Identyfikuj() const
{
    std::ostringstream Obiekt;

    Obiekt << "Gora z dluga grania (" << Polozenie[0] << ", " << Polozenie[1] <<")";

    return Obiekt.str();
}

/*!
 * \brief Metoda sprawdzajaca ID obiektu
 * 
 * \param[in] _id - id, ktore ma zostac sprawdzone
 * 
 * \retval false - jesli id sie nie zgadza
 * \retval true - jeslie id jest takie samo
 * 
 */
bool GoraZDlugaGrania::SprawdzID(unsigned int _id) const
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
std::vector<Wektor<2>> GoraZDlugaGrania::ObliczeGraniczneWsp() const
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

/*!
 * \brief Metoda sprawdzajaca czy dane polozenie jest zajete przez obiekt klasy GoraZDlugaGrania
 *
 * Sprawdzane jest czy odleglosc miedzy srodkami dronow jest wieksza od
 * dwoch promienia + 1/2 skali na danej osi. Dodatkowo sprawdzana jest odleglosc
 * od poszczegolnych wierzchokow.
 * 
 * \param[in] Polozenie_drona - wektor polozenia aktualnie poruszanego drona
 * \param[in] Promien - promien aktualnie poruszanego drona
 * 
 * \retval false - jesli dane miejsce nie jest zajete przez obiekt klasy GoraZDlugaGrania
 * \retval true - jesli dane miejsce jest zajete przez obiekt klasy GoraZDlugaGrania
 * 
 */
bool GoraZDlugaGrania::CzyZajete(const Wektor3D& Polozenie_drona, double Promien) const
{
    std::vector<Wektor<2>> wsp_wierzcholkow_2D =  ObliczeGraniczneWsp();
    double odleglosc, x, y; //x to zmienna pomocnicza
    //double licznik = 0;
    Wektor<2> Polozenie_drona_2D = Polozenie_drona;
    Wektor<2> Polozenie_Plaskowyzu_2D = Polozenie;

    odleglosc = (Polozenie_drona_2D - Polozenie_Plaskowyzu_2D).ObliczDlugosc();

    //case 1: lewo/prawo
    x = Promien + Skala[0]/2;
    y = Promien + Skala[1]/2;
    if(odleglosc >= x && odleglosc >= y)
    {
        //std::cout<<"Wolne na osi x i y gzdg"<<std::endl;
        return false;
    }

    //case 3,4,5,6: odleglosci od wierzcholkow
    for(unsigned int idx=0; idx<wsp_wierzcholkow_2D.size(); ++idx)
    {
        odleglosc = (Polozenie_drona_2D - wsp_wierzcholkow_2D[idx]).ObliczDlugosc();
        if(odleglosc <= Promien) return true;
        //std::cout<<"Wolne, odleglosc gzdg"<< odleglosc <<std::endl;
    }

    
    return true;
}