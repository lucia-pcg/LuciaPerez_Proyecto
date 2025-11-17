/*
 * ventas.h
 *
 *  Created on: 24/09/2025
 *      Author: Lucía Casas - A01713181
 */

#ifndef VENTAS_H
#define VENTAS_H

#include <iostream>
#include <deque>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <ctime>

struct Venta {
    std::string nota;
    std::string fecha;
    double cantidad;
};

void imprimirVenta(const Venta &v) {
    std::cout << "Nota: " << v.nota
              << " - Fecha: " << v.fecha
              << " - Cantidad: " << v.cantidad << "\n";
}

void cargarDatos(const std::string &archivo, std::deque<Venta> &ventas) {
    std::ifstream file(archivo);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo.\n";
        return;
    }
    std::string linea;
    while (std::getline(file, linea)) {
        std::stringstream ss(linea);
        std::string nota, fecha, cantidadStr;
        if (std::getline(ss, nota, ',') &&
            std::getline(ss, fecha, ',') &&
            std::getline(ss, cantidadStr)) {
            Venta v;
            v.nota = nota;
            v.fecha = fecha;
            v.cantidad = std::stod(cantidadStr);
            ventas.push_back(v);
        }
    }
    file.close();
}

// Registrar una venta del día
Venta registrarVenta(const std::string &fechaDia) {
    int opcion;
    double total = 0;

    do {
        std::cout << "\n--- MENU DE PRODUCTOS ---\n";
        std::cout << "1. Body ($150)\n";
        std::cout << "2. Mameluco ($250)\n";
        std::cout << "3. Vestido ($480)\n";
        std::cout << "4. Conjunto ($750)\n";
        std::cout << "5. Calcetines ($60)\n";
        std::cout << "6. Set de almohadas ($300)\n";
        std::cout << "7. Babero ($45)\n";
        std::cout << "8. Terminar compra\n";
        std::cout << "Elige una opcion: ";
        std::cin >> opcion;

        if (opcion == 1) total += 150;
        else if (opcion == 2) total += 250;
        else if (opcion == 3) total += 480;
        else if (opcion == 4) total += 750;
        else if (opcion == 5) total += 60;
        else if (opcion == 6) total += 300;
        else if (opcion == 7) total += 45;
        else if (opcion != 8)
            std::cout << "Opcion inválida.\n";

    } while (opcion != 8);

    Venta v;
    std::cout << "Ingresa numero de nota: ";
    std::cin >> v.nota;

    v.fecha = fechaDia;
    v.cantidad = total;

    std::cout << "Venta registrada: \n";
    imprimirVenta(v);

    return v;
}

// Cierre de lote
void cierreDeLote(const std::string &archivo,
                  std::deque<Venta> &ventas,
                  std::deque<Venta> &ventasDia) {

    for (const auto &v : ventasDia)
        ventas.push_back(v);

    ventasDia.clear();

    std::ofstream file(archivo);
    if (!file.is_open()) {
        std::cerr << "Error al abrir archivo para escribir.\n";
        return;
    }

    for (const auto &v : ventas)
        file << v.nota << "," << v.fecha << "," << v.cantidad << "\n";

    file.close();

    std::cout << "Cierre de lote completado. Registro de ventas actualizado.\n";
}

// Sorts
void ordenarPorCantidad(std::deque<Venta> &ventas) {
    std::sort(ventas.begin(), ventas.end(),
              [](const Venta &a, const Venta &b) { return a.cantidad < b.cantidad; });
    for (const auto &v : ventas) imprimirVenta(v);
}

void ordenarPorFecha(std::deque<Venta> &ventas) {
    std::sort(ventas.begin(), ventas.end(),
              [](const Venta &a, const Venta &b) { return a.fecha < b.fecha; });
    for (const auto &v : ventas) imprimirVenta(v);
}

void ordenarPorNota(std::deque<Venta> &ventas) {
    std::sort(ventas.begin(), ventas.end(),
              [](const Venta &a, const Venta &b) { return a.nota < b.nota; });
}

// Búsquedas
int busquedaBinariaPorNota(const std::deque<Venta> &ventas, const std::string &notaBuscada) {
    int low = 0, high = ventas.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (ventas[mid].nota == notaBuscada)
            return mid;
        else if (ventas[mid].nota < notaBuscada)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

void buscarPorCantidad(const std::deque<Venta> &ventas, double cantidadBuscada) {
    bool encontrado = false;
    for (const auto &v : ventas) {
        if (v.cantidad == cantidadBuscada) {
            imprimirVenta(v);
            encontrado = true;
        }
    }
    if (!encontrado) std::cout << "No se encontro esa cantidad.\n";
}

std::string obtenerDiaSemana(const std::string &fecha) {
    int year, month, day;
    char sep;
    std::stringstream ss(fecha);
    ss >> year >> sep >> month >> sep >> day;
    std::tm time_in = {};
    time_in.tm_year = year - 1900;
    time_in.tm_mon = month - 1;
    time_in.tm_mday = day;
    std::mktime(&time_in);
    const char* dias[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return dias[time_in.tm_wday];
}

void buscarPorDiaSemana(const std::deque<Venta> &ventas, const std::string &diaBuscado) {
    bool encontrado = false;
    for (const auto &v : ventas) {
        std::string dia = obtenerDiaSemana(v.fecha);
        if (dia == diaBuscado) {
            imprimirVenta(v);
            encontrado = true;
        }
    }
    if (!encontrado) std::cout << "No hay ventas en ese dia.\n";
}

#endif
