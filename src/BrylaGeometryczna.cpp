#include "../inc/BrylaGeometryczna.hh"
#include <string.h>
#include <fstream>
#include <cmath>


Figure::Figure(std::string NazwaPilku,const Wektor3D& skala, const Wektor3D& center)
    : FinalFileName(NazwaPilku), Scale(skala), Orientation_deg(0), GlobalOrientation(Matrix3x3()), LocalCenter(center) { }


/*!
 * \brief Metoda Obracajaca Prostopadloscian
 * 
 * Obliczana jest macierz obrotu dla danego kata
 * i na jej podstawie obliczane jest polozenie po obrocie
 *
 */
void Figure::Rotate() 
{
    Matrix3x3 MatrixRot(Matrix3x3::Axis::OZ, Orientation_deg);

    for(Wektor3D& wierzcholek : vertices) {
        wierzcholek = MatrixRot * wierzcholek;
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
bool Figure::Draw()
{
    std::ofstream FileFile(FinalFileName);

    if(!FileFile.is_open()) {
        std::cerr<<std::endl<<"Blad otwarcia pliku: "<<FinalFileName<<std::endl;
        return false;
    }

    int i=0;
    for(const auto& vertex : vertices) { 
        if(i != 0 && i % 4 == 0) FileFile << "\n";
        i++;
        FileFile << vertex;
    }
    vertices.clear();
    FileFile.close();
    
    return !FileFile.fail();
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
void Figure::Translate(const Wektor3D& Wek)
{   
    CalculateLocalPosition();
    Rotate();
    for(Wektor3D& vertex : vertices) {
        vertex += (Wek+GlobalOrientation*LocalCenter);
    }
}