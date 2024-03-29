#include "../inc/Drone.hh"
#include "../inc/Consts.hh"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include <unistd.h>
#include <chrono>
#include <thread>

#define BLAD_OBLICZEN 1e-8


Drone::Drone(unsigned int ID, PzG::LaczeDoGNUPlota& lacze)
 : Position({0,0,0}), current_drone_rotation(0), id(ID) {

    Vector3D BodyScale = {16, 12, 10};
    Vector3D RotorScale = {10,10,6};

    std::string file_name = CreateBodyFileName(ID);

    Body = std::make_shared<Cuboid>(file_name, BodyScale, Vector3D({0,0,5}));
    Body->SetRotation(current_drone_rotation);
    lacze.DodajNazwePliku(file_name.c_str()).ZmienKolor(4);
    
    int idx = -1;
    for(std::shared_ptr<Prism>& Rotor : Rotors) {
        file_name = CreateRotorFileName(ID, ++idx);
        Rotor = std::make_shared<Prism>(file_name, RotorScale, Vector3D({(double)(idx>1 ? -8 : 8), (double)(idx==1 || idx==3 ? 6 : -6), 10}));
        lacze.DodajNazwePliku(file_name.c_str()).ZmienKolor(4);
    }
}

/*!
 * \brief Metoda tworzaca nazwe rotora
 * 
 * W zaleznosci od ID drona i nr rotora tworzony jest
 * odpowiedni plik wynikowy
 * 
 * \param[in] id_drona - nr drona na scenie
 * \param[in] nrRotota - nr rotora drona
 * 
 * \return string - bedacy odpowiednio sformatowana nazwa pliku
 * 
 */
std::string Drone::CreateRotorFileName(unsigned int id_Drona, unsigned int nrRotora)
{
    std::stringstream StrmWy;

    StrmWy << "dat/Dron"<<id_Drona<<"/PlikWlasciwy_Dron"<<id_Drona<<"_Rotor"<<nrRotora+1<<".dat";

    return StrmWy.str();
}

/*!
 * \brief Metoda tworzaca nazwe korpusu
 * 
 * W zaleznosci od ID drona tworzony jest
 * odpowiedni plik wynikowy
 * 
 * \param[in] id_drona - nr drona na scenie
 * 
 * \return string - bedacy odpowiednio sformatowana nazwa pliku
 * 
 */
std::string Drone::CreateBodyFileName(unsigned int id_Drona)
{
    std::ostringstream StrmWy;

    StrmWy << "dat/Dron"<<id_Drona<<"/PlikWlasciwy_Dron"<<id_Drona<<"_Korpus.dat";

    return StrmWy.str();
}

std::string Drone::Identify() const
{
    std::ostringstream Obiekt;
    Obiekt << "Dron (" << Position[0] << ", " << Position[1] <<")";
    return Obiekt.str();
}

/*!
 * \brief Obliczajaca wspolrzedne elementów drona
 */
void Drone::CalcAndSaveElements()
{
    Matrix3x3 MatrixRot(Matrix3x3::Axis::OZ, current_drone_rotation);
    static double kat_obr = 0;

    Body->SetRotation(current_drone_rotation);
    for(int i=0; i<4; ++i) {
        Rotors[i]->SetGlobalOrientation(MatrixRot);
        Rotors[i]->SetRotation(i==0 || i==3 ? kat_obr : -kat_obr);
    }
    kat_obr+=15;
}

/*!
 * \brief Metoda przesuwajaca Drona wzgledem sceny
 * 
 * Tutaj dokonywane jest ostateczne przesuniecie o odpowiedni
 * Wektor i rysowanie drona
 * 
 * \param[in] Wek - Wektor Translacji
 * \param[in] lacze
 * 
 */
void Drone::Draw(PzG::LaczeDoGNUPlota& Lacze)
{
    CalcAndSaveElements();
    Body->Draw();
    for(auto& Rotor : Rotors) {
        Rotor->Draw();
    }
    Lacze.Rysuj();
}

void Drone::Translate(const Vector3D& Wek)
{
    Position += Wek;
    Body->Translate(Position);
    for(auto& Rotor : Rotors) {
        Rotor->Translate(Position);
    }
}

/*!
 * \brief Metoda realizujaca lot drona
 *
 * \param[in] Wek_kierunkowy - jednostkowy wektor kierunkowy
 * \param[in] dlugosc_lotu - odleglosc lotu drona
 * \param[in] Lacze - lacze do gnuplota
 * 
 */
void Drone::Fly(Vector3D& direction_vector, const double horizontal_distance, PzG::LaczeDoGNUPlota& Lacze)
{
    assert(fabs(direction_vector.ObliczDlugosc()-1) < BLAD_OBLICZEN);

    const double frequency = 30;
    const u_int16_t delay = 1000./frequency;

    Vector3D Wek_czastkowy = direction_vector * single_step;
    Vector3D Start_pos = Position;
    double distance_left = horizontal_distance;

    distance_left -= single_step;
    while(distance_left > 0) {
        Translate(Wek_czastkowy);
        usleep(delay*1'000);
        Draw(Lacze);
        distance_left -= single_step;
    }
    Vector3D move = direction_vector*horizontal_distance;
    Position = Start_pos+move;
    Translate({0,0,0});
    Draw(Lacze);
}

/*!
 * \brief Metoda realizujaca lot do przodu drona
 *
 * \param[in] dlugosc_lotu - odleglosc lotu drona
 * \param[in] LaczeDoGNUPlota
 * 
 * \pre dlugosc_lotu musi byc liczba dodatnia
 * 
 */
void Drone::FlyHorizontal(double dlugosc_lotu, PzG::LaczeDoGNUPlota& Lacze)
{
    Vector3D Kierunek_lotu = {1, 0, 0};
    Matrix3x3 MacierzRot(Matrix3x3::Axis::OZ, current_drone_rotation);

    Kierunek_lotu = MacierzRot * Kierunek_lotu;

    Fly(Kierunek_lotu, fabs(dlugosc_lotu), Lacze);
}

/*!
 * \brief Metoda realizujaca lot pionowy drona
 *
 * \param[in] dlugosc_lotu - odleglosc lotu drona
 * \param[in] LaczeDoGNUPlota
 * 
 */
void Drone::FlyVertical(double dlugosc_lotu, PzG::LaczeDoGNUPlota& Lacze)
{
    double kierunek = 0;
    if(dlugosc_lotu>0) kierunek =  1;
    if(dlugosc_lotu<0) kierunek = -1;

    Vector3D Kierunek_lotu = {0, 0, kierunek};

    Fly(Kierunek_lotu, fabs(dlugosc_lotu), Lacze);
}

/*!
 * \brief Metoda realizujaca obrot drona
 * 
 * \pre kat obrotu musi byc podany w stopniach
 * 
 * \param[in] kat_obrotu - kat o jaki ma obrocic sie dron
 * \param[in] Lacze 
 * 
 */
void Drone::Rotation(double kat_obrotu, PzG::LaczeDoGNUPlota & Lacze)
{
    kat_obrotu += current_drone_rotation;
    if(kat_obrotu>0) {
        for(; current_drone_rotation <= kat_obrotu; current_drone_rotation += 5) {
            Translate({0,0,0});
            usleep(100'000);
            Draw(Lacze);
        }
        current_drone_rotation -= 5;
    } else {
        for(; current_drone_rotation >= kat_obrotu; current_drone_rotation -= 5) {
            Translate({0,0,0});
            usleep(100'000);
            Draw(Lacze);
        }
        current_drone_rotation += 5;
    }
}

/*!
 * \brief Metoda animujaca lot w miejscu
 *
 * Dron bedzie unosil sie w powietrzu przez zadana ilosc czasu
 * 
 * \param[in] czas_sek - czas w sekundach, jak dlugo drona ma sie unosic
 * \param[in] LaczeDoGNUPlota
 * 
 */
void Drone::Wait(double czas_sek, PzG::LaczeDoGNUPlota& Lacze)
{
    double licznik = 0;
    while(true) {
        Translate({0,0,0});
        usleep(100'000);
        Draw(Lacze);
        licznik += 1;
        //std::cout<< licznik/10 << std::endl;
        if(licznik/10 >= czas_sek) break;
    }
}

/*!
 * \brief Metoda ustalajaca sciezke lotu drona
 * 
 * Wykorzystywany do tego jest argument typu Sciezka
 * i jej jego metoda \e UstalSciezke po uprzednim
 * odpowiednim zsumowaniu katow
 * 
 */
void Drone::CreatePath(const Vector3D& Polozenie_poczatkowe, double kat_skretu, double Dlugosc_lotu)
{
    kat_skretu += current_drone_rotation;
    path.CreatePath(Polozenie_poczatkowe, kat_skretu, Dlugosc_lotu);
}


/*!
 * \brief Metoda planujaca sciezke lotu drona
 *
 * Wykorzystywany do tego jest argument typu Sciezka
 * i jego metoda \e PlanujSciezke
 * 
 */
void Drone::PlanPath(PzG::LaczeDoGNUPlota& Lacze)
{
    path.PlanPath(Lacze);
}

/*!
 * \brief Metoda wyswietlajaca Sciezke lotu
 *
 * Wykorzystywany do tego jest argument typu Sciezka
 * i jego metoda \e WyswietlSciezke
 * 
 */
void Drone::ShowPath(std::ofstream& Plik) const
{
    path.ShowPath(Plik);
}

/*!
 * \brief Metoda inicjalizujaca sciezke lotu drona
 *
 * Do plikow sledzonych przez GNUPlota dodawany jest plik
 * zawierajacy sciezke
 */
void Drone::InitPath(PzG::LaczeDoGNUPlota& Lacze) const
{
    Lacze.DodajNazwePliku(PLIK_TRASY_PRZELOTU);
}

/*!
 * \brief Metoda sprawdzajaca czy dane polozenie jest zajete przez obiekt klasy Dron
 *
 * Sprawdzane jest czy odleglosc miedzy srodkami dronow jest wieksza od
 * dwoch promieni - czy drona na siebie nie nachodza
 * 
 * \param[in] Polozenie_drona - wektor polozenia aktualnie poruszanego drona
 * \param[in] Promien - promien aktualnie poruszanego drona
 * 
 * \retval false - jesli dane miejsce nie jest zajete przez obiekt klasy Dron
 * \retval true - jesli dane miejsce jest zajete przez obiekt klasy Dron
 * 
 */
bool Drone::IsOccupied(const Vector3D& Polozenie_drona, double Promien) const
{
    double odleglosc;
    Vector<2> Polozenie_drona_2D = Polozenie_drona;
    Vector<2> Polozenie_drona_this = Position;

    odleglosc = (Polozenie_drona_2D - Polozenie_drona_this).ObliczDlugosc();

    if(odleglosc > 2 * Promien) return false;

    return true;
}