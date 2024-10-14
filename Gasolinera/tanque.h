#ifndef TANQUE_H
#define TANQUE_H

#include <string>
using namespace std;

class Tanque {
private:
    double capacidadRegular;
    double capacidadPremium;
    double capacidadEcoExtra;
    double cantidadRegular;
    double cantidadPremium;
    double cantidadEcoExtra;
    double precioRegular;
    double precioPremium;
    double precioEcoExtra;

public:
    Tanque();
    void asignarCapacidades();
    void restarCantidad(const string& categoria, double cantidad);
    double obtenerCantidad(const string& categoria) const;
    double obtenerPrecio(const string& categoria) const;
    void fijarPrecios(double regular, double premium, double ecoExtra);
    void verificarFugas() const;
};

#endif // TANQUE_H
