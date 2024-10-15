#include "estacion_servicio.h"
#include <iostream>
#include <cstdlib> // Para rand()

EstacionServicio::EstacionServicio(std::string nombre, int codigo, std::string gerente, std::string region, std::string ubicacionGPS)
    : nombre(nombre), codigo(codigo), gerente(gerente), region(region), ubicacionGPS(ubicacionGPS), numSurtidores(0) {}

EstacionServicio::~EstacionServicio() {
    for (int i = 0; i < numSurtidores; ++i) {
        delete surtidores[i];
    }
}

void EstacionServicio::agregarSurtidor(Surtidor* nuevoSurtidor) {
    if (numSurtidores < 12) {
        surtidores[numSurtidores++] = nuevoSurtidor;
    }
}

void EstacionServicio::eliminarSurtidor(int codigoSurtidor) {
    for (int i = 0; i < numSurtidores; ++i) {
        if (surtidores[i]->getCodigo() == codigoSurtidor) {
            delete surtidores[i];
            surtidores[i] = surtidores[--numSurtidores]; // Reemplazar con el último
            break;
        }
    }
}

void EstacionServicio::fijarPrecios(float regular, float premium, float ecoExtra) {
    tanque.setPrecio(regular, premium, ecoExtra);
}

float EstacionServicio::calcularVentas() const {
    float totalVentas = 0;
    for (int i = 0; i < numSurtidores; ++i) {
        totalVentas += surtidores[i]->getVentasTotales();
    }
    return totalVentas;
}

void EstacionServicio::reportarVentas() const {
    std::cout << "Reporte de ventas para la estacion " << nombre << " (Codigo: " << codigo << "):\n";
    for (int i = 0; i < numSurtidores; ++i) {
        std::cout << "Surtidor " << surtidores[i]->getCodigo() << ":\n";
        surtidores[i]->mostrarHistorial();
    }
}

void EstacionServicio::simularVenta(int cantidadLitros, std::string categoria, std::string metodoPago, std::string docCliente) {
    if (numSurtidores > 0) {
        int surtidorSeleccionado = rand() % numSurtidores;
        surtidores[surtidorSeleccionado]->venderCombustible(cantidadLitros, categoria, metodoPago, docCliente, tanque);
    } else {
        std::cout << "No hay surtidores disponibles para realizar la venta.\n";
    }
}
