#include "../inc/Macierz3x3.hh"

#include <cmath>
#include <iostream>
#include <iomanip>

/*!
 * \brief Konstruktor bezparametryczny obiektu Macierz
 * 
 * \tparam WYMIAR - rozmiar macierzy
 * 
 * tworzy obiekt Macierz jako macierz jednostkowa
 */
Matrix3x3::Matrix3x3()
{
    for(int i=0; i<WYMIAR; ++i)
    {
        for(int j=0; j<WYMIAR; ++j) {
        if(i==j)
            wart[i][j] = 1;
        else
            wart[i][j] = 0;
        }
    }
}

Matrix3x3::Matrix3x3(Axis axis, double angle_deg)
{
    double rad = angle_deg*M_PI/180;

    switch(axis) {
        case Axis::OX:
            wart[1][1] = cos(rad);
            wart[1][2] = -sin(rad);
            wart[2][1] = sin(rad);
            wart[2][2] = cos(rad);
            wart[0][0] = 1;
            wart[1][0] = wart[0][1] = wart[0][2] = wart[2][0] = 0;
            break;

        case Axis::OY:
            wart[0][0] = cos(rad);
            wart[2][0] = -sin(rad);
            wart[0][2] = sin(rad);
            wart[2][2] = cos(rad);
            wart[1][1] = 1;
            wart[1][0] = wart[0][1] = wart[1][2] = wart[2][1] = 0;
            break;

        case Axis::OZ:
            wart[0][0] = cos(rad);
            wart[0][1] = -sin(rad);
            wart[1][0] = sin(rad);
            wart[1][1] = cos(rad);
            wart[2][2] = 1;
            wart[2][0] = wart[2][1] = wart[0][2] = wart[1][2] = 0;
            break;
    }
}


/*!
 * \brief Konstruktor bezparametryczny obiektu Macierz
 * 
 * \tparam WYMIAR - rozmiar macierzy
 * 
 * tworzy obiekt Macierz jako macierz jednostkowa
 */
Matrix3x3::Matrix3x3(int liczba)
{
    for(int i=0; i<WYMIAR; ++i) {
        for(int j=0; j<WYMIAR; ++j) {
            wart[i][j] = liczba;
        }
    }
}

/*!
 * \brief Metoda generujaca macierz obrotu wokol osi OZ
 *
 * odpowiednio wypelnia pola macierzy, tak aby spelniala ona wymagania dla obrotu wokol OZ
 * 
 * \param[in] kat - kat w radianach dla jakiego trzeba obliczyc macierz obrotu
 * 
 * \return MacObr - macierz obrotu OZ
 */
void Matrix3x3::ObrotZ(double kat)
{
    //Macierz3x3 MacObr = Macierz3x3();
    //double Rad = kat*M_PI/180;   //zamiana na radiany
    (*this)(0,0) =  cos(kat);
    (*this)(0,1) = -1*(sin(kat));
    (*this)(1,0) =  sin(kat);
    (*this)(1,1) =  cos(kat);
}

/*!
 * \brief Przeciazenie operatora mnozenia macierzy przez wektor
 * 
 * \tparam WYMIAR - rozmiar macierzy i wektora
 * \param[in] wektor - Wektor mnozony
 * 
 * \return Wynik - wektor, bedacy iloczynem macierzy przez wektor
 * 
 */
Wektor3D Matrix3x3::operator* (const Wektor3D& wektor) const
{
    Wektor3D wynik;
    for(int i=0; i<WYMIAR; ++i)
    {
        for(int j=0; j<WYMIAR; ++j)
        {
        wynik[i] += (wart[i][j] * wektor[j]);
        }
    }
    return wynik;
}


/*!
 * \brief Przeciazenie operatora mnozenia wektorow
 * 
 * \tparam WYMIAR - rozmiar wektorow
 * \param[in] wektor - Wektor mnozony
 * 
 * \return Wynik - wektor, bedacy iloczynem wektorowym wektorow
 * 
 */
Matrix3x3 Matrix3x3::operator* (const Matrix3x3& macierz) const
{
    Matrix3x3 wynik(0);  //musi byc zerowa bo inaczej wyjdzie zle
    for(int i=0; i<WYMIAR; ++i) 
    {
        for(int j=0; j<WYMIAR; ++j)
        {
        for(int k=0; k<WYMIAR; ++k)
        {
            wynik(i, j) += (wart[i][k] * macierz(k, j));
        }
        }
    }
    return wynik;
}

/*!
 * \brief Przeciazenie operatora przesuniecia bitowego w lewo dla obiektow klasy Macierz
 * 
 * \tparam WYMIAR - rozmiar
 * 
 * \param[in] Strm - strumien wyjsciowy
 * \param[in] Mac - macierz do wypisania
 * 
 * \return strumien z odpowiednio sformatowana macierza
 * 
 */
inline std::ostream& operator << (std::ostream &Strm, const Matrix3x3 &Mac)
{
    for(int i=0; i<WYMIAR; ++i)
    {
        for(int j=0; j<WYMIAR; ++j)
        {
        Strm << std::setw(16) << std::fixed << std::setprecision(10) << Mac(i, j);
        }
        Strm<<std::endl;
    }
    return Strm;  
}

/*!
 * \brief Przeciazenie operatora przesuniecia bitowego w prawo dla obiektow klasy Macierz
 * 
 * \tparam WYMIAR - rozmiar
 * 
 * \param[in] Strm - strumien wejsciowy
 * \param[in] Mac - macierz do wypisania
 * 
 * \return strumien z odpowiednio sformatowana macierza
 * 
 */
inline std::istream& operator >> (std::istream &Strm, Matrix3x3 &Mac)
{
    for(int i=0; i<WYMIAR; ++i)
    {
        for(int j=0; j<WYMIAR; ++j)
        {
        Strm>>Mac(i,j);
        if(Strm.fail())
            return Strm;
        }
    }
    return Strm;
}