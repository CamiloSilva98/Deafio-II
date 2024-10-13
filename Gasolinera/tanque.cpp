#include "tanque.h"

Tanque::Tanque(float capReg, float capPre, float capEco)
    : capacidadRegular(capReg), capacidadPremium(capPre), capacidadEcoExtra(capEco),
    precioRegular(0), precioPremium(0), precioEcoExtra(0) {}

void Tanque::setPrecio(float reg, float pre, float eco) {
    precioRegular = reg;
    precioPremium = pre;
    precioEcoExtra = eco;
}

float Tanque::getPrecio(const std::string& categoria) const {
    if (categoria == "Regular") return precioRegular;
    if (categoria == "Premium") return precioPremium;
    if (categoria == "EcoExtra") return precioEcoExtra;
    return 0;
}

bool Tanque::venderCombustible(float cantidad, const std::string& categoria) {
    if (categoria == "Regular" && capacidadRegular >= cantidad) {
        capacidadRegular -= cantidad;
        return true;
    }
    if (categoria == "Premium" && capacidadPremium >= cantidad) {
        capacidadPremium -= cantidad;
        return true;
    }
    if (categoria == "EcoExtra" && capacidadEcoExtra >= cantidad) {
        capacidadEcoExtra -= cantidad;
        return true;
    }
    return false; // No hay suficiente combustible en el tanque
}
