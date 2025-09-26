# Ventas de una tienda
**Lucía Pérez Casas Gutiérrez | A01713181**  
Este proyecto maneja un registro de ventas con número de nota, fecha y cantidad, permitiendo ordenar y buscar de diferentes maneras para analizar la información.

## Avance de proyecto
### Guarda las cantidades vendidas
Cada venta tendrá 3 atributos:  
- Número de nota (ej. 001, 002, etc.)  
- Fecha (ej. 2025-09-23)  
- Cantidad de venta (ej. 350.75)  

Los datos se encuentran en un archivo en formato CSV y el programa lo leerá y cargará en un arreglo dinámico (vector).
Se utiliza ifstream para leer línea por línea y separar por comas.

### Ordenamiento
Se pueden ordenar los datos de menor a mayor según la necesidad:
- Por cantidad: para ver las ventas más altas y más bajas.
- Por fecha: para ver la evolución.

Se utilizó std::sort para facilitar este proceso.

### Busquedas
Se puede acceder a los datos de tres maneras diferentes:  

**1. Por número de nota → localizar una venta específica.**  
  Recorrer vector y comparar venta.nota == buscada.  
  -Se utiliza la *busqueda binaria* porque es más rápida.  
**2. Por cantidad exacta → ver si se vendió una cantidad determinada.**  
  Recorrer vector y verificar si venta.cantidad == buscada.  
  -Se utiliza la *busqueda secuencial*.  
**3. Por por día de la semana → filtrar, ej. todas las ventas de lunes.**  
  Convertir fecha a día con <ctime> (mktime + strftime).  
  Mostrar todas las ventas que coincidan (ej. “Monday”).  
  -Se utiliza la *busqueda secuencial*.

### Menú
Cuando se corre el programa, aparece un menú para que el usuario indique que desea hacer:
1. Ordenar por cantidad
2. Ordenar por fecha
3. Buscar por número de nota
4. Buscar por cantidad
5. Buscar por día de la semana
6. Salir

Según la opción seleccionada, se llamará a su función correspondiente.

## Uso del programa
**1. Preparar el archivo CSV:**  
   Guardar el archivo llamado ventas.csv en la misma carpeta que el programa.  
   Cada línea del archivo contiene: nota,fecha,cantidad.  
**3. Menú**  
  Al ejecutar, el programa muestra un menú con las opciones: ordenar por cantidad, ordenar por fecha, buscar por nota, buscar por cantidad, buscar por día de la semana o       salir.  
  Se ingresa el número de opción y luego los datos necesarios para la búsqueda (por ejemplo, número de nota o día de la semana).  
  Los resultados se imprimen en la terminal.  
**4. Ejemplo de uso**  
  -Si elige **1 (Ordenar por cantidad)** → se muestran todas las ventas ordenadas de menor a mayor según la cantidad.  
  -Si elige **3 (Buscar por número de nota)** → se pide el número de nota y devuelve la línea de esa venta.  
  -Si elige **5 (Buscar por día de la semana)** → se tiene que ingresar un día en inglés (ej. 'Monday') y el programa lista todas las ventas de ese día.   
**5. Salir**  
  Selecciona la opción **6** para terminar el programa.  

## Análisis de complejidad
### Ordenamiento:
Se utilizó std::sort, que en la mayoría de las implementaciones modernas de C++ es introsort (una combinación de quicksort, heapsort e insertion sort).
En teoría, std::sort es un algoritmo de ordenamiento que el compilador ya trae optimizado, y ese algoritmo interno se llama Introsort, que mezcla quicksort (rápido en promedio), heapsort (para evitar el peor caso On^2) e insertion sort (para tramos pequeños). Esto hace que complejidad esté garantizada en O(nlogn) en el mejor, promedio y peor de los casos.
- **Mejor caso**: *O(nlogn)* → Si el elemento se encuentra justo en el centro en la primera comparación.
- **Caso promedio**: *O(nlogn)*.
- **Peor caso**: *O(logn)* → Aunque no esté el elemento, se requiere dividir hasta agotar el rango.

### Búsqueda:
1. Por número de nota (binaria):
- **Mejor caso**: *O(1)* → Si el elemento se encuentra justo en el centro en la primera comparación.
- **Caso promedio**: *O(logn)*.
- **Peor caso**: *O(logn)* → Aunque no esté el elemento, se requiere dividir hasta agotar el rango.

3. Por cantidad exacta (secuencial):
- **Mejor caso**: *O(1)* → Si el primer elemento coincide.
- **Caso promedio**: *O(n)*.
- **Peor caso**: *O(n)* → Si no existe el elemento o se encuentra en la última posición.

5. Por día de la semana (secuencial):
- **Mejor caso**: *O(1)* → Si el primer elemento coincide.
- **Caso promedio**: *O(n)*.
- **Peor caso**: *O(n)* → Si no existe el elemento o se encuentra en la última posición.

  
