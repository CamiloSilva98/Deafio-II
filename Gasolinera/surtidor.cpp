#include "surtidor.h"
#include <iostream>

Surtidor::Surtidor(int codigo, std::string modelo)
    : codigo(codigo), modelo(modelo), numTransacciones(0), ventasTotales(0) {}

void Surtidor::venderCombustible(float cantidad, const std::string& categoria, const std::string& metodoPago, const std::string& docCliente, Tanque& tanque) {
    if (tanque.venderCombustible(cantidad, categoria)) {
        float precioPorLitro = tanque.getPrecio(categoria);
        float totalVenta = cantidad * precioPorLitro;
        ventasTotales += totalVenta;

        if (numTransacciones < MAX_TRANSACCIONES) {
            historialTransacciones[numTransacciones] = "Venta: " + std::to_string(cantidad) + "L de " + categoria +
                                                       " a " + metodoPago + " (" + docCliente + ") - $" +
                                                       std::to_string(totalVenta);
            numTransacciones++;
        }
    } else if (numTransacciones < MAX_TRANSACCIONES) {
        historialTransacciones[numTransacciones] = "Fallo en venta: No suficiente " + categoria;
        numTransacciones++;
    }
}

void Surtidor::mostrarHistorial() const {
    for (int i = 0; i < numTransacciones; i++) {
        std::cout << historialTransacciones[i] << std::endl;
    }
}

float Surtidor::getVentasTotales() const {
    return ventasTotales;
}

int Surtidor::getCodigo() const {
    return codigo;
}
