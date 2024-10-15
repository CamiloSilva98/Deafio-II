#ifndef ESTACIONSERVICIO_H
#define ESTACIONSERVICIO_H

#include <string>
#include "Tanque.h"
#include "Surtidor.h"
using namespace std;

class EstacionServicio {
private:
    string nombre;
    int codigo;
    string gerente;
    string region;
    double latitud;
    double longitud;
    Tanque tanque;
    static const int MAX_SURTIDORES = 12;
    Surtidor* surtidores[MAX_SURTIDORES];
    int numSurtidores;

public:
    EstacionServicio(const string& nombre, int codigo, const string& gerente,
                     const string& region, double latitud, double longitud);
    ~EstacionServicio();

    void agregarSurtidor();
    void eliminarSurtidor();
    void activarDesactivarSurtidor();
    void consultarTransacciones() const;
    void reportarLitrosVendidos() const;
    void simularVenta();
    void verificarFugas() const;
    void calcularVentasTotales() const;
    void fijarPrecios(double regular, double premium, double ecoExtra);
    bool tieneHurtirsActivos() const;

    void gestionarEstacion();

    string obtenerNombre() const { return nombre; }

    friend class RedNacional;
};

#endif // ESTACIONSERVICIO_H
