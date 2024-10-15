#ifndef ESTACIONSERVICIO_H
#define ESTACIONSERVICIO_H

#include <string>
#include "tanque.h"
#include "surtidor.h"
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
    void guardarSurtidores() const;
    void gestionarEstacion();
    void cargarSurtidores();

    // Getters
    string obtenerNombre() const { return nombre; }
    int obtenerCodigo() const { return codigo; }
    string obtenerGerente() const { return gerente; }
    string obtenerRegion() const { return region; }
    double obtenerLatitud() const { return latitud; }
    double obtenerLongitud() const { return longitud; }

    friend class RedNacional;  // Permite a RedNacional acceder a los atributos privados
};

#endif // ESTACIONSERVICIO_H
