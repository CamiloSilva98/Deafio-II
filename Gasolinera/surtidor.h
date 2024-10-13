#ifndef SURTIDOR_H
#define SURTIDOR_H

#include "tanque.h"
#include <string>

class Surtidor {
private:
    int codigo;
    std::string modelo;
    static const int MAX_TRANSACCIONES = 100; // Definimos un máximo de transacciones
    std::string historialTransacciones[MAX_TRANSACCIONES];
    int numTransacciones;
    float ventasTotales;

public:
    Surtidor(int codigo, std::string modelo);
    void venderCombustible(float cantidad, const std::string& categoria, const std::string& metodoPago, const std::string& docCliente, Tanque& tanque);
    void mostrarHistorial() const;
    float getVentasTotales() const;
    int getCodigo() const;
};

#endif // SURTIDOR_H
