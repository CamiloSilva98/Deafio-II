#ifndef RED_NACIONAL_H
#define RED_NACIONAL_H

#include "estacion_servicio.h"
#include <string>

class RedNacional {
private:
    std::string nombreEmpresa;
    static int contadorEstaciones;
    EstacionServicio* estaciones[100]; // Arreglo para almacenar estaciones
    int numeroEstaciones;

public:
    RedNacional(std::string nombre);
    ~RedNacional();

    void agregarEstacion(EstacionServicio* nuevaEstacion);
    void eliminarEstacion(int codigo);

    void fijarPrecios(float regular, float premium, float ecoExtra);
    float calcularVentasTotales() const;

    void agregarSurtidorAEstacion(int codigoEstacion, Surtidor* nuevoSurtidor);
    void eliminarSurtidorDeEstacion(int codigoEstacion, int codigoSurtidor);
    void fijarPreciosEnEstacion(int codigoEstacion, float regular, float premium, float ecoExtra);
    void simularVenta(int codigoEstacion, int cantidadLitros, std::string categoria, std::string metodoPago, std::string docCliente);
    void reportarVentasDeEstacion(int codigoEstacion) const;

    static int obtenerContador();
};

#endif // RED_NACIONAL_H
