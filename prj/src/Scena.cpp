#include "Scena.hh"

#include "Menu.hh"
#include <vector>
#include <unistd.h>

/*!
 * \brief Metoda ustawiajaca Drony na scenie
 *
 * Drony sa tworzone i ustawiane "na szytwno"
 * 
 */
void Scena::TworzScene()
{
  UstawGNUPlot(Lacze);
  lPrzeszkod = 0;

  UstawDrony();
  UstawPrzeszkody();
}

/*!
 * \brief Metoda wyswietlajaca menu programu
 */
void Scena::WyswietlMenu()
{
  std::cout<<"\n\t a - Wybierz aktywnego drona"<<std::endl;
  std::cout<<"\t p - Zadaj parametry przelotu"<<std::endl;
  std::cout<<"\t w - Podaj liczbe wektorow"<<std::endl;
  std::cout<<"\t d - Dodaj przeszkode"<<std::endl;
  std::cout<<"\t D - Dodaj drona"<<std::endl;
  std::cout<<"\t u - Usun przeszkode"<<std::endl;
  std::cout<<"\t m - Wyswietl menu"<<std::endl<<std::endl;
  std::cout<<"\t k - Koniec dzialania programu"<<std::endl<<std::endl;
}

/*!
 * \brief Metoda pozwalajaca na wybor drona
 *
 * W zaleznosci od wyboru drona (jest on ograniczony do 1 i 2)
 * zostaje zmieniony dron pomocniczy, ktory bedzie wykonywal zadany
 * przelot. W razie wyboru niepoprawnego liczby (id drona) zostanie
 * wyswitlony odpowiedni komunikat.
 */
void Scena::WyborDrona()
{
  int aktywny, pomocnicza = 0;
  std::cout<<"Aktualnie aktywny jest dron o wspolrzednych: "<<std::endl;
  Dron_wybrany->PodajWspolrzedne();
  std::cout<<std::endl<<"Wybierz aktywnego drona: ";
  std::cin>>aktywny;
  for(const std::shared_ptr<Dron>& Dr : ListaDronow)
  {
    if(Dr->ZwrocID() == aktywny)
    {
      Dron_wybrany = Dr;
      ++pomocnicza;
    }
  }
  if(pomocnicza == 0) 
    std::cout<<"Nie udalo sie wybrac drona (mozliwy wybor: 1 lub 2)"<<std::endl;
}

/*!
 * \brief Metoda obslugujaca menu
 */
void Scena::Menu(char& wybor)
{
  switch(wybor)
  {
    case 'k':
      break;

    case 'm':
      WyswietlMenu();
      break;

    case 'a':
      WyswietlDrony();
      WyborDrona();
      break;
    
    case 'w':
      Wektor3D::ZwrocIloscWektorow();
      break;

    case 'd':
      DodajPrzeszkode();
      break;

    case 'D':
      DodajDrona();
      break;

    case 'u':
      UsunPrzeszkode();
      break;

    case 'p':
      LotDrona(Dron_wybrany);
      Wektor3D::ZwrocIloscWektorow();
      break;

    default:
      std::cout<<"Wybrano niepoprawna opcje :("<<std::endl;
      break;
  }
}

/*!
 * \brief Metoda Dodajaca drona do sceny
 *
 * \param[in] ID - id drona dodawanego
 * \param[in] Wek - wektor przesuniecia drona na scenie
 * 
 * Tworzony jest wskaznik na obiekt klasy dron, nastepnie jest
 * on odpowiednio tworzony, transformowany do ukladu rodzica
 * i dodawany do listy dronow
 * 
 * \return _Dron - wskaznik na dodanego drona
 */
std::shared_ptr<Dron> Scena::DodajDrona(unsigned int ID, const Wektor3D& Wek)
{
  std::shared_ptr<Dron> _Dron = std::make_shared<Dron>();

  _Dron->TworzDrona(ID, Lacze);
  _Dron->TransDoUklRodzica(Wek, Lacze);

  ListaDronow.push_back(_Dron);
  ListaObiektow.push_back(_Dron);

  return _Dron;
}

/*!
 * \brief Metoda Ustawiajaca drony w odpowiednich miejscach na scenie
 *
 * Dodatkowo jako dron wybrany (ten ktory bedzie wykonywal lot) jest
 * ustawiony jako dron nr 1.
 * 
 */
void Scena::UstawDrony()
{
  Wektor3D W1 = {20, 50, 0}; Wektor3D W2 = {150, 100, 0};

  Dron_wybrany = DodajDrona(1, W1);
  DodajDrona(2, W2);
}

/*!
 * \brief Metoda Dodajaca drona
 *
 * \pre mozna dodac maksymalnie 3 drony
 * 
 * Z powodu ograniczonej ilosci folderow na zestawy
 * plikow opisujace drona, maksymalnie mozna dodac do trzech 
 * dronow. Dodany drona jest umiejscawiany na wskazanym miejscu
 * 
 */
void Scena::DodajDrona()
{
  double wsp_x, wsp_y;
  int id_drona = ListaDronow.size() + 1;

  std::cout<<"Procedura dodawania drona..."<<std::endl;
  std::cout<<"Podaj wsporzedne drona (x,y): ";
  std::cin>>wsp_x>>wsp_y;

  DodajDrona(id_drona, {wsp_x, wsp_y, 0});
}

void Scena::WyswietlDrony()
{
  std::cout<<"Aktualnie na scenie znajduje sie " << ListaDronow.size() << std::endl;

  for(const std::shared_ptr<Dron> &Dr : ListaDronow)
  {
    std::cout << Dr->ZwrocID() << ". " << Dr->Identyfikuj() << std::endl;
  }
  std::cout<<std::endl;
}

/*!
 * \brief Metoda Dodajaca gore z dluga grania do sceny
 *
 * \pre ID musi byc liczba dodatnia rozna od poprzednio dodanych przeszkod
 * 
 * \param[in] ID - id przeszkody (ktora z kolei)
 * 
 * Tworzony jest wskaznik na obiekt klasy GoraZDlugaGRania, nastepnie
 * pobierane sa odpowiednie wartosci od uzytkownika, potem stworzony 
 * i wyswietlony zostaje odpowiedni obiekt. Po tej procedurze wskaznik
 * na ten obiekt zostaje dodany do listy przeszkod
 * 
 */
void Scena::DodajGoreZDlugaGrania(unsigned int ID)
{
  std::shared_ptr<GoraZDlugaGrania> _GoraZDlugaGrania = std::make_shared<GoraZDlugaGrania>();

  int wsp_x, wsp_y;
  Wektor3D Skala, Polozenie_przeszkody;

  std::cout<<"Procedura dodawania przeszkody..."<<std::endl;
  std::cout<<"Podaj wspolrzedne srodka podstawy (x,y): ";
  std::cin>>wsp_x>>wsp_y;
  Polozenie_przeszkody = _GoraZDlugaGrania->UstawPolozenie(wsp_x, wsp_y);
  std::cout<<"Podaj scale wzdluz kolejnych osi OX, OY, OZ.\nWsprowadz skale:";
  std::cin>>Skala;

  _GoraZDlugaGrania->UstawSkale(Skala);
  _GoraZDlugaGrania->TworzGoreZDlugaGrania(ID, Lacze);
  _GoraZDlugaGrania->TransDoUklRodzica(Polozenie_przeszkody, Lacze);

  ListaObiektow.push_back(_GoraZDlugaGrania);
}

/*!
 * \brief Metoda Dodajaca gore z ostrym szczytem do sceny
 *
 * \pre ID musi byc liczba dodatnia rozna od poprzednio dodanych przeszkod
 * 
 * \param[in] ID - id przeszkody (ktora z kolei)
 * 
 * Tworzony jest wskaznik na obiekt klasy GoraZOstrymSzczytem, nastepnie
 * pobierane sa odpowiednie wartosci od uzytkownika, potem stworzony 
 * i wyswietlony zostaje odpowiedni obiekt. Po tej procedurze wskaznik
 * na ten obiekt zostaje dodany do listy przeszkod
 * 
 */
void Scena::DodajGoreZOstrymSzczytem(unsigned int ID)
{
  std::shared_ptr<GoraZOstrymSzczytem> _GoraZOstrymSzczytem = std::make_shared<GoraZOstrymSzczytem>();

  int wsp_x, wsp_y;
  Wektor3D Skala, Polozenie_przeszkody;

  std::cout<<"Procedura dodawania przeszkody..."<<std::endl;
  std::cout<<"Podaj wspolrzedne srodka podstawy (x,y): ";
  std::cin>>wsp_x>>wsp_y;
  Polozenie_przeszkody = _GoraZOstrymSzczytem->UstawPolozenie(wsp_x, wsp_y);
  std::cout<<"Podaj scale wzdluz kolejnych osi OX, OY, OZ.\nWsprowadz skale:";
  std::cin>>Skala;

  _GoraZOstrymSzczytem->UstawSkale(Skala);
  _GoraZOstrymSzczytem->TworzGoreZOstrymSzczytem(ID, Lacze);
  _GoraZOstrymSzczytem->TransDoUklRodzica(Polozenie_przeszkody, Lacze);

  ListaObiektow.push_back(_GoraZOstrymSzczytem);
}

/*!
 * \brief Metoda Dodajaca Plaskowyz do sceny
 *
 * \pre ID musi byc liczba dodatnia rozna od poprzednio dodanych przeszkod
 * 
 * \param[in] ID - id przeszkody (ktora z kolei)
 * 
 * Tworzony jest wskaznik na obiekt klasy Plaskowyz, nastepnie
 * pobierane sa odpowiednie wartosci od uzytkownika, potem stworzony 
 * i wyswietlony zostaje odpowiedni obiekt. Po tej procedurze wskaznik
 * na ten obiekt zostaje dodany do listy przeszkod
 * 
 */
void Scena::DodajPlaskowyz(unsigned int ID)
{
  std::shared_ptr<Plaskowyz> _Plaskowyz = std::make_shared<Plaskowyz>();

  int wsp_x, wsp_y;
  Wektor3D Skala, Polozenie_przeszkody;

  std::cout<< std::endl <<"Procedura dodawania przeszkody..."<<std::endl;
  std::cout<<"Podaj wspolrzedne srodka podstawy (x,y): ";
  std::cin>>wsp_x>>wsp_y;
  Polozenie_przeszkody = _Plaskowyz->UstawPolozenie(wsp_x, wsp_y);
  std::cout<<"Podaj scale wzdluz kolejnych osi OX, OY, OZ.\nWsprowadz skale:";
  std::cin>>Skala;

  _Plaskowyz->UstawSkale(Skala);
  _Plaskowyz->TworzPlaskowyz(ID, Lacze);
  _Plaskowyz->TransDoUklRodzica(Polozenie_przeszkody, Lacze);

  ListaObiektow.push_back(_Plaskowyz);
}

/*!
 * \brief Metoda Ustawiajaca trzy przeszkody w odpowiednich miejscach na scenie
 */
void Scena::UstawPrzeszkody()
{
  std::shared_ptr<Plaskowyz> _Plaskowyz = std::make_shared<Plaskowyz>();
  std::shared_ptr<GoraZDlugaGrania> _GoraZDlugaGrania = std::make_shared<GoraZDlugaGrania>();
  std::shared_ptr<GoraZOstrymSzczytem> _GoraZOstrymSzczytem = std::make_shared<GoraZOstrymSzczytem>();

  Wektor3D skala = {30, 40, 60};
  Wektor3D tab[] = {{150,150,0}, {50,150,0}, {70,50,0}};
  _Plaskowyz->UstawSkale(skala);
  _Plaskowyz->TworzPlaskowyz(++lPrzeszkod, Lacze);
  _Plaskowyz->TransDoUklRodzica(tab[0], Lacze);
  ListaObiektow.push_back(_Plaskowyz);

  _GoraZDlugaGrania->UstawSkale(skala);
  _GoraZDlugaGrania->TworzGoreZDlugaGrania(++lPrzeszkod, Lacze);
  _GoraZDlugaGrania->TransDoUklRodzica(tab[1], Lacze);
  ListaObiektow.push_back(_GoraZDlugaGrania);

  _GoraZOstrymSzczytem->UstawSkale(skala);
  _GoraZOstrymSzczytem->TworzGoreZOstrymSzczytem(++lPrzeszkod, Lacze);
  _GoraZOstrymSzczytem->TransDoUklRodzica(tab[2], Lacze);
  ListaObiektow.push_back(_GoraZOstrymSzczytem);
}

/*!
 * \brief Metoda pozwalajaca dodanie nowej przeszkody do listy sceny
 * 
 * Wykorzystywane zostaja poszczegolne metody dodajace przeszkody, 
 * a przy kazdej operacji zwieksza sie licznik sumujacy wszystkie przeszkody
 * 
 */
void Scena::DodajPrzeszkode()
{
  int typ;

  std::cout << std::endl << "Podaj rodzaj elementu powierzchni" << std::endl << std::endl;
  std::cout << "1 - Gora z ostrym szczytem\n2 - Gora z dluga grania\n3 - Plaskowyz\n" << std::endl;
  std::cout << "Wprowadz numer typu elementu: ";
  std::cin>>typ;
  switch (typ)
  {
  case 1:
    DodajGoreZOstrymSzczytem(++lPrzeszkod);
    break;
  
  case 2:
    DodajGoreZDlugaGrania(++lPrzeszkod);
    break;

  case 3:
    DodajPlaskowyz(++lPrzeszkod);
    break;

  default:
    std::cout<<":( Nie ma takiej opcji"<<std::endl;
    break;
  }
}
/*!
 * \brief Metoda wypisujaca wszystkie przeszkody
 *
 * Przeszkody zostaja odpowiednio wypisane, tak aby
 * dalo sie je odroznic
 * 
 * \note po usunieciu przeszkody o danym numerze, numery pozostalych sie nie zmieniaja
 * 
 */
void Scena::PokazPrzeszkody()
{
  std::cout<<std::endl<<"Wybierz element powierzchni do usuniecia: " <<std::endl;
  for(const std::shared_ptr<ObiektSceny> &Br : ListaObiektow)
  {
    if(!Br->CzyDron())
      std::cout << Br->PokazID() << ". " << Br->Identyfikuj() << std::endl;
  }
  std::cout<<std::endl;
}

/*!
 * \brief Metoda umozliwiajaca usuniecie danej przeszkody ze sceny
 *
 * Po pobraniu od uzytkownika id przeszkody, ktora chcemy usunac,
 * sprawdzane jest ono z kolejnymi obiektami na liscie, a gdy zostaje 
 * odnaleziony obiekt o odpowiendnim id - zostaje on usuniety
 * 
 */
void Scena::UsunPrzeszkode()
{ 
  int nr_przeszkody;
  PokazPrzeszkody();

  if(ListaObiektow.size()>=2)
  {
    std::cout<<"Podaj numer elementu: ";
    std::cin >> nr_przeszkody;
  
    for(const std::shared_ptr<ObiektSceny> &Br : ListaObiektow)
    {
      if(Br->SprawdzID(nr_przeszkody))
      {
        std::cout<<"Usuwanie przeszkody z listy..." << std::endl;
        Lacze.UsunNazwePliku(Br->ZwrocNazwePlikuFinalnego());
        Lacze.Rysuj();
        ListaObiektow.remove(Br);
        break;
      }
    }
  }
    else std::cout<<"Brak przeszkod do usuniecia!"<<std::endl;
}

/*!
 * \brief Metoda sprawdzajaca czy dane polozenie jest zajete przez Obiekt z listy obiektow
 *
 * Po kolei, obszar zajmowany przez kazdego z obiektow sceny jest sprawdzane
 * czy nie naklada sie z obszarem zajmowanym przez drona podanego w
 * argumencie (jest to dron wybrany, poruszajacy sie).
 * 
 * \param[in] Dr - wskaznik na aktualnie aktywnego drona
 * 
 * \retval false - jesli dane miejsce nie jest zajete przez obiekt sceny
 * \retval true - jesli dane miejsce jest zajete przez obiekt sceny
 * 
 */
bool Scena::CzyZajete(std::shared_ptr<Dron>& Dr)
{
  for(const std::shared_ptr<ObiektSceny>& Ob : ListaObiektow)
  {
    if(Ob == Dr) continue;
    if(Ob->CzyZajete(Dr->ZwrocPolozenie(), Dr->ZwrocPromien()))
    {
      std::cout << "Aktualna pozycja jest zajeta przez obiekt: " << Ob->Identyfikuj() << 
      std:: endl << "Przedluzam lot....." << std::endl << std::endl;

      return true;
    }
  }
  return false;
}

/*!
 * \brief Metoda realizujaca lot drona
 *
 * Po kolei zostaje wykonywana animacja lotu w gore, obrotu,
 * lotu do celu, a nastepnie sprawdzenia zajetosci miejsca
 * docelowego, jesli jest ono wolne - dron wyladuje; jesli nie
 * - dron poleci 20 jednostke dalej. Na koncu zostaje pokazane
 * polozenie ostateczne drona po wyladowaniu.
 * 
 * \param[in] Dr - wskaznik na aktualnie aktywnego drona
 * 
 */
void Scena::LotDrona(std::shared_ptr<Dron> &Dr)
{
  double kat, dlugosc;
  Wektor3D Polozenie_poczatkowe = Dr->ZwrocPolozenie();
  
  std::cout<<"Podaj kierunek lotu (kat w stopniach): ";
  std::cin>>kat;
  std::cout<<"Podaj dlugosc lotu: ";
  std::cin>>dlugosc;

  Dr->InicjalizujSciezke(Lacze);
  Dr->UstalSciezke(Polozenie_poczatkowe, kat, dlugosc);
  Dr->PlanujSciezke(Lacze);

  Dr->LotPionowy(80, Lacze);
  Dr->Obrot(kat, Lacze);
  Dr->LotDoPrzodu(dlugosc, Lacze);

  while(CzyZajete(Dr))
  {
    dlugosc+=30;
    Dr->WyczyscSciezke(Lacze);
    Dr->UstalSciezke(Polozenie_poczatkowe, 0, dlugosc);
    Dr->PlanujSciezke(Lacze);
    Dr->Czekaj(2, Lacze);
    Dr->LotDoPrzodu(30, Lacze);
  }
  
  Dr->LotPionowy(-80 ,Lacze);
  Dr->WyczyscSciezke(Lacze);
  Lacze.UsunNazwePliku(PLIK_TRASY_PRZELOTU);

  Dr->PodajWspolrzedne();
}