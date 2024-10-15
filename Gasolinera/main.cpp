#include <iostream>
#include <cstdlib>
#include <ctime>
#include "rednacional.h"
using namespace std;

void mostrarMenu() {
    cout << "\n--- Menu Principal ---\n";
    cout << "1. Gestion de la red nacional\n";
    cout << "2. Gestion de estaciones de servicio\n";
    cout << "3. Verificacion de fugas\n";
    cout << "4. Simulacion de ventas\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    RedNacional redNacional;
    redNacional.cargarDatos();
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
        case 1:
            redNacional.gestionRedNacional();
            break;
        case 2:
            redNacional.gestionEstacionesServicio();
            break;
        case 3:
            redNacional.verificacionFugas();
            break;
        case 4:
            redNacional.simulacionVentas();
            break;
        case 0:
            cout << "Guardando datos y saliendo del programa...\n";
            redNacional.guardarDatos();  // Guardar los datos al salir
            break;
        default:
            cout << "Opción no valida. Intente de nuevo.\n";
        }
    } while (opcion != 0);

    return 0;
}
