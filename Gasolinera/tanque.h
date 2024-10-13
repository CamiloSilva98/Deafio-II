#ifndef TANQUE_H
#define TANQUE_H

#include <string>

class Tanque {
private:
    float capacidadRegular;
    float capacidadPremium;
    float capacidadEcoExtra;
    float precioRegular;
    float precioPremium;
    float precioEcoExtra;

public:
    Tanque(float capReg = 150, float capPre = 150, float capEco = 150);

    void setPrecio(float reg, float pre, float eco);
    float getPrecio(const std::string& categoria) const;
    bool venderCombustible(float cantidad, const std::string& categoria);
};

#endif // TANQUE_H
