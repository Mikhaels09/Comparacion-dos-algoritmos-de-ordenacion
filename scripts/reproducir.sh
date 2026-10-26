#!/bin/bash
# Script de reproducción: compila el programa y ejecuta todas las mediciones.
# Uso (desde la carpeta del proyecto):
#   bash scripts/reproducir.sh            -> n = 1 000 y 10 000
#   bash scripts/reproducir.sh grande     -> también n = 100 000
# Si git no está disponible, puedes indicar el hash a mano:
#   HASH=a1b2c3d bash scripts/reproducir.sh

# Hash corto del último commit (se guarda en cada fila del CSV)
HASH=${HASH:-$(git rev-parse --short HEAD 2>/dev/null)}
HASH=${HASH:-sin_commit}

echo "Compilando..."
g++ -O2 -std=c++14 src/ordenamiento.cpp -o ordenamiento || exit 1

echo "Ejecutando mediciones (commit: $HASH)..."
./ordenamiento "$HASH" "$@"
