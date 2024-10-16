#include "surtidor.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

Surtidor::Surtidor(int codigo, const string& modelo)
    : codigo(codigo), modelo(modelo), activo(true), numTransacciones(0) {}

void Surtidor::cargarTransacciones() {
    string nombreArchivo = "transacciones_" + to_string(codigo) + ".txt";
    ifstream archivoTransacciones(nombreArchivo);
    if (!archivoTransacciones) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << " para cargar transacciones.\n";
        return;
    }

    string linea;
    while (getline(archivoTransacciones, linea)) {
        stringstream ss(linea);
        Transaccion nuevaTransaccion;

        ss >> nuevaTransaccion.fecha;
        ss.ignore();
        getline(ss, nuevaTransaccion.categoria, ',');
        ss >> nuevaTransaccion.cantidad;
        ss.ignore();
        getline(ss, nuevaTransaccion.metodoPago, ',');
        ss >> nuevaTransaccion.numeroDocumentoCliente;
        ss.ignore();
        ss >> nuevaTransaccion.montoTotal;

        transacciones[numTransacciones++] = nuevaTransaccion;
    }

    archivoTransacciones.close();
}

void Surtidor::registrarVenta(const string& categoria, double cantidad, const string& metodoPago,
                              int numeroDocumentoCliente, double montoTotal) {
    if (numTransacciones < MAX_TRANSACCIONES) {
        Transaccion nuevaTransaccion;
        nuevaTransaccion.fecha = time(nullptr);
        nuevaTransaccion.categoria = categoria;
        nuevaTransaccion.cantidad = cantidad;
        nuevaTransaccion.metodoPago = metodoPago;
        nuevaTransaccion.numeroDocumentoCliente = numeroDocumentoCliente;
        nuevaTransaccion.montoTotal = montoTotal;

        transacciones[numTransacciones] = nuevaTransaccion;
        numTransacciones++;
    } else {
        cout << "No se pueden registrar más transacciones. Límite alcanzado.\n";
    }
}

void Surtidor::mostrarTransacciones() const {
    cout << "Transacciones del surtidor " << codigo << ":\n";
    for (int i = 0; i < numTransacciones; ++i) {
        cout << "Fecha: " << ctime(&transacciones[i].fecha);
        cout << "Categoría: " << transacciones[i].categoria << "\n";
        cout << "Cantidad: " << transacciones[i].cantidad << " litros\n";
        cout << "Método de pago: " << transacciones[i].metodoPago << "\n";
        cout << "Número de documento del cliente: " << transacciones[i].numeroDocumentoCliente << "\n";
        cout << "Monto total: $" << std::fixed << std::setprecision(2) << transacciones[i].montoTotal << "\n\n";
    }
}

double Surtidor::obtenerLitrosVendidos(const string& categoria) const {
    double total = 0;
    for (int i = 0; i < numTransacciones; ++i) {
        if (transacciones[i].categoria == categoria) {
            total += transacciones[i].cantidad;
        }
    }
    return total;
}

double Surtidor::obtenerVentaTotal(const string& categoria) const {
    double total = 0;
    for (int i = 0; i < numTransacciones; ++i) {
        if (transacciones[i].categoria == categoria) {
            total += transacciones[i].montoTotal;
        }
    }
    return total;
}

void Surtidor::cambiarEstado() {
    activo = !activo;
    cout << "El surtidor " << codigo << " ahora está " << (activo ? "activo" : "inactivo") << ".\n";
}

bool Surtidor::estaActivo() const {
    return activo;
}

int Surtidor::obtenerCodigo() const {
    return codigo;
}

