/*
 * main.cpp
 *
 *  Created on: 24/09/2025
 *      Author: Lucía Casas - A01713181
 */

#include "ventas.h"

int main() {
    std::deque<Venta> ventas;
    std::string archivo = "ventas.csv";

    cargarDatos(archivo, ventas);

    int opcion;

    do {
        std::cout << "\n---- MENU ----\n";
        std::cout << "1. Comenzar dia\n";
        std::cout << "2. Mostrar las ventas (ordenadas por numero de nota)\n";
        std::cout << "3. Ordenar por cantidad\n";
        std::cout << "4. Ordenar por fecha\n";
        std::cout << "5. Buscar por numero de nota\n";
        std::cout << "6. Buscar por cantidad\n";
        std::cout << "7. Buscar por dia de la semana\n";
        std::cout << "8. Salir\n";
        std::cout << "Selecciona una opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            std::string fechaDia;
            std::deque<Venta> ventasDia;

            std::cout << "Ingresa la fecha del dia (YYYY-MM-DD): ";
            std::cin >> fechaDia;

            int op2;
            do {
                std::cout << "\n--- MENU DEL DIA ---\n";
                std::cout << "1. Registrar venta\n";
                std::cout << "2. Cierre de lote\n";
                std::cout << "Elige una opcion: ";
                std::cin >> op2;

                if (op2 == 1) {
                    Venta v = registrarVenta(fechaDia);
                    ventasDia.push_back(v);

                } else if (op2 == 2) {
                    cierreDeLote(archivo, ventas, ventasDia);
                    break;
                }

            } while (op2 != 2);
        }

        else if (opcion == 2) {
            std::deque<Venta> copia = ventas;
            ordenarPorNota(copia);
            for (const auto& v : copia) imprimirVenta(v);
        }

        else if (opcion == 3) ordenarPorCantidad(ventas);
        else if (opcion == 4) ordenarPorFecha(ventas);

        else if (opcion == 5) {
            std::string nota;
            std::cout << "Ingrese el numero de nota (000): ";
            std::cin >> nota;
            ordenarPorNota(ventas);
            int indice = busquedaBinariaPorNota(ventas, nota);
            if (indice != -1)
                imprimirVenta(ventas[indice]);
            else
                std::cout << "Nota no encontrada.\n";
        }

        else if (opcion == 6) {
            double cantidad;
            std::cout << "Ingrese la cantidad: ";
            std::cin >> cantidad;
            buscarPorCantidad(ventas, cantidad);
        }

        else if (opcion == 7) {
            std::string dia;
            std::cout << "Ingrese el dia (ej. Monday, Tuesday...): ";
            std::cin >> dia;
            buscarPorDiaSemana(ventas, dia);
        }

        else if (opcion == 8) {
            std::cout << "Saliendo...\n";
        }

    } while (opcion != 8);

    return 0;
}
