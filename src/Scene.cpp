#include "../inc/Scene.hh"

#include "../inc/Menu.hh"
#include <vector>
#include <unistd.h>


Scene::Scene() 
{
    Vector3D W1{50, 50, 0};
    GnuplotSetUp(Lacze);
    ObstacleCounter = 0;

    // drony zawsze na poczatku
    ChosenDrone = AddDrone(1, W1);
    AddRidge();
    AddPyramid();
    AddPlateau();
}

/*!
 * \brief Metoda wyswietlajaca menu programu
 */
void Scene::WyswietlMenu()
{
    std::cout<<"\n\t a - Wybierz aktywnego drona"<<std::endl;
    std::cout<<"\t p - Zadaj parametry przelotu"<<std::endl;
    std::cout<<"\t w - Podaj liczbe Vectorow"<<std::endl;
    std::cout<<"\t D - Dodaj drona"<<std::endl;
    std::cout<<"\t u - usun przeszkode"<<std::endl;
    std::cout<<"\t m - Wyswietl menu"<<std::endl<<std::endl;
    std::cout<<"\t k - Koniec dzialania programu"<<std::endl<<std::endl;
}

void Scene::RemoveObstacle() 
{
    int id;
    if(ObjectList.size() > 2) {
        std::cout << "Podaj numer przeszkody do usuniecia:";
        std::cin >> id; 
        for(std::shared_ptr<SceneObject>& obj: ObjectList) {
            if(obj->IsDrone()) continue;
                

        }
    }
    
}

/*!
 * \brief Metoda pozwalajaca na wybor drona
 *
 * W zaleznosci od wyboru drona (jest on ograniczony do 1 i 2)
 * zostaje zmieniony dron pomocniczy, ktory bedzie wykonywal zadany
 * przelot. W razie wyboru niepoprawnego liczby (id drona) zostanie
 * wyswitlony odpowiedni komunikat.
 */
void Scene::WyborDrona()
{
    int aktywny, pomocnicza = 0;
    std::cout<<"Aktualnie aktywny jest dron o wspolrzednych: "<<std::endl;
    ChosenDrone->PrintPosition();
    std::cout<<std::endl<<"Wybierz aktywnego drona: ";
    std::cin>>aktywny;
    for(const std::shared_ptr<Drone>& Dr : DroneList) {
        if(Dr->GetID() == aktywny) {
            ChosenDrone = Dr;
            ++pomocnicza;
        }
    }
    if(pomocnicza == 0) 
        std::cout<<"Nie udalo sie wybrac drona (mozliwy wybor: 1 lub 2)"<<std::endl;
}

/*!
 * \brief Metoda obslugujaca menu
 */
void Scene::Menu(char& wybor)
{
    switch(wybor)
    {
        case 'k':
            break;

        case 'm':
            WyswietlMenu();
            break;

        case 'a':
            PrintDrones();
            WyborDrona();
            break;
        
        case 'w':
            Vector3D::GetNumberOfVectors();
            break;

        case 'u':
            RemoveObstacle();

        case 'D':
            AddDrone();
            break;


        case 'p':
        Animate(ChosenDrone);
        Vector3D::GetNumberOfVectors();
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
 * \param[in] Wek - Vector przesuniecia drona na scenie
 * 
 * Tworzony jest wskaznik na obiekt klasy dron, nastepnie jest
 * on odpowiednio tworzony, transformowany do ukladu rodzica
 * i dodawany do listy dronow
 * 
 * \return _Dron - wskaznik na dodanego drona
 */
std::shared_ptr<Drone> Scene::AddDrone(unsigned int ID, const Vector3D& Wek)
{
    std::shared_ptr<Drone> _Dron = std::make_shared<Drone>(ID, Lacze);
    Lacze.Rysuj();

    _Dron->Translate(Wek);
    _Dron->Draw(Lacze);

    DroneList.push_back(_Dron);
    ObjectList.push_back(_Dron);

    return _Dron;
}

void Scene::AddRidge()
{
    std::ostringstream stream;
    stream << "dat/przeszkody/przeszkoda" << ++ObstacleCounter << ".dat";
    std::string name = stream.str();
    Vector3D pos{100, 100, 0}, scale{30,30,60};
    std::shared_ptr<Obstacle> _ridge = std::make_shared<Obstacle>(name, scale, pos, Type::Ridge);

    _ridge->Translate(pos);
    _ridge->Draw(Lacze);

    ObjectList.push_back(_ridge);
}

void Scene::AddPyramid()
{
    std::ostringstream stream;
    stream << "dat/przeszkody/przeszkoda" << ++ObstacleCounter << ".dat";
    std::string name = stream.str();
    Vector3D pos{150, 50, 0}, scale{30,20,70};
    std::shared_ptr<Obstacle> _pyramid = std::make_shared<Obstacle>(name, scale, pos, Type::Pyramid);

    _pyramid->Translate(pos);
    _pyramid->Draw(Lacze);

    ObjectList.push_back(_pyramid);
}

void Scene::AddPlateau()
{
    std::ostringstream stream;
    stream << "dat/przeszkody/przeszkoda" << ++ObstacleCounter << ".dat";
    std::string name = stream.str();
    Vector3D pos{150, 150, 0}, scale{30,50,20};
    std::shared_ptr<Obstacle> _plateau = std::make_shared<Obstacle>(name, scale, pos, Type::Plateau);

    _plateau->Translate(pos);
    _plateau->Draw(Lacze);

    ObjectList.push_back(_plateau);
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
void Scene::AddDrone()
{
    double wsp_x, wsp_y;
    int id_drona = DroneList.size() + 1;

    std::cout<<"Procedura dodawania drona..."<<std::endl;
    std::cout<<"Podaj wsporzedne drona (x,y): ";
    std::cin>>wsp_x>>wsp_y;

    AddDrone(id_drona, {wsp_x, wsp_y, 0});
}

void Scene::PrintDrones()
{
    std::cout<<"Aktualnie na scenie znajduje sie " << DroneList.size() << std::endl;

    for(const std::shared_ptr<Drone> &Dr : DroneList) {
        std::cout << Dr->GetID() << ". " << Dr->Identify() << std::endl;
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
bool Scene::IsOccupied(std::shared_ptr<Drone>& Dr)
{
    for(const std::shared_ptr<SceneObject>& Ob : ObjectList) {
        if(Ob == Dr) continue;
        if(Ob->IsOccupied(Dr->GetPosition(), Dr->GetRadius())) {
            Ob->Identify();
            std::cout << "Aktualna pozycja jest zajeta przez obiekt: " << Ob->Identify() << 
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
void Scene::Animate(std::shared_ptr<Drone> &Dr)
{
    double kat, dlugosc;
    Vector3D Polozenie_poczatkowe = Dr->GetPosition();
    
    std::cout<<"Podaj kierunek lotu (kat w stopniach): ";
    std::cin>>kat;
    std::cout<<"Podaj dlugosc lotu: ";
    std::cin>>dlugosc;

    Dr->InitPath(Lacze);
    Dr->CreatePath(Polozenie_poczatkowe, kat, dlugosc);
    Dr->PlanPath(Lacze);

    Dr->FlyVertical(80, Lacze);
    Dr->Rotation(kat, Lacze);
    Dr->FlyHorizontal(dlugosc, Lacze);

    while(IsOccupied(Dr)) {
        dlugosc += 30;
        Dr->ClearPath(Lacze);
        Dr->CreatePath(Polozenie_poczatkowe, 0, dlugosc);
        Dr->PlanPath(Lacze);
        Dr->Wait(2, Lacze);
        Dr->FlyHorizontal(30, Lacze);
    }
    
    Dr->FlyVertical(-80 ,Lacze);
    Dr->ClearPath(Lacze);
    Lacze.UsunNazwePliku(PLIK_TRASY_PRZELOTU);

    Dr->PrintPosition();
}