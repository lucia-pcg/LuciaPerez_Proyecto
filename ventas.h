/*
 * ventas.h
 *
 *  Created on: 24/09/2025
 *      Author: Lucía Casas - A01713181
 */

#ifndef VENTAS_H
#define VENTAS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <ctime>

struct Venta {
    std::string nota;
    std::string fecha; // YYYY-MM-DD
    double cantidad;
};

// Función para imprimir una venta
void imprimirVenta(const Venta &v) {
    std::cout << "Nota: " << v.nota
              << " - Fecha: " << v.fecha
              << " - Cantidad: " << v.cantidad << "\n";
}

// Cargar datos desde CSV
void cargarDatos(const std::string &archivo, std::vector<Venta> &ventas) {
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

// Ordenar por cantidad
void ordenarPorCantidad(std::vector<Venta> &ventas) {
    std::sort(ventas.begin(), ventas.end(),
              [](const Venta &a, const Venta &b) { return a.cantidad < b.cantidad; });
    for (const auto &v : ventas) imprimirVenta(v);
}

// Ordenar por fecha
void ordenarPorFecha(std::vector<Venta> &ventas) {
    std::sort(ventas.begin(), ventas.end(),
              [](const Venta &a, const Venta &b) { return a.fecha < b.fecha; });
    for (const auto &v : ventas) imprimirVenta(v);
}

// Ordenar por nota antes de la búsqueda
void ordenarPorNota(std::vector<Venta> &ventas) {
    std::sort(ventas.begin(), ventas.end(),
              [](const Venta &a, const Venta &b) { return a.nota < b.nota; });
}

// Búsqueda binaria por nota
int busquedaBinariaPorNota(const std::vector<Venta> &ventas, const std::string &notaBuscada) {
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

    return -1; // si no se encuentra
}

// Búsqueda secuencial por cantidad
void buscarPorCantidad(const std::vector<Venta> &ventas, double cantidadBuscada) {
    bool encontrado = false;
    for (const auto &v : ventas) {
        if (v.cantidad == cantidadBuscada) {
            imprimirVenta(v);
            encontrado = true;
        }
    }
    if (!encontrado) std::cout << "No se encontro esa cantidad.\n";
}

// Obtener día de la semana desde YYYY-MM-DD
std::string obtenerDiaSemana(const std::string &fecha) {
    int year, month, day;
    char sep;
    std::stringstream ss(fecha);
    ss >> year >> sep >> month >> sep >> day;

    std::tm time_in = {};
    time_in.tm_year = year - 1900;
    time_in.tm_mon = month - 1;
    time_in.tm_mday = day;

    std::mktime(&time_in); // Calcula el día de la semana

    const char* dias[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return dias[time_in.tm_wday];
}

// Búsqueda secuencial por día de la semana
void buscarPorDiaSemana(const std::vector<Venta> &ventas, const std::string &diaBuscado) {
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
