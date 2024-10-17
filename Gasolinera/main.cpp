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
    cout << "0. Guardar y Salir\n";
    cout << "Seleccione una opcion: \n";
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    RedNacional redNacional;
    redNacional.cargarDatos();
    int opcion;
    string entrada;

    do {
        mostrarMenu();

        while (true) {
            cout << "Ingrese su opcion: ";
            getline(cin, entrada);

            // Intenta convertir la entrada a un número
            try {
                opcion = stoi(entrada);
                break; // Si la conversión es exitosa, sal del bucle
            }
            catch (const invalid_argument&) {
                cout << "Error: Debe ingresar un numero. Por favor, elija una de las opciones mostradas en el menu.\n";
                mostrarMenu();
            }
            catch (const out_of_range&) {
                cout << "Error: El numero ingresado es demasiado grande. Por favor, elija una de las opciones mostradas en el menu.\n";
                mostrarMenu();
            }
        }

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
            cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 0);

    return 0;
}
//bien
