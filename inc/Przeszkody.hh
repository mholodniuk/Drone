#pragma once

#include "BrylaGeometryczna.hh"
#include "lacze_do_gnuplota.hh"
#include "ObiektSceny.hh"

enum Type {Ridge, Pyramid, Plateau};

class Obstacle : public Figure, public SceneObject {

    Type type;

public:

    Obstacle(std::string NazwaPilku, const Wektor3D& skala, const Wektor3D& center, Type typ);

    void CalculateLocalPosition() override;
    void Draw(PzG::LaczeDoGNUPlota& Lacze);

    bool IsOccupied(const Wektor3D& Polozenie_drona, double Promien) const override { return false; }
    
    //! \brief Metody identyfikujace
    std::string Identify() const override {return "aaa";};
    const char* GetFileName() const override { return std::string("przeszkoda typu ...").c_str(); }

};