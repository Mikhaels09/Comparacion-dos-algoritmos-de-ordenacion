# Comparación de algoritmos de ordenación en C++

## Descripción
Este proyecto compara dos algoritmos de ordenación implementados en C++, midiendo su tiempo de ejecución, el número de comparaciones y el número de intercambios. Lo desarrollo de manera individual para el curso de Programación Avanzada.

## Algoritmos comparados
Elegí Inserción y Shell sort. Inserción es un método directo y Shell sort es una mejora de Inserción que compara elementos separados por saltos. Los escogí porque Shell parte de la misma idea que Inserción, y eso permite ver claramente cuánto mejora el rendimiento.

## Qué se mide
- Tiempo de ejecución (ms)
- Número de comparaciones
- Número de intercambios
- Profundidad de recursión (no aplica, porque ninguno de los dos es recursivo)

## Estructura del repositorio
- `src/`: código fuente en C++
- `data/`: resultados de las pruebas en archivos CSV
- `docs/`: artículo del proyecto
- `scripts/`: scripts para compilar y reproducir las pruebas
- `BITACORA.md`: registro de los avances y cambios

## Entorno de pruebas
- CPU: Intel Core i5-12450H (12.ª generación), 8 núcleos, 12 hilos, frecuencia base 2.00 GHz
- RAM: 15.7 GB
- Sistema operativo: Windows 11 Pro, versión 26H2 (compilación 26300.9711)
- Compilador: g++ 16.2.0 (MSYS2 UCRT64)

## Cómo ejecutar
bash scripts/reproducir.sh

## Estado
Hasta ahora creé el repositorio con su estructura y elegí los algoritmos (Inserción y Shell sort). Me falta programar el código, hacer las pruebas, los gráficos y el artículo.