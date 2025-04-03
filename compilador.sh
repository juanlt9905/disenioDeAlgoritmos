#!/bin/bash

# Compila los tres programas de ordenamiento

gcc ordenamiento_clase.c -o ordenamiento_clase
gcc ordenamiento2.c -o ordenamiento2
gcc ordenamiento3.c -o ordenamiento3
gcc generarRand.c -o generarRand

# Verifica si la compilación fue exitosa
if [ $? -eq 0 ]; then
    echo "Compilación exitosa."
else
    echo "Error de compilación."
    exit 1  # Salir con un código de error
fi