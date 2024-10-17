#ifndef TANQUE_H
#define TANQUE_H

#include <string>
class EstacionServicio;
using namespace std;

class Tanque
{
private:
    double capacidadRegular, capacidadPremium, capacidadEcoExtra, cantidadRegular, cantidadPremium, cantidadEcoExtra,
 totalVendidoRegular, totalVendidoPremium, totalVendidoEcoExtra;
//precioRegular, precioPremium, precioEcoExtra,
public:
    Tanque();
    void asignarCapacidades();
    void restarCantidad(const string& categoria, double cantidad);
    double obtenerCantidad(const string& categoria) const;
   // double obtenerPrecio(const string& categoria) const;
   // void fijarPrecios(double regular, double premium, double ecoExtra);
    void verificarFugas() const;
};

#endif // TANQUE_H
