#include "ventas.h"

int main() {
    std::vector<Venta> ventas;
    std::string archivo = "ventas.csv";

    cargarDatos(archivo, ventas);

    if (ventas.empty()) {
        std::cout << "No se cargaron ventas.\n";
        return 0;
    }

    int opcion;
    do {
        std::cout << "\n---- MENU ----\n";
        std::cout << "1. Ordenar por cantidad\n";
        std::cout << "2. Ordenar por fecha\n";
        std::cout << "3. Buscar por numero de nota (binaria)\n";
        std::cout << "4. Buscar por cantidad\n";
        std::cout << "5. Buscar por dia de la semana\n";
        std::cout << "6. Salir\n";
        std::cout << "Selecciona una opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            ordenarPorCantidad(ventas);
        } else if (opcion == 2) {
            ordenarPorFecha(ventas);
        } else if (opcion == 3) {
            std::string nota;
            std::cout << "Ingrese el numero de nota: ";
            std::cin >> nota;
            ordenarPorNota(ventas); // ordenar antes de la busqueda binaria
            int indice = busquedaBinariaPorNota(ventas, nota);
            if (indice != -1)
                imprimirVenta(ventas[indice]);
            else
                std::cout << "Nota no encontrada.\n";
        } else if (opcion == 4) {
            double cantidad;
            std::cout << "Ingrese la cantidad: ";
            std::cin >> cantidad;
            buscarPorCantidad(ventas, cantidad);
        } else if (opcion == 5) {
            std::string dia;
            std::cout << "Ingrese el dia (ej. Monday, Tuesday...): "; // pedir al usuario el dia
            std::cin >> dia;
            buscarPorDiaSemana(ventas, dia);
        } else if (opcion == 6) {
            std::cout << "Saliendo...\n";
        } else {
            std::cout << "Opcion invalida.\n";
        }
    } while (opcion != 6);

    return 0;
}
