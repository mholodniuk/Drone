#pragma once

#include "Figure.hh"
#include "lacze_do_gnuplota.hh"
#include "SceneObject.hh"

enum Type {Ridge, Pyramid, Plateau};

class Obstacle : public Figure, public SceneObject {

    Type type;
    Vector3D Position;

public:

    Obstacle(std::string fileName, const Vector3D& scale, const Vector3D& center, Type typ);

    void CalculateLocalPosition() override;
    void Draw(PzG::LaczeDoGNUPlota& Lacze);

    virtual bool IsOccupied(const Vector3D& Drone_position, double Radius) const override;
    std::vector<Vector<2>> GetBorderCords() const;
    
    //! \brief Metody identyfikujace
    std::string Identify() const override;
    const char* GetFileName() const override { return std::string("przeszkoda typu ...").c_str(); }

};