#pragma once

#include <string>

class ObiektSceny
{
public:

    ObiektSceny() { }
    virtual ~ObiektSceny() { }
    virtual bool CzyDron() const { return false; }
    virtual bool CzyLadowac() const { return false; }

    virtual std::string Identyfikuj() const { return "Bryla Geometryczna"; }
    virtual bool SprawdzID(unsigned int) const { return false; }
    virtual double PokazID() const { return 0; }
    virtual const char* ZwrocNazwePlikuFinalnego() const { return "obiekt sceny"; }
};