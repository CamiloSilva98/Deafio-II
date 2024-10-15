#include "red_nacional.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
int RedNacional::contadorEstaciones = 0;

RedNacional::RedNacional(std::string nombre) : nombreEmpresa(nombre), numeroEstaciones(0) {}

RedNacional::~RedNacional() {
    for (int i = 0; i < numeroEstaciones; ++i) {
        delete estaciones[i];
    }
}
void RedNacional::guardarDatos() const
{
    // Guardar estaciones en el archivo "estaciones.txt"
    ofstream archivoEstaciones("estaciones.txt");
    if (!archivoEstaciones)
    {
        cout << "No se pudo abrir el archivo estaciones.txt para guardar.\n";
        return;
    }

    for (int i = 0; i < numEstaciones; ++i) {
        EstacionServicio* estacion = estaciones[i];
        archivoEstaciones <<"Nombre: "<< estacion->obtenerNombre() << ", Codigo: "
                          << estacion->codigo << ", Gerente: "
                          << estacion->gerente << ", Region: "
                          << estacion->region << ", Latitud: "
                          << estacion->latitud << ", Longitud: "
                          << estacion->longitud << "\n";

        // Guardar surtidores de cada estación
        estacion->guardarSurtidores();
    }
void RedNacional::agregarEstacion(EstacionServicio* nuevaEstacion) {
    if (numeroEstaciones < 100) {
        estaciones[numeroEstaciones++] = nuevaEstacion;
        ++contadorEstaciones;
    }
}

void RedNacional::eliminarEstacion(int codigo) {
    for (int i = 0; i < numeroEstaciones; ++i) {
        if (estaciones[i]->getCodigo() == codigo) {
            delete estaciones[i];
            estaciones[i] = estaciones[--numeroEstaciones];
            --contadorEstaciones;
            break;
        }
    }
}

void RedNacional::fijarPrecios(float regular, float premium, float ecoExtra) {
    for (int i = 0; i < numeroEstaciones; ++i) {
        estaciones[i]->fijarPrecios(regular, premium, ecoExtra);
    }
}

float RedNacional::calcularVentasTotales() const {
    float totalVentas = 0.0;
    for (int i = 0; i < numeroEstaciones; ++i) {
        totalVentas += estaciones[i]->calcularVentas();
    }
    return totalVentas;
}

void RedNacional::agregarSurtidorAEstacion(int codigoEstacion, Surtidor* nuevoSurtidor) {
    for (int i = 0; i < numeroEstaciones; ++i) {
        if (estaciones[i]->getCodigo() == codigoEstacion) {
            estaciones[i]->agregarSurtidor(nuevoSurtidor);
            break;
        }
    }
}

void RedNacional::eliminarSurtidorDeEstacion(int codigoEstacion, int codigoSurtidor) {
    for (int i = 0; i < numeroEstaciones; ++i) {
        if (estaciones[i]->getCodigo() == codigoEstacion) {
            estaciones[i]->eliminarSurtidor(codigoSurtidor);
            break;
        }
    }
}

void RedNacional::fijarPreciosEnEstacion(int codigoEstacion, float regular, float premium, float ecoExtra) {
    for (int i = 0; i < numeroEstaciones; ++i) {
        if (estaciones[i]->getCodigo() == codigoEstacion) {
            estaciones[i]->fijarPrecios(regular, premium, ecoExtra);
            break;
        }
    }
}

void RedNacional::simularVenta(int codigoEstacion, int cantidadLitros, std::string categoria, std::string metodoPago, std::string docCliente) {
    for (int i = 0; i < numeroEstaciones; ++i) {
        if (estaciones[i]->getCodigo() == codigoEstacion) {
            estaciones[i]->simularVenta(cantidadLitros, categoria, metodoPago, docCliente);
            break;
        }
    }
}

void RedNacional::reportarVentasDeEstacion(int codigoEstacion) const {
    for (int i = 0; i < numeroEstaciones; ++i) {
        if (estaciones[i]->getCodigo() == codigoEstacion) {
            estaciones[i]->reportarVentas();
            break;
        }
    }
}

int RedNacional::obtenerContador() {
    return contadorEstaciones;
}
