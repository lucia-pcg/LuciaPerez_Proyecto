# Sistema de Gestión de Ventas

**Lucía Pérez Casas Gutiérrez – A01713181**  
**Fecha:** 23/09/2025  

Este proyecto permite almacenar, ordenar y acceder a datos de ventas de una tienda.  
Cada venta incluye un número de nota, una fecha y una cantidad.  
El objetivo es organizar la información de forma eficiente y poder acceder a los datos según diferentes criterios.

---

## Descripción del avance del proyecto

### Funcionalidad principal

El programa carga la información desde un archivo `ventas.csv`, donde cada línea contiene una venta con los siguientes campos:
```
nota,fecha,cantidad
```
Ejemplo:
```
001,2025-09-21,300.50
002,2025-09-22,150.00
003,2025-09-23,500.00
```

Los datos se guardan en un `std::deque<Venta>`, una estructura dinámica que permite almacenar y acceder eficientemente a los registros.
Después, se pueden ordenar o buscar dependiendo de lo que el usuario necesite.

### Opciones disponibles en el menú

1. **Ordenar por cantidad**  
   Ordena las ventas de menor a mayor según la cantidad.
2. **Ordenar por fecha**  
   Ordena las ventas de manera cronológica.
3. **Buscar por número de nota (búsqueda binaria)**  
   Ordena previamente por nota y permite localizar una venta específica.
4. **Buscar por cantidad (búsqueda secuencial)**  
   Busca las ventas que coincidan con una cantidad exacta.
5. **Buscar por día de la semana (búsqueda secuencial)**  
   Convierte la fecha en día de la semana y muestra todas las ventas realizadas ese día.
6. **Salir**  
   Finaliza la ejecución del programa.

---

## Instrucciones de uso

1. Guarda el archivo `ventas.csv` en la misma carpeta donde están los archivos `main.cpp` y `ventas.h`.
2. Compila el programa:
   ```bash
   g++ main.cpp -o ventas
   ```
3. Ejecuta el programa:
   ```bash
   ./ventas
   ```
4. Selecciona una opción del menú e ingresa los valores solicitados (nota, cantidad o día).

---

## SICT0301: Evalúa los componentes

### Análisis de complejidad

#### Estructura de datos: `std::deque`
- **Inserción y eliminación en ambos extremos:** O(1).  
- **Acceso por índice:** O(1).  
- **Recorrido completo:** O(n).

#### Ordenamiento (`std::sort` – Introsort)
- Basado en **Quicksort**, con respaldo de **Heapsort** y optimización final con **Insertionsort**.

| Algoritmo         | Mejor caso | Caso promedio | Peor caso  |
| ----------------- | ---------- | ------------- | ---------- |
| **Quicksort**     | O(n log n) | O(n log n)    | O(n²)      |
| **Heapsort**      | O(n log n) | O(n log n)    | O(n log n) |
| **Insertionsort** | O(n)       | O(n²)         | O(n²)      |

###### Complejidad final:
- **Mejor caso:** O(n log n) (cuando Quicksort divide bien los datos)  
- **Caso promedio:** O(n log n)  
- **Peor caso:** O(n^2) en el caso de que el arreglo sea muy pequeño y no esté ordenado.  

#### Búsquedas
| Tipo | Método | Mejor | Promedio | Peor |
|------|---------|--------|-----------|-------|
| Por número de nota | Binaria | O(1) | O(log n) | O(log n) |
| Por cantidad | Secuencial | O(1) | O(n) | O(n) |
| Por día de la semana | Secuencial | O(1) | O(n) | O(n) |

Cada función tiene una complejidad adecuada para su propósito. Las búsquedas secuenciales se usan cuando los datos no necesitan orden previo, y la binaria cuando los datos ya están ordenados.

---

## SICT0302: Toma decisiones

### Selecciona una estructura de datos adecuada al problema y la usa correctamente

Elegí `std::deque` para almacenar los datos de mi proyecto por las siguientes razones:

**1. Inserción y eliminación eficientes en ambos extremos:**
A diferencia de vector, que solo inserta rápido al final, deque permite agregar o eliminar elementos tanto al inicio como al final en tiempo constante O(1).  
> *Esto resulta útil si en el futuro se necesita registrar nuevas ventas al principio o final de la lista sin tener que copiar todos los elementos.*

**2. Acceso aleatorio rápido:**
Deque permite acceder a cualquier elemento mediante índices (ventas[i]) en tiempo constante.  
> *Esto es importante porque el programa utiliza búsquedas binarias y recorridos que requieren acceso directo a posiciones específicas, manteniendo la eficiencia O(1) en       lectura.*

**3. Mejor aprovechamiento de la memoria en inserciones intermedias:**
Deque gestiona sus elementos en bloques de memoria independientes conectados internamente, en lugar de usar un único bloque continuo.
> *Esto permite agregar o eliminar elementos sin necesidad de copiar grandes cantidades de datos, reduciendo la sobrecarga de memoria y manteniendo estable el rendimiento incluso con muchos registros de ventas.*

**4. Adecuado para un sistema que evoluciona**
El programa actualmente solo carga, ordena y busca ventas, pero deque ofrece una base más escalable si el sistema crece, sin que el programa se vuelva más lento ni consuma más memoria.
> *Por ejemplo, se podría implementar fácilmente una cola de ventas pendientes o de registros antiguos, donde los datos ya procesados o antigüos se eliminen desde el inicio y las ventas nuevas se agreguen al final*

### Selecciona un algoritmo de ordenamiento adecuado al problema

Elegí `std::sort` ya que usa Introsort internamente, garantizando un rendimiento O(n log n) en la mayoría de los casos.  
También permite definir comparadores personalizados para ordenar por **cantidad**, **fecha** o **nota**, según la necesidad del usuario.

---

## SICT0303: Implementa acciones científicas

### Implementa mecanismos para consultar información de las estructuras

El programa incluye un menú que permite ordenar o buscar ventas según diferentes criterios.  
Cada función fue diseñada de forma modular para poder acceder a los datos de manera clara y rápida.

### Implementa mecanismos de lectura de archivos

La función `cargarDatos` utiliza `ifstream` para leer el archivo `ventas.csv`, separa los valores por comas con `getline`, y convierte las cantidades a tipo `double` usando `stod`.  
De esta forma, los datos se cargan correctamente en el vector de ventas antes de realizar los ordenamientos o búsquedas.

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
