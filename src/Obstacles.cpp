#include "../inc/Obstacles.hh"


/*!
 * \brief Konstruktor bezparametryczny
 *
 * Ustawia Nazwe pliku wzorcowego i nadaje kat orientacji 0
 * 
 */
Obstacle::Obstacle(std::string NazwaPilku, const Vector3D& skala, const Vector3D& center, Type _type)
    : Figure(NazwaPilku, skala, Vector3D()), type(_type), Position(center) { }


std::string Obstacle::Identify() const
{
    switch(type) {
        case Ridge:
            return "Gora z dluga grania";
        case Pyramid:
            return "Gora z ostrym szczytem";
        case Plateau:
            return "Plaskowyz";
        default:
            return "Niezidentyfikowany obiekt";
    }
}

void Obstacle::CalculateLocalPosition() 
{
    std::ifstream PlikWzorcowy("bryly_wzorcowe/szescian_na_powierzchni.dat");
    std::stringstream buffer;
    buffer << PlikWzorcowy.rdbuf();

    if(!PlikWzorcowy.is_open()) {
        std::cerr << std::endl << "Blad otwarcia pliku: bryly_wzorcowe/szescian_na_powierzchni.dat" << std::endl;
    }

    Vector3D tmp;
    while(buffer>>tmp) {

        switch(type) {
            case Ridge:
                if(tmp[2] > 0.5)
                    if(tmp[0] < 0)
                        tmp[0] = fabs(tmp[0]);
                break;

            case Pyramid:
                if(tmp[2] > 0.5)
                    tmp[0] = tmp[1] = 0;
                else if(tmp[2] == 0.5) {
                    tmp[0] /= 2;
                    tmp[1] /= 2;
                }
                break;

            case Plateau:
                break;

            default: std::cerr << "wybrano zly typ przeszkody" <<std::endl; break;
        }        
        vertices.push_back(tmp);
    }

    for(Vector3D& vertex : vertices) {
        for(int i=0; i<WYMIAR; ++i) {
            vertex[i] = vertex[i] * Scale[i];
        }
    }
    PlikWzorcowy.close();
}

void Obstacle::Draw(PzG::LaczeDoGNUPlota& Lacze)
{
    Figure::Draw();
    Lacze.DodajNazwePliku(FinalFileName.c_str()).ZmienKolor(0);
    Lacze.Rysuj();
}

std::vector<Vector<2>> Obstacle::GetBorderCords() const
{
    std::vector<Vector<2>> vertex_cords;

    Vector<2> x_min, x_max, y_min, y_max;
    //nazewnictwo nie jest zbytnio istotne
    x_min[0] = Position[0] - Scale[0]/2;
    x_min[1] = Position[1] - Scale[1]/2;

    y_max[0] = Position[0] + Scale[0]/2;
    y_max[1] = Position[1] + Scale[1]/2;

    x_max[0] = Position[0] + Scale[0]/2;
    x_max[1] = x_min[1];

    y_min[0] = Position[0] - Scale[0]/2;
    y_min[1] = y_max[1];

    //  4.---------2.
    //  |          |
    //  |          |
    //  1.---------3.

    vertex_cords.push_back(x_min);
    vertex_cords.push_back(y_max);
    vertex_cords.push_back(x_max);
    vertex_cords.push_back(y_min);

    return vertex_cords;
}

bool Obstacle::IsOccupied(const Vector3D& Polozenie_drona, double Radius) const
{
    std::vector<Vector<2>> Cords2D =  GetBorderCords();
    double distance, x, y; //x to zmienna pomocnicza
    Vector<2> DronePosition = Polozenie_drona;
    Vector<2> ObstaclePosition = Position;

    distance = (DronePosition - ObstaclePosition).ObliczDlugosc();

    //case 1: lewo/prawo
    x = Radius + Scale[0]/2;
    y = Radius + Scale[1]/2;
    if(distance >= x && distance >= y)
    {
        //std::cout<<"Wolne na osi x i y plask"<<std::endl;
        return false;
    }

    //case 3,4,5,6: odleglosci od wierzcholkow
    for(unsigned int idx=0; idx<Cords2D.size(); ++idx) {
        distance = (DronePosition - Cords2D[idx]).ObliczDlugosc();
        if(distance <= Radius) return true;
    }
    
    return true;
}