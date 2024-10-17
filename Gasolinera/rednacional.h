#ifndef REDNACIONAL_H
#define REDNACIONAL_H

#include "estacionservicio.h"

class RedNacional {
private:
    static const int MAX_ESTACIONES = 100;
    EstacionServicio* estaciones[MAX_ESTACIONES];
    int numEstaciones;
    float precioRegular;
    float precioPremium;
    float precioEcoExtra;

public:
    RedNacional();
    ~RedNacional();
    void fijarPrecios(float regular, float premium, float ecoExtra);
    float obtenerPrecio(const string& categoria) const;
    // Métodos para gestionar la red de estaciones
    void actualizarPreciosPorDia();
    void gestionarRedNacional();

    float calcularPrecioConRegion(const std::string& categoria, const std::string& region) const;
    void agregarEstacionServicio();
    void eliminarEstacionServicio();
    void calcularVentasTotales() const;
    void fijarPreciosCombustible();
    void cargarDatos();
    void gestionRedNacional();
    void gestionEstacionesServicio();
    void verificacionFugas();
    void simulacionVentas();
    void guardarDatos() const;

private:
    EstacionServicio* seleccionarEstacion() const;
};

#endif // REDNACIONAL_H
