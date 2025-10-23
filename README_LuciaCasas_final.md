# Sistema de Gestión de Ventas

**Lucía Pérez Casas Gutiérrez – A01713181**  
**Fecha:** 23/09/2025  

Este proyecto permite almacenar, ordenar y acceder a datos de ventas de una tienda.  
Cada venta incluye un número de nota, una fecha y una cantidad.  
El objetivo es poder organizar la información de distintas formas y facilitar la búsqueda de datos de manera eficiente.

---

## Descripción del avance del proyecto

### Funcionalidad principal

El programa lee los datos desde un archivo llamado `ventas.csv`, donde cada línea contiene la información de una venta:
```
nota,fecha,cantidad
```
Por ejemplo:
```
001,2025-09-21,300.50
002,2025-09-22,150.00
003,2025-09-23,500.00
```

Los datos se cargan en un `std::vector<Venta>` para poder manipularlos de forma dinámica.  
Cada venta tiene tres atributos: número de nota, fecha y cantidad.  
Después de cargar los datos, el programa permite ordenarlos y hacer búsquedas con diferentes criterios.

### Opciones disponibles en el menú

1. **Ordenar por cantidad**  
   Muestra las ventas ordenadas de menor a mayor según la cantidad.
2. **Ordenar por fecha**  
   Permite ver las ventas en orden cronológico.
3. **Buscar por número de nota (búsqueda binaria)**  
   Ordena por nota antes de buscar, lo que permite encontrar una venta específica más rápido.
4. **Buscar por cantidad (búsqueda secuencial)**  
   Busca todas las ventas que coincidan con la cantidad que se indique.
5. **Buscar por día de la semana (búsqueda secuencial)**  
   Convierte la fecha a un día de la semana y muestra todas las ventas registradas en ese día.
6. **Salir**  
   Termina la ejecución del programa.

---

## Instrucciones de uso

1. Guarda el archivo `ventas.csv` en la misma carpeta donde tengas los archivos del programa (`main.cpp` y `ventas.h`).
2. Compila el programa:
   ```bash
   g++ main.cpp -o ventas
   ```
3. Ejecuta el programa:
   ```bash
   ./ventas
   ```
4. Usa el menú para elegir la opción que quieras.  
   Por ejemplo:
   ```
   ---- MENU ----
   1. Ordenar por cantidad
   2. Ordenar por fecha
   3. Buscar por número de nota
   ...
   ```
5. Introduce los valores que el programa te pida (como número de nota, cantidad o día de la semana) para realizar la búsqueda o el ordenamiento.

---

## SICT0301: Evalúa los componentes

### Análisis de complejidad

#### Algoritmo de ordenamiento (`std::sort`)

Para ordenar se utiliza `std::sort`, que internamente usa **Introsort**.  
Este algoritmo combina tres métodos:  
- **Quicksort**, que es muy rápido en promedio.  
- **Heapsort**, que se usa para evitar el peor caso de quicksort.  
- **Insertionsort**, que se aplica en los tramos pequeños para hacerlo más eficiente.  

La complejidad total se mantiene en:
- **Mejor caso:** O(n log n)  
- **Caso promedio:** O(n log n)  
- **Peor caso:** O(n log n)

#### Búsquedas implementadas

| Tipo de búsqueda | Método | Mejor caso | Promedio | Peor caso |
|------------------|---------|-------------|-----------|------------|
| Por número de nota | Binaria | O(1) | O(log n) | O(log n) |
| Por cantidad | Secuencial | O(1) | O(n) | O(n) |
| Por día de la semana | Secuencial | O(1) | O(n) | O(n) |

---

## SICT0302: Toma decisiones

### Selecciona un algoritmo de ordenamiento adecuado al problema

Elegí usar `std::sort` porque es eficiente y confiable para vectores en C++.  
Su rendimiento está garantizado en **O(n log n)** y permite usar comparadores personalizados para ordenar por cantidad, fecha o nota.  
Además, no necesita estructuras adicionales ni consume mucha memoria.

### Usa el algoritmo correctamente dentro del programa

Cada función de ordenamiento o búsqueda está implementada de forma modular en el archivo `ventas.h`, por ejemplo:
- `ordenarPorCantidad(vector<Venta> &ventas)`  
- `ordenarPorFecha(vector<Venta> &ventas)`  
- `ordenarPorNota(vector<Venta> &ventas)`  
- `busquedaBinariaPorNota(...)`  
- `buscarPorCantidad(...)`  
- `buscarPorDiaSemana(...)`

El menú principal en `main.cpp` controla todo el flujo y llama a las funciones dependiendo de la opción que el usuario elija.

---

## Ejemplo de ejecución

```
---- MENU ----
1. Ordenar por cantidad
2. Ordenar por fecha
3. Buscar por número de nota
4. Buscar por cantidad
5. Buscar por día de la semana
6. Salir
Selecciona una opción: 1

Nota: 002 - Fecha: 2025-09-22 - Cantidad: 150
Nota: 001 - Fecha: 2025-09-21 - Cantidad: 300.5
Nota: 003 - Fecha: 2025-09-23 - Cantidad: 500
```
