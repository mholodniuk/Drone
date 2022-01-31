#pragma once

#include "BrylaGeometryczna.hh"
#include "lacze_do_gnuplota.hh"
#include "ObiektSceny.hh"

class Ridge : public Figure, public SceneObject {

public:

    Ridge(std::string NazwaPilku, const Wektor3D& skala, const Wektor3D& center);

    void CalculateLocalPosition() override;
    void Draw(PzG::LaczeDoGNUPlota& Lacze);

    bool IsOccupied(const Wektor3D& Polozenie_drona, double Promien) const override { return false; }
    
    //! \brief Metody identyfikujace
    std::string Identify() const override {return "aaa";};
    const char* GetFileName() const override { return std::string("przeszkoda typu ...").c_str(); }

};