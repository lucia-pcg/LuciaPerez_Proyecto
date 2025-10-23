# Sistema de Gestión de Ventas

**Lucía Pérez Casas Gutiérrez – A01713181**  
**Fecha:** 23/09/2025  

Este proyecto permite almacenar, ordenar y acceder a datos de ventas de una tienda.  
Cada venta incluye un número de nota, una fecha y una cantidad.  
El programa permite ordenar y buscar registros de forma eficiente mediante algoritmos de ordenamiento y búsqueda.

---

## Descripción del avance del proyecto

### Funcionalidad principal

El programa lee los datos de un archivo `ventas.csv`, donde cada línea contiene:
```
nota,fecha,cantidad
```
Ejemplo:
```
001,2025-09-21,300.50
002,2025-09-22,150.00
003,2025-09-23,500.00
```

Los datos se cargan en un `std::vector<Venta>`, que actúa como un arreglo dinámico.

### Opciones disponibles en el menú

1. **Ordenar por cantidad**  
   Usa `std::sort` para ordenar las ventas de menor a mayor según el monto.

2. **Ordenar por fecha**  
   Permite visualizar la evolución de las ventas en orden cronológico.

3. **Buscar por número de nota (búsqueda binaria)**  
   Ordena primero por nota y luego busca eficientemente una venta específica.

4. **Buscar por cantidad (búsqueda secuencial)**  
   Permite saber si existe una venta con cierta cantidad.

5. **Buscar por día de la semana (búsqueda secuencial)**  
   Convierte la fecha a día de la semana (usando `std::tm` y `mktime`) y filtra las ventas por día (ej. “Monday”).

6. **Salir**  
   Finaliza la ejecución del programa.

---

## Instrucciones de uso

1. Guarda el archivo `ventas.csv` en la misma carpeta que los archivos `.cpp` y `.h`.
2. Compila el programa (por ejemplo en Linux/Mac):
   ```bash
   g++ main.cpp -o ventas
   ```
3. Ejecuta el programa:
   ```bash
   ./ventas
   ```
4. Usa el menú interactivo para elegir las opciones.
   Ejemplo:
   ```
   ---- MENU ----
   1. Ordenar por cantidad
   2. Ordenar por fecha
   3. Buscar por número de nota
   ...
   ```
5. Introduce los valores solicitados (nota, cantidad o día) según la opción.

---

## SICT0301: Evalúa los componentes

### Análisis de complejidad

#### Algoritmo de ordenamiento (`std::sort`)
`std::sort` utiliza **Introsort**, una mezcla de tres algoritmos:
- **Quicksort** (divide y conquista, O(n log n) promedio),
- **Heapsort** (evita el peor caso de quicksort, O(n log n)),
- **Insertionsort** (optimiza tramos pequeños, O(n²) en segmentos reducidos).

Por tanto, su complejidad general es:
- **Mejor caso:** O(n log n)
- **Caso promedio:** O(n log n)
- **Peor caso:** O(n log n)

La corrección del profesor aplica aquí: no es el compilador quien optimiza, sino la **implementación de la librería estándar** (`<algorithm>`), que usa introsort internamente.

#### Búsquedas implementadas

| Tipo de búsqueda | Método | Complejidad mejor | Promedio | Peor |
|------------------|---------|------------------|-----------|-------|
| Por número de nota | Binaria | O(1) | O(log n) | O(log n) |
| Por cantidad | Secuencial | O(1) | O(n) | O(n) |
| Por día de la semana | Secuencial | O(1) | O(n) | O(n) |

Cada búsqueda fue seleccionada en función de la naturaleza de los datos y su frecuencia de uso.

---

## SICT0302: Toma decisiones

### Selecciona un algoritmo de ordenamiento adecuado al problema

Se eligió `std::sort` (Introsort) por ser el método más eficiente para ordenar vectores en C++:
- Garantiza **O(n log n)** incluso en el peor caso.
- Usa comparadores personalizados (por cantidad o fecha) fácilmente adaptables.
- Minimiza el uso de memoria adicional.

### Usa el algoritmo correctamente dentro del programa

Cada opción de ordenamiento o búsqueda está implementada como una función modular independiente:
- `ordenarPorCantidad(vector<Venta> &ventas)`
- `ordenarPorFecha(vector<Venta> &ventas)`
- `ordenarPorNota(vector<Venta> &ventas)`
- `busquedaBinariaPorNota(...)`
- `buscarPorCantidad(...)`
- `buscarPorDiaSemana(...)`

El menú principal (`main.cpp`) centraliza el flujo del programa y llama a las funciones adecuadas según la opción seleccionada.

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

---

## Conclusión

El programa cumple con la organización, acceso y análisis de datos requeridos en esta etapa.  
Se aplicaron algoritmos de ordenamiento y búsqueda con una complejidad garantizada y un enfoque modular.  
Además, se siguió el formato de competencias del curso y se corrigió el análisis de introsort conforme al comentario del profesor.
