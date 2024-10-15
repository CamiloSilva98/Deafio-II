#include "EstacionServicio.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;

EstacionServicio::EstacionServicio(const string& nombre, int codigo, const string& gerente,
                                   const string& region, double latitud, double longitud)
    : nombre(nombre), codigo(codigo), gerente(gerente), region(region),
    latitud(latitud), longitud(longitud), numSurtidores(0)
{
    for (int i = 0; i < MAX_SURTIDORES; ++i)
    {
        surtidores[i] = nullptr;
    }
    tanque.asignarCapacidades();
}

EstacionServicio::~EstacionServicio()
{
    for (int i = 0; i < numSurtidores; ++i)
    {
        delete surtidores[i];
    }
}
void EstacionServicio::cargarSurtidores()
{
    string nombreArchivo = "surtidores_" + to_string(codigo) + ".txt";
    ifstream archivoSurtidores(nombreArchivo);
    if (!archivoSurtidores)
    {
        cout << "No se pudo abrir el archivo " << nombreArchivo << " para cargar surtidores.\n";
        return;
    }

    string linea;
    while (getline(archivoSurtidores, linea))
    {
        stringstream ss(linea);
        int codigoSurtidor;
        string modelo;
        bool activo;

        ss >> codigoSurtidor;
        ss.ignore();
        getline(ss, modelo, ',');
        ss >> activo;

        Surtidor* nuevoSurtidor = new Surtidor(codigoSurtidor, modelo);
        if (!activo)
        {
            nuevoSurtidor->cambiarEstado();  // Desactivar si estaba inactivo
        }

        surtidores[numSurtidores++] = nuevoSurtidor;

        // Cargar transacciones de este surtidor
        nuevoSurtidor->cargarTransacciones();
    }

    archivoSurtidores.close();
}
void EstacionServicio::agregarSurtidor()
{
    if (numSurtidores < MAX_SURTIDORES)
    {
        int codigo;
        string modelo;
        cout << "Ingrese el codigo del surtidor: ";
        cin >> codigo;
        cout << "Ingrese el modelo del surtidor: ";
        cin >> modelo;
        surtidores[numSurtidores] = new Surtidor(codigo, modelo);
        numSurtidores++;
        cout << "Surtidor agregado con exito.\n";
    }
    else
    {
        cout << "No se pueden agregar mas surtidores.\n";
    }
}
void EstacionServicio::guardarSurtidores() const
{
    // Crear un archivo para los surtidores de esta estación
    string nombreArchivo = "surtidores_" + to_string(codigo) + ".txt";
    ofstream archivoSurtidores(nombreArchivo);
    if (!archivoSurtidores) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << " para guardar surtidores.\n";
        return;
    }
}
void EstacionServicio::eliminarSurtidor() {
    if (numSurtidores == 0) {
        cout << "No hay surtidores para eliminar.\n";
        return;
    }

    int codigo;
    cout << "Ingrese el codigo del surtidor a eliminar: ";
    cin >> codigo;

    for (int i = 0; i < numSurtidores; ++i) {
        if (surtidores[i]->obtenerCodigo() == codigo) {
            delete surtidores[i];
            for (int j = i; j < numSurtidores - 1; ++j) {
                surtidores[j] = surtidores[j + 1];
            }
            numSurtidores--;
            cout << "Surtidor eliminado con exito.\n";
            return;
        }
    }
    cout << "Surtidor no encontrado.\n";
}

void EstacionServicio::activarDesactivarSurtidor() {
    if (numSurtidores == 0) {
        cout << "No hay surtidores para activar/desactivar.\n";
        return;
    }

    int codigo;
    cout << "Ingrese el codigo del surtidor a activar/desactivar: ";
    cin >> codigo;

    for (int i = 0; i < numSurtidores; ++i) {
        if (surtidores[i]->obtenerCodigo() == codigo) {
            surtidores[i]->cambiarEstado();
            cout << "Estado del surtidor cambiado.\n";
            return;
        }
    }
    cout << "Surtidor no encontrado.\n";
}

void EstacionServicio::consultarTransacciones() const {
    if (numSurtidores == 0) {
        cout << "No hay surtidores para consultar transacciones.\n";
        return;
    }

    int codigo;
    cout << "Ingrese el codigo del surtidor para consultar transacciones: ";
    cin >> codigo;

    for (int i = 0; i < numSurtidores; ++i) {
        if (surtidores[i]->obtenerCodigo() == codigo) {
            surtidores[i]->mostrarTransacciones();
            return;
        }
    }
    cout << "Surtidor no encontrado.\n";
}

void EstacionServicio::reportarLitrosVendidos() const {
    double regularTotal = 0, premiumTotal = 0, ecoExtraTotal = 0;
    for (int i = 0; i < numSurtidores; ++i) {
        regularTotal += surtidores[i]->obtenerLitrosVendidos("Regular");
        premiumTotal += surtidores[i]->obtenerLitrosVendidos("Premium");
        ecoExtraTotal += surtidores[i]->obtenerLitrosVendidos("EcoExtra");
    }
    cout << "Litros vendidos:\n";
    cout << "Regular: " << regularTotal << " litros\n";
    cout << "Premium: " << premiumTotal << " litros\n";
    cout << "EcoExtra: " << ecoExtraTotal << " litros\n";
}

void EstacionServicio::simularVenta() {
    if (numSurtidores == 0) {
        cout << "No hay surtidores disponibles para simular una venta.\n";
        return;
    }

    int surtidorIndex = rand() % numSurtidores;
    Surtidor* surtidorSeleccionado = surtidores[surtidorIndex];

    if (!surtidorSeleccionado->estaActivo()) {
        cout << "El surtidor seleccionado no esta activo. Intente de nuevo.\n";
        return;
    }

    string categoriaCombustible;
    int opcion = rand() % 3;
    switch (opcion) {
    case 0: categoriaCombustible = "Regular"; break;
    case 1: categoriaCombustible = "Premium"; break;
    case 2: categoriaCombustible = "EcoExtra"; break;
    }

    double cantidadSolicitada = 3 + (rand() % 18); // Entre 3 y 20 litros
    double cantidadDisponible = tanque.obtenerCantidad(categoriaCombustible);
    double cantidadVendida = (cantidadSolicitada <= cantidadDisponible) ? cantidadSolicitada : cantidadDisponible;

    if (cantidadVendida > 0) {
        tanque.restarCantidad(categoriaCombustible, cantidadVendida);
        double precioTotal = cantidadVendida * tanque.obtenerPrecio(categoriaCombustible);

        string metodoPago;
        switch (rand() % 3) {
        case 0: metodoPago = "Efectivo"; break;
        case 1: metodoPago = "TDebito"; break;
        case 2: metodoPago = "TCredito"; break;
        }

        int numeroDocumentoCliente = 10000000 + (rand() % 90000000); // Número aleatorio de 8 dígitos

        surtidorSeleccionado->registrarVenta(categoriaCombustible, cantidadVendida, metodoPago, numeroDocumentoCliente, precioTotal);

        cout << "Venta simulada con exito:\n";
        cout << "Surtidor: " << surtidorSeleccionado->obtenerCodigo() << "\n";
        cout << "Combustible: " << categoriaCombustible << "\n";
        cout << "Cantidad: " << cantidadVendida << " litros\n";
        cout << "Precio total: $" << precioTotal << "\n";
        cout << "Metodo de pago: " << metodoPago << "\n";
        cout << "Numero de documento del cliente: " << numeroDocumentoCliente << "\n";
    } else {
        cout << "No hay suficiente combustible disponible para realizar la venta.\n";
    }
}

void EstacionServicio::verificarFugas() const {
    cout << "Verificacion de fugas para la estacion " << nombre << ":\n";
    tanque.verificarFugas();
}

void EstacionServicio::calcularVentasTotales() const {
    double regularTotal = 0, premiumTotal = 0, ecoExtraTotal = 0;
    for (int i = 0; i < numSurtidores; ++i) {
        regularTotal += surtidores[i]->obtenerVentaTotal("Regular");
        premiumTotal += surtidores[i]->obtenerVentaTotal("Premium");
        ecoExtraTotal += surtidores[i]->obtenerVentaTotal("EcoExtra");
    }
    cout << "Ventas totales para la estacion " << nombre << ":\n";
    cout << "Regular: $" << regularTotal << "\n";
    cout << "Premium: $" << premiumTotal << "\n";
    cout << "EcoExtra: $" << ecoExtraTotal << "\n";
}

void EstacionServicio::fijarPrecios(double regular, double premium, double ecoExtra) {
    tanque.fijarPrecios(regular, premium, ecoExtra);
    cout << "Precios actualizados para la estacion " << nombre << ".\n";
}

bool EstacionServicio::tieneHurtirsActivos() const {
    for (int i = 0; i < numSurtidores; ++i) {
        if (surtidores[i]->estaActivo()) {
            return true;
        }
    }
    return false;
}

void EstacionServicio::gestionarEstacion() {
    int opcion;
    do {
        cout << "\n--- Gestion de Estacion de Servicio: " << nombre << " ---\n";
        cout << "1. Agregar surtidor\n";
        cout << "2. Eliminar surtidor\n";
        cout << "3. Activar/desactivar surtidor\n";
        cout << "4. Consultar transacciones de un surtidor\n";
        cout << "5. Reportar litros vendidos\n";
        cout << "6. Simular una venta\n";
        cout << "0. Volver al menu anterior\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: agregarSurtidor(); break;
        case 2: eliminarSurtidor(); break;
        case 3: activarDesactivarSurtidor(); break;
        case 4: consultarTransacciones(); break;
        case 5: reportarLitrosVendidos(); break;
        case 6: simularVenta(); break;
        case 0: cout << "Volviendo al menu anterior...\n"; break;
        default: cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 0);
}

