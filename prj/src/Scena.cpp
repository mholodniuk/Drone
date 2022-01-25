#include "../inc/Scena.hh"

#include "../inc/Menu.hh"
#include <vector>
#include <unistd.h>


Scena::Scena() {
  
}

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
}

/*!
 * \brief Metoda wyswietlajaca menu programu
 */
void Scena::WyswietlMenu()
{
  std::cout<<"\n\t a - Wybierz aktywnego drona"<<std::endl;
  std::cout<<"\t p - Zadaj parametry przelotu"<<std::endl;
  std::cout<<"\t w - Podaj liczbe wektorow"<<std::endl;
  std::cout<<"\t D - Dodaj drona"<<std::endl;
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


    case 'D':
      DodajDrona();
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
  std::shared_ptr<Dron> _Dron = std::make_shared<Dron>(ID, Lacze);

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
    dlugosc += 30;
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