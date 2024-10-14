#include "Tanque.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Tanque::Tanque() : capacidadRegular(0), capacidadPremium(0), capacidadEcoExtra(0),
    cantidadRegular(0), cantidadPremium(0), cantidadEcoExtra(0),
    precioRegular(0), precioPremium(0), precioEcoExtra(0) {}

void Tanque::asignarCapacidades() {
    capacidadRegular = 100 + (rand() % 101); // Entre 100 y 200 litros
    capacidadPremium = 100 + (rand() % 101);
    capacidadEcoExtra = 100 + (rand() % 101);

    cantidadRegular = capacidadRegular;
    cantidadPremium = capacidadPremium;
    cantidadEcoExtra = capacidadEcoExtra;

    cout << "Capacidades asignadas:\n";
    cout << "Regular: " << capacidadRegular << " litros\n";
    cout << "Premium: " << capacidadPremium << " litros\n";
    cout << "EcoExtra: " << capacidadEcoExtra << " litros\n";
}

void Tanque::restarCantidad(const std::string& categoria, double cantidad) {
    if (categoria == "Regular") {
        cantidadRegular -= cantidad;
    } else if (categoria == "Premium") {
        cantidadPremium -= cantidad;
    } else if (categoria == "EcoExtra") {
        cantidadEcoExtra -= cantidad;
    }
}

double Tanque::obtenerCantidad(const std::string& categoria) const {
    if (categoria == "Regular") {
        return cantidadRegular;
    } else if (categoria == "Premium") {
        return cantidadPremium;
    } else if (categoria == "EcoExtra") {
        return cantidadEcoExtra;
    }
    return 0;
}

double Tanque::obtenerPrecio(const std::string& categoria) const {
    if (categoria == "Regular") {
        return precioRegular;
    } else if (categoria == "Premium") {
        return precioPremium;
    } else if (categoria == "EcoExtra") {
        return precioEcoExtra;
    }
    return 0;
}

void Tanque::fijarPrecios(double regular, double premium, double ecoExtra) {
    precioRegular = regular;
    precioPremium = premium;
    precioEcoExtra = ecoExtra;
}

void Tanque::verificarFugas() const {
    double porcentajeRegular = (cantidadRegular / capacidadRegular) * 100;
    double porcentajePremium = (cantidadPremium / capacidadPremium) * 100; // cambiar la manera en que se verifica la fuga
    double porcentajeEcoExtra = (cantidadEcoExtra / capacidadEcoExtra) * 100;

    cout << "Verificación de fugas:\n";
    cout << "Regular: " << porcentajeRegular << "% disponible\n";
    cout << "Premium: " << porcentajePremium << "% disponible\n";
    cout << "EcoExtra: " << porcentajeEcoExtra << "% disponible\n";

    if (porcentajeRegular < 95 || porcentajePremium < 95 || porcentajeEcoExtra < 95) {
        cout << "¡Alerta! Posible fuga detectada en uno o más tanques.\n";
    } else {
        cout << "No se detectaron fugas. Todos los tanques están por encima del 95% de su capacidad.\n";
    }
}

