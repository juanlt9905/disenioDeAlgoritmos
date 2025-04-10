#!/bin/bash

# Archivo de entrada con los números a ordenar
INPUT_FILE="lista_numeros_aleatorios.txt"


# Define los diferentes tamaños de subarreglos a ordenar
for n in 100000 
do
    # Crea un archivo  con los primeros n números del archivo de entrada, omitiendo la primera línea
    tail -n +2 $INPUT_FILE | head -n $n > borrar_input.txt
done