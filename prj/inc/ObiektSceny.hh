#pragma once

class ObiektSceny
{
public:

    ObiektSceny() { }
    virtual ~ObiektSceny() { }
    virtual bool CzyLadowac() const { return false; }
};