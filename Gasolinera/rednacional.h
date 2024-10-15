#ifndef REDNACIONAL_H
#define REDNACIONAL_H

#include "EstacionServicio.h"

class RedNacional {
private:
    static const int MAX_ESTACIONES = 100;
    EstacionServicio* estaciones[MAX_ESTACIONES];
    int numEstaciones;

public:
    RedNacional();
    ~RedNacional();

    void agregarEstacionServicio();
    void eliminarEstacionServicio();
    void calcularVentasTotales() const;
    void fijarPreciosCombustible();

    void gestionRedNacional();
    void gestionEstacionesServicio();
    void verificacionFugas();
    void simulacionVentas();

private:
    EstacionServicio* seleccionarEstacion() const;
};

#endif // REDNACIONAL_H
