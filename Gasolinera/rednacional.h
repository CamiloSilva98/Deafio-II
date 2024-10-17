#ifndef REDNACIONAL_H
#define REDNACIONAL_H

#include "estacionservicio.h"

class RedNacional {
private:
    static const int MAX_ESTACIONES = 100;
    EstacionServicio* estaciones[MAX_ESTACIONES];
    int numEstaciones;
    double precioBaseRegular;
    double precioBasePremium;
    double precioBaseEcoExtra;

public:
    RedNacional();
    ~RedNacional();
    void fijarPreciosBase(double regular, double premium, double ecoExtra);
    double obtenerPrecioBaseRegular() const { return precioBaseRegular; }
    double obtenerPrecioBasePremium() const { return precioBasePremium; }
    double obtenerPrecioBaseEcoExtra() const { return precioBaseEcoExtra; }

    // Métodos para gestionar la red de estaciones
    void actualizarPreciosPorDia();
    void gestionarRedNacional();

    double calcularPrecioConRegion(const std::string& categoria, const std::string& region) const;

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
