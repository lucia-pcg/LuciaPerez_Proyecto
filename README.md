# Ventas de una tienda
Este proyecto maneja un registro de ventas con número de nota, fecha y cantidad, permitiendo ordenar y buscar de diferentes maneras para analizar la información.

### Avance de proyecto
## Guarda las cantidades vendidas
Cada venta tendrá 3 atributos:
- Número de nota (ej. 001, 002, etc.)
- Fecha (ej. 2025-09-23)
- Cantidad de venta (ej. 350.75)

Los datos se encuentran en un archivo en formato CSV y el programa lo leerá y cargará en un arreglo dinámico (vector).
Se utiliza ifstream para leer línea por línea y separar por comas.

## Ordenamiento
Se pueden ordenar los datos de menor a mayor según la necesidad:
- Por cantidad: para ver las ventas más altas y más bajas.
- Por fecha: para ver la evolución.

Se utilizó std::sort para facilitar este proceso.

## Busquedas
Se puede acceder a los datos de tres maneras diferentes:
**1. Por número de nota → localizar una venta específica.**
  Recorrer vector y comparar venta.nota == buscada.
  - Se utiliza la busqueda binaria porque es más rápida.
**2. Por cantidad exacta → ver si se vendió una cantidad determinada.**
  Recorrer vector y verificar si venta.cantidad == buscada.
  - Se utiliza la busqueda secuencial.
**3. Por por día de la semana → filtrar, ej. todas las ventas de lunes.**
  Convertir fecha a día con <ctime> (mktime + strftime).
  Mostrar todas las ventas que coincidan (ej. “Monday”).
  - Se utiliza la busqueda secuencial.

## Menú
Cuando se corre el programa, aparece un menú para que el usuario indique que desea hacer:
1. Ordenar por cantidad
2. Ordenar por fecha
3. Buscar por número de nota
4. Buscar por cantidad
5. Buscar por día de la semana
6. Salir

Según la opción seleccionada, se llamará a su función correspondiente.

### Uso del programa

### Análisis de complejidad


  
