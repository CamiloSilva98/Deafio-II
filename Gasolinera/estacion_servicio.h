#ifndef ESTACION_SERVICIO_H
#define ESTACION_SERVICIO_H

#include "tanque.h"
#include "surtidor.h"
#include <string>

class EstacionServicio {
private:
    std::string nombre;
    int codigo;
    std::string gerente;
    std::string region;
    std::string ubicacionGPS;
    Tanque tanque;
    Surtidor* surtidores[12]; // Máximo de 12 surtidores
    int numSurtidores;

public:
    EstacionServicio(std::string nombre, int codigo, std::string gerente, std::string region, std::string ubicacionGPS);
    ~EstacionServicio();

    void agregarSurtidor(Surtidor* nuevoSurtidor);
    void eliminarSurtidor(int codigoSurtidor);
    void fijarPrecios(float regular, float premium, float ecoExtra);
    float calcularVentas() const;

    void reportarVentas() const;
    void simularVenta(int cantidadLitros, std::string categoria, std::string metodoPago, std::string docCliente);

    int getCodigo() const { return codigo; }

    friend class RedNacional; // RedNacional tiene acceso a los detalles de esta clase
};

#endif // ESTACION_SERVICIO_H
