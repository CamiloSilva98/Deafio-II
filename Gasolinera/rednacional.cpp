#include "RedNacional.h"
#include <iostream>
#include <cstdlib>
using namespace std;

RedNacional::RedNacional() : numEstaciones(0) {
    for (int i = 0; i < MAX_ESTACIONES; ++i) {
        estaciones[i] = nullptr;
    }
}

RedNacional::~RedNacional() {
    for (int i = 0; i < numEstaciones; ++i) {
        delete estaciones[i];
    }
}

void RedNacional::agregarEstacionServicio() {
    if (numEstaciones < MAX_ESTACIONES) {
        std::string nombre, gerente, region;
        int codigo;
        double latitud, longitud;

        cout << "Ingrese el nombre de la estacion: ";
        cin >> nombre;
        cout << "Ingrese el codigo de la estacion: ";
        cin >> codigo;
        cout << "Ingrese el nombre del gerente: ";
        cin >> gerente;
        cout << "Ingrese la region (Norte/Centro/Sur): ";
        cin >> region;
        cout << "Ingrese la latitud: ";
        cin >> latitud;
        cout << "Ingrese la longitud: ";
        cin >> longitud;

        estaciones[numEstaciones] = new EstacionServicio(nombre, codigo, gerente, region, latitud, longitud);
        numEstaciones++;
        cout << "Estacion de servicio agregada con exito.\n";
    } else {
        cout << "No se pueden agregar mas estaciones de servicio.\n";
    }
}

void RedNacional::eliminarEstacionServicio() {
    EstacionServicio* estacion = seleccionarEstacion();
    if (estacion) {
        if (estacion->tieneHurtirsActivos()) {
            cout << "No se puede eliminar la estacion porque tiene surtidores activos.\n";
        } else {
            for (int i = 0; i < numEstaciones; ++i) {
                if (estaciones[i] == estacion) {
                    delete estaciones[i];
                    for (int j = i; j < numEstaciones - 1; ++j) {
                        estaciones[j] = estaciones[j + 1];
                    }
                    numEstaciones--;
                    cout << "Estacion de servicio eliminada con exito.\n";
                    return;
                }
            }
        }
    }
}

void RedNacional::calcularVentasTotales() const {
    for (int i = 0; i < numEstaciones; ++i) {
        estaciones[i]->calcularVentasTotales();
    }
}

void RedNacional::fijarPreciosCombustible() {
    double precioRegular, precioPremium, precioEcoExtra;
    cout << "Ingrese el nuevo precio para combustible Regular: ";
    cin >> precioRegular;
    cout << "Ingrese el nuevo precio para combustible Premium: ";
    cin >> precioPremium;
    cout << "Ingrese el nuevo precio para combustible EcoExtra: ";
    cin >> precioEcoExtra;

    for (int i = 0; i < numEstaciones; ++i) {
        estaciones[i]->fijarPrecios(precioRegular, precioPremium, precioEcoExtra);
    }
    cout << "Precios actualizados para todas las estaciones.\n";
}

void RedNacional::gestionRedNacional() {
    int opcion;
    do {
        cout << "\n--- Gestion de la Red Nacional ---\n";
        cout << "1. Agregar estacion de servicio\n";
        cout << "2. Eliminar estacion de servicio\n";
        cout << "3. Calcular ventas totales\n";
        cout << "4. Fijar precios de combustible\n";
        cout << "0. Volver al menu principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: agregarEstacionServicio(); break;
        case 2: eliminarEstacionServicio(); break;
        case 3: calcularVentasTotales(); break;
        case 4: fijarPreciosCombustible(); break;
        case 0: cout << "Volviendo al menu principal...\n"; break;
        default: cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 0);
}

void RedNacional::gestionEstacionesServicio() {
    EstacionServicio* estacion = seleccionarEstacion();
    if (estacion) {
        estacion->gestionarEstacion();
    }
}

void RedNacional::verificacionFugas() {
    EstacionServicio* estacion = seleccionarEstacion();
    if (estacion) {
        estacion->verificarFugas();
    }
}

void RedNacional::simulacionVentas() {
    EstacionServicio* estacion = seleccionarEstacion();
    if (estacion) {
        estacion->simularVenta();
    }
}

EstacionServicio* RedNacional::seleccionarEstacion() const {
    if (numEstaciones == 0) {
        cout << "No hay estaciones de servicio registradas.\n";
        return nullptr;
    }

    cout << "Estaciones de servicio disponibles:\n";
    for (int i = 0; i < numEstaciones; ++i) {
        cout << i + 1 << ". " << estaciones[i]->obtenerNombre() << "\n";
    }

    int seleccion;
    cout << "Seleccione una estacion (1-" << numEstaciones << "): ";
    cin >> seleccion;

    if (seleccion < 1 || seleccion > numEstaciones) {
        cout << "Seleccion invalida.\n";
        return nullptr;
    }

    return estaciones[seleccion - 1];
}

