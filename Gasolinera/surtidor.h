#ifndef SURTIDOR_H
#define SURTIDOR_H

#include <string>
#include <ctime>
using namespace std;

struct Transaccion {
    time_t fecha;
    string categoria;
    double cantidad;
    string metodoPago;
    int numeroDocumentoCliente;
    double montoTotal;
};

class Surtidor {
private:
    int codigo;
    string modelo;
    bool activo;
    static const int MAX_TRANSACCIONES = 100;
    Transaccion transacciones[MAX_TRANSACCIONES];
    int numTransacciones;

public:
    Surtidor(int codigo, const string& modelo);

    void registrarVenta(const string& categoria, double cantidad, const string& metodoPago,
                        int numeroDocumentoCliente, double montoTotal);
    void mostrarTransacciones() const;
    double obtenerLitrosVendidos(const string& categoria) const;
    double obtenerVentaTotal(const string& categoria) const;
    void cambiarEstado();
    bool estaActivo() const;
    int obtenerCodigo() const;
};

#endif // SURTIDOR_H
