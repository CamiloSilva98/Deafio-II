#include "rednacional.h"
#include "tanque.h"
#include "estacionservicio.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cctype>
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
void RedNacional::fijarPrecios(float regular, float premium, float ecoExtra)
{
    precioRegular = regular;
    precioPremium = premium;
    precioEcoExtra = ecoExtra;
}
float RedNacional::obtenerPrecio(const std::string& categoria) const {
    if (categoria == "Regular") {
        return precioRegular;
    } else if (categoria == "Premium") {
        return precioPremium;
    } else if (categoria == "EcoExtra") {
        return precioEcoExtra;
    }
    return 0;

}
void RedNacional::actualizarPreciosPorDia()
{
    precioRegular *= 1.01;
    precioPremium *= 1.01;
    precioEcoExtra *= 1.01;
}
float RedNacional::calcularPrecioConRegion(const string& categoria, const string& region) const
{
    float precioBase = 0.0;

    // Determina el precio base según la categoría
    if (categoria == "Regular")
    {
        precioBase = obtenerPrecio("Regular");
    }
    else if (categoria == "Premium")
    {
        precioBase = obtenerPrecio("Premium");
    }
    else if (categoria == "EcoExtra")
    {
        precioBase = obtenerPrecio("EcoExtra");
    }
    else
    {
        std::cerr << "Categoría no válida\n";
        return 0.0;
    }
    // Ajustar el precio según la región
    if (region == "norte")
    {
        precioBase = precioBase*1.05;
    }
    else if (region == "sur")
    {
        precioBase = precioBase*1.02;
    }
    return precioBase;
}
void RedNacional::cargarDatos() {
    ifstream archivoEstaciones("estaciones.txt");
    if (!archivoEstaciones) {
        cout << "No se pudo abrir el archivo estaciones.txt para cargar.\n";
        return;
    }

    string linea;
    while (getline(archivoEstaciones, linea)) {
        stringstream ss(linea);
        string nombre, gerente, region;
        int codigo;
        double latitud, longitud;

        getline(ss, nombre, ',');
        ss >> codigo;
        ss.ignore();  // Ignorar la coma
        getline(ss, gerente, ',');
        getline(ss, region, ',');
        ss >> latitud;
        ss.ignore();
        ss >> longitud;

        EstacionServicio* nuevaEstacion = new EstacionServicio(nombre, codigo, gerente, region, latitud, longitud, this);
        estaciones[numEstaciones++] = nuevaEstacion;

        // Cargar surtidores de esta estación
        nuevaEstacion->cargarSurtidores();
    }

    archivoEstaciones.close();
    ifstream archivoPrecios("precios.txt");
    if (!archivoEstaciones) {
        cout << "No se pudo abrir el archivo estaciones.txt para cargar.\n";
        return;
    }
}
void RedNacional::guardarDatos()
{
    // Guardar estaciones en el archivo "estaciones.txt"
    ofstream archivoEstaciones("estaciones.txt");
    if (!archivoEstaciones)
    {
        cout << "No se pudo abrir el archivo estaciones.txt para guardar.\n";
        return;
    }

    for (int i = 0; i < numEstaciones; ++i) {
        EstacionServicio* estacion = estaciones[i];
        archivoEstaciones<< estacion->obtenerNombre() << ","
                          << estacion->codigo << ","
                          << estacion->gerente << ","
                          << estacion->region << ","
                          << estacion->latitud << ","
                          << estacion->longitud << "\n";

        // Guardar surtidores de cada estación
        estacion->guardarSurtidores();
    }
    archivoEstaciones.close();
    ifstream archivoPrecios("precios.txt");
    if (!archivoPrecios)
    {
        cout << "No se pudo abrir el archivo precios.txt.\n";
        return;
    }
    string categoria;
    float precio;
    while (archivoPrecios >> categoria >> precio) {
        if (categoria == "Regular") {
            precioRegular = precio;
        } else if (categoria == "Premium") {
            precioPremium = precio;
        } else if (categoria == "EcoExtra") {
            precioEcoExtra = precio;
        }
    }

    archivoPrecios.close();
    cout << "Datos de la red nacional guardados con exito.\n";
}
void RedNacional::agregarEstacionServicio() {
    if (numEstaciones < MAX_ESTACIONES) {
        std::string nombre, gerente, region;
        int codigo;
        double latitud, longitud;

        cout << "Ingrese el nombre de la estacion: ";
        while (!(cin >> nombre)) {
            cout << "Error: Ingrese un nombre valido.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ingrese el nombre de la estacion: ";
        }

        cout << "Ingrese el codigo de la estacion: ";
        while (!(cin >> codigo)) {
            cout << "Error: Ingrese un codigo numerico valido.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ingrese el codigo de la estacion: ";
        }

        cout << "Ingrese el nombre del gerente: ";
        while (!(cin >> gerente)) {
            cout << "Error: Ingrese un nombre valido.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ingrese el nombre del gerente: ";
        }

        do {
            cout << "Ingrese la region (Norte/Centro/Sur): ";
            cin >> region;
            for (char& c : region)
        {
            c =tolower(c);
        }
            if (region != "norte" && region != "centro" && region != "sur") {
                cout << "Error: Region invalida. Ingrese Norte, Centro o Sur.\n";
            }
        } while (region != "norte" && region != "centro" && region != "sur");
        cout << "Ingrese la latitud: ";
        while (!(cin >> latitud)) {
            cout << "Error: Ingrese un numero valido para la latitud.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ingrese la latitud: ";
        }

        cout << "Ingrese la longitud: ";
        while (!(cin >> longitud)) {
            cout << "Error: Ingrese un numero valido para la longitud.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ingrese la longitud: ";
        }

        estaciones[numEstaciones] = new EstacionServicio(nombre, codigo, gerente, region, latitud, longitud, this);
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
    float precioRegular, precioPremium, precioEcoExtra;

    cout << "Ingrese el nuevo precio para combustible Regular: ";
    while (!(cin >> precioRegular) || precioRegular < 0) {
        cout << "Error: Ingrese un precio valido (mayor o igual a 0).\n";
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ingrese el nuevo precio para combustible Regular: ";
    }

    cout << "Ingrese el nuevo precio para combustible Premium: ";
    while (!(cin >> precioPremium) || precioPremium < 0) {
        cout << "Error: Ingrese un precio valido (mayor o igual a 0).\n";
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ingrese el nuevo precio para combustible Premium: ";
    }

    cout << "Ingrese el nuevo precio para combustible EcoExtra: ";
    while (!(cin >> precioEcoExtra) || precioEcoExtra < 0) {
        cout << "Error: Ingrese un precio valido (mayor o igual a 0).\n";
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ingrese el nuevo precio para combustible EcoExtra: ";
    }
    fijarPrecios(precioRegular, precioPremium, precioEcoExtra);
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

        while (!(cin >> opcion)) {
            cout << "Error: Ingrese un numero valido.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Seleccione una opcion: ";
        }

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
    while (!(cin >> seleccion) || seleccion < 1 || seleccion > numEstaciones) {
        cout << "Error: Seleccion invalida.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Seleccione una estacion (1-" << numEstaciones << "): ";
    }

    return estaciones[seleccion - 1];
}

