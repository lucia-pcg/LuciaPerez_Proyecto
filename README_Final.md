# Sistema de Gestión de Ventas

**Lucía Pérez Casas Gutiérrez – A01713181**  
**Fecha:** 17/11/2025  

Este proyecto permite almacenar, ordenar y acceder a datos de ventas de una tienda.  
Cada venta incluye un número de nota, una fecha y una cantidad.  
El objetivo es organizar la información de forma eficiente y poder acceder a los datos según diferentes criterios.

---

## Descripción del avance del proyecto

### Funcionalidad principal

El usuario tiene la posibilidad de elegir los productos de cada compra y agregarlos al carrito para al final del día cargar las notas de venta acumuladas a la base de datos de la tienda.
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

Los datos de las compras del día se van guardando en un `std::deque<Venta>`, una estructura dinámica que permite almacenar y acceder eficientemente a los registros, para después cargarlos uno por uno al excel y poder consultarlos u ordenarlos según el orden que el usuario necesite.

**Productos disponibles (ropa de bebé):**
El menú de productos incluye siete artículos de ropa de bebé:

1. Body ($150)
2. Mameluco ($250)
3. Vestido ($480)
4. Conjunto ($750)
5. Calcetines ($60)
6. Set de almohadas ($300)
7. Babero ($45)

El usuario puede seleccionar varios artículos y el programa irá sumando sus precios hasta que seleccione la opción "Terminar compra".
Al final, el número de nota lo ingresa manualmente el usuario (no se genera automáticamente).

### Opciones disponibles en el menú principal

1. **Comenzar día**
   Solicita la fecha del día e ingresa al submenú de registro de ventas.
2. **Mostrar las ventas (ordenadas por número de nota)**  
   Ordena primero todas las ventas por nota con `ordenarPorNota()` y las muestra con `imprimirVenta()`.
3. **Ordenar por cantidad**  
   Ordena las ventas de menor a mayor según la cantidad.
4. **Ordenar por fecha**  
   Ordena las ventas de manera cronológica.
5. **Buscar por número de nota (búsqueda binaria)**  
   Ordena previamente por nota y permite localizar una venta específica.
6. **Buscar por cantidad (búsqueda secuencial)**  
   Busca las ventas que coincidan con una cantidad exacta.
7. **Buscar por día de la semana (búsqueda secuencial)**  
   Convierte la fecha en día de la semana y muestra todas las ventas realizadas ese día.
8. **Salir**  
   Finaliza la ejecución del programa.

### Menú de "Comenzar día"

Requiere al usuario que ingrese la fecha del día y luego muestra las siguientes opciones:
1. **Registrar venta**
   Muestra un menú de los productos disponibles junto con su precio y el usuario elige los artículos que quiere comprar. 
2. **Cierre de lote**
   Todas las ventas registradas del día se agregan al historial y se reescribe **completamente** `ventas.csv` con todas las ventas acumuladas.
   
Después de cargar las ventas del día regresa al menú principal.

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
4. Elige la 'opción 1' del menú principal para registrar nuevas ventas.
5. Selecciona una opción del menú principal e ingresa los valores solicitados (nota, cantidad o día).

---

## SICT0301: Evalúa los componentes

### Análisis de complejidad

#### Estructura de datos: `std::deque`

##### _Acceso por índice_
- **Mejor caso:** O(1).  
  El elemento se encuentra rápidamente porque el cálculo de su ubicación de acuerdo al índice es inmediato.
- **Caso promedio:** O(1).  
  `std::deque` divide los datos en varios bloques y puede determinar de manera inmediata en qué bloque está cualquier índice, sin recorrer elementos.
- **Peor caso:** O(1).  
  Aunque el elemento esté en un bloque distinto, el acceso sigue siendo constante porque solo se calcula qué bloque contiene la posición solicitada y cuál es la posición exacta dentro de ese bloque.
  
*En el programa, este tipo de acceso ocurre en la búsqueda binaria (`ventas[mid]`) en las líneas 145 y 147 del header y cuando se imprime la venta encontrada (`ventas[indice]`) en la línea 74 del main.*

##### _Inserciones (push_back)_
- **Mejor caso:** O(1).  
  No hay reacomodo del mapa de bloques.
- **Caso promedio:** O(1).  
  Lo normal: agregar a un bloque existente o crear uno nuevo.
- **Peor caso:** O(n).  
  El mapa de bloques se queda sin espacio (se duplica el mapa).

##### _Eliminación en extremos (pop_front y pop_back)_
La eliminación en los extremos de un deque siempre toma tiempo constante porque no requiere mover todos los elementos como en un vector.
- **Mejor caso:** O(1).
  Se elimina un elemento en el primer o último bloque sin necesidad de liberar un bloque completo. La operación solo actualiza un puntero.
- **Caso promedio:** O(1).  
  Normalmente, eliminar un elemento simplemente reduce el índice interno del bloque correspondiente. No hay desplazamientos ni copias.
- **Peor caso:** O(1).  
  Incluso si al eliminar el último elemento de un bloque este queda vacío y el bloque se libera, la operación sigue siendo constante, porque:
   - Se elimina un bloque completo de tamaño fijo.
   - No se ve afectado el resto del deque.
   - El número de operaciones no depende de n, sino del tamaño de bloque (constante).

##### _Recorrido completo_
- **Mejor caso:** O(n) Elementos en pocos bloques (menos saltos).  
- **Caso promedio:** O(n) Distribución normal de bloques.  
- **Peor caso:** O(n) Los elementos quedaron muy fragmentados en bloques.
 
*(La fragmentación en bloques no cambia la complejidad.)*

#### Ordenamiento (`std::sort` – Introsort)
- Basado en **Quicksort**, con respaldo de **Heapsort** y optimización final con **Insertionsort**.

| Algoritmo         | Mejor caso | Caso promedio | Peor caso  |
| ----------------- | ---------- | ------------- | ---------- |
| **Quicksort**     | O(n log n) | O(n log n)    | O(n²)      |
| **Heapsort**      | O(n log n) | O(n log n)    | O(n log n) |
| **Insertionsort** | O(n)       | O(n²)         | O(n²)      |

###### Complejidad final:
- **Mejor caso:** O(n log n) cuando Quicksort divide bien los datos.  
- **Caso promedio:** O(n log n).  
- **Peor caso:** O(n^2) en el caso de que el arreglo sea muy pequeño y no esté ordenado.  

#### Búsquedas
| Tipo | Método | Mejor | Promedio | Peor |
|------|---------|--------|-----------|-------|
| Por número de nota | Binaria | O(1) | O(log n) | O(log n) |
| Por cantidad | Secuencial | O(1) | O(n) | O(n) |
| Por día de la semana | Secuencial | O(1) | O(n) | O(n) |

Cada función tiene una complejidad adecuada para su propósito. Las búsquedas secuenciales se usan cuando los datos no necesitan orden previo, y la binaria cuando los datos ya están ordenados.

#### Complejidad final del programa
El programa realiza lectura/escritura de archivos (O(n)), ordenamientos y búsquedas. 

**Mejor caso:**  
~ Impresiones → O(n)  

  >*O(n)*

**Caso promedio:**  
~ Algunas búsquedas secuenciales → O(n)  
~ Una o varias ordenaciones → O(n log n)  
~ Escritura del archivo → O(n)  

  >*O(n log n)*

**Peor caso:**  
~ Lectura del archivo → O(n)  
~ Cierre de lote → O(n + m)  
~ Ordenamientos completos → O(n²)  
~ Varias búsquedas secuenciales → O(n)  
~ Escritura del archivo → O(n)  
  
  >*O(n²)*

.  
.  

La operación más costosa es `std::sort`, por lo que la complejidad final es:
>***O(n²)***

---

## SICT0302: Toma decisiones

### Selecciona una estructura de datos adecuada al problema y la usa correctamente

Elegí `std::deque` para almacenar los datos de mi proyecto por las siguientes razones:

**1. Manejo eficiente de las ventas del día en el cierre de lote:**
Durante el día, las ventas nuevas se acumulan en un deque temporal.
Al hacer cierre de lote, el programa:
- Vacía ese deque de ventas del día
- Inserta sus elementos al final del deque principal de todas las ventas
- Escribe el resultado actualizado en el CSV

> *En el programa, `std::deque` es ideal para esto porque permite mover cientos de ventas del día al final del historial sin reacomodar toda la memoria.*

**2. Inserción y eliminación eficientes en ambos extremos:**
A diferencia de vector, que solo inserta rápido al final, deque permite agregar o eliminar elementos tanto al inicio como al final en tiempo constante O(1).  
> *Esto resulta útil si en el futuro se necesita registrar nuevas ventas al principio o final de la lista sin tener que copiar todos los elementos.*

**3. Mejor aprovechamiento de la memoria en inserciones grandes:**
Deque gestiona sus elementos en bloques de memoria independientes conectados internamente, en vez de un solo bloque continuo como `std::vector`. Esto permite agregar o eliminar elementos sin necesidad de copiar grandes cantidades de datos, reduciendo la sobrecarga de memoria y manteniendo estable el rendimiento incluso con muchos registros de ventas. Con vector, cuando se llena su espacio, debe reservar un bloque nuevo y copiar todos los elementos anteriores, lo cual es costoso para listas grandes.
> *En cada “cierre de lote” el programa carga todas las ventas del día y las agrega al final. Cuando se agregan muchas ventas juntas, no se copia todo el historial de ventas.*

**4. Adecuado para un sistema que evoluciona**
El programa actualmente solo carga, ordena, busca y guarda ventas, pero deque ofrece una base más escalable si el sistema crece, sin que el programa se vuelva más lento ni consuma más memoria.
> *Por ejemplo, se podría implementar fácilmente una cola de ventas pendientes o de registros antiguos, donde los datos ya procesados o antigüos se eliminen desde el inicio y las ventas nuevas se agreguen al final*

### Selecciona un algoritmo de ordenamiento adecuado al problema

Elegí `std::sort` ya que usa Introsort internamente, garantizando una complejidad de O(n log n) en el caso promedio y de O(n^2) en el peor de los casos, lo que es poco probable porque la cantidad de datos que se manejan en el programa no es tan pequeña. También permite definir comparadores personalizados para ordenar por **cantidad**, **fecha** o **nota**, según la necesidad del usuario.

En comparación con otros algoritmos de ordenamiento, considero que es la mejor opción porque combina lo mejor de varios lo que provee mejor rendimiento. Por ejemplo, en el caso de `Bubble Sort` e `Insertion Sort`, su complejidad en el mejor caso es O(n), pero en el peor caso y caso promedio es O(n^2). Por otra parte, `Selection Sort` tiene una complejidad de O(n^2) en todos los casos. Si comparamos las complejidades de estos 3 algoritmos con las de introsort, tomando en cuenta el contexto del problema, introsort(std::sort), parece ser una buena opción.

---

## SICT0303: Implementa acciones científicas

### Implementa mecanismos para consultar información de las estructuras

El programa incluye un menú que permite registrar, ordenar o buscar ventas según diferentes criterios.  
Cada función fue diseñada de forma modular para poder acceder a los datos de manera clara y rápida.

### Implementa mecanismos de lectura de archivos

La función `cargarDatos` utiliza `ifstream` para leer el archivo `ventas.csv`, separa los valores por comas con `getline`, y convierte las cantidades a tipo `double` usando `stod`.  
De esta forma, los datos se cargan correctamente en el deque de ventas antes de realizar los ordenamientos o búsquedas.

### Implementa mecanismos de escritura de archivos para guardar los datos de las estructuras de manera correcta.
El programa escribe las ventas usando `ofstream`:
```
ofstream file(archivo);
```
Esto significa que sobreescribe el archivo completo agregando las ventas del día al final y ventas.csv actúa como historial de ventas. Esto mantiene un historial limpio y ordenado sin duplicar datos.

---

## Ejemplo de ejecución

```
---- MENU ----
1. Comenzar dia
2. Mostrar las ventas (ordenadas por numero de nota)
3. Ordenar por cantidad
4. Ordenar por fecha
5. Buscar por numero de nota
6. Buscar por cantidad
7. Buscar por dia de la semana
8. Salir
Selecciona una opcion: 1

Ingresa la fecha del día (YYYY-MM-DD): 2025-09-25

--- MENU DEL DÍA ---
1. Registrar venta
2. Cierre de lote
Elige una opción: 1

--- MENU DE PRODUCTOS ---
1. Body ($150)
2. Mameluco ($250)
3. Vestido ($480)
4. Conjunto ($750)
5. Calcetines ($60)
6. Set de almohadas ($300)
7. Babero ($45)
8. Terminar compra
Elige una opción: 1
Elige una opción: 2
Elige una opción: 4
Ingresa número de nota: 004
Venta registrada:
Nota: 004 - Fecha: 2025-09-25 - Cantidad: 1150

--- MENU DEL DÍA ---
1. Registrar venta
2. Cierre de lote
Elige una opción: 1

--- MENU DE PRODUCTOS ---
1. Body ($150)
2. Mameluco ($250)
3. Vestido ($480)
4. Conjunto ($750)
5. Calcetines ($60)
6. Set de almohadas ($300)
7. Babero ($45)
8. Terminar compra
Elige una opción: 3
Elige una opción: 3
Elige una opción: 7
Ingresa número de nota: 005
Venta registrada:
Nota: 005 - Fecha: 2025-09-25 - Cantidad: 1005

--- MENU DEL DÍA ---
1. Registrar venta
2. Cierre de lote
Elige una opción: 2

Cierre de lote completado. Registro de ventas actualizado.

---- MENU ----
1. Comenzar dia
2. Mostrar las ventas (ordenadas por numero de nota)
3. Ordenar por cantidad
4. Ordenar por fecha
5. Buscar por numero de nota
6. Buscar por cantidad
7. Buscar por dia de la semana
8. Salir
Selecciona una opcion: 3

Nota: 005 - Fecha: 2025-09-25 - Cantidad: 1005
Nota: 004 - Fecha: 2025-09-25 - Cantidad: 1150

---- MENU ----
1. Comenzar dia
2. Mostrar las ventas (ordenadas por numero de nota)
3. Ordenar por cantidad
4. Ordenar por fecha
5. Buscar por numero de nota
6. Buscar por cantidad
7. Buscar por dia de la semana
8. Salir
Selecciona una opcion: 5

Ingrese el numero de nota: 004
Nota: 004 - Fecha: 2025-09-25 - Cantidad: 1150
```
