#!/bin/bash

# Archivo de entrada con los números a ordenar
INPUT_FILE="lista_numeros_aleatorios.txt"
# Archivo CSV donde se guardarán los tiempos
OUTPUT_CSV="tiempos_ordenamiento.csv"

# Escribe la cabecera del archivo CSV
echo "Numero_Elementos,Tiempo_Ordenamiento (segundos)" > $OUTPUT_CSV

# Define los diferentes tamaños de subarreglos a ordenar
for n in 100000 200000 300000 400000 500000 600000 700000 800000 900000
do
    # Crea un archivo temporal con los primeros n números del archivo de entrada
    head -n $n $INPUT_FILE > temp_input.txt

    # Ejecuta el programa y captura únicamente el tiempo de ejecución
    TIEMPO=$(./ordenamiento32 < temp_input.txt)

    # Guarda el número de elementos y el tiempo en el archivo CSV
    echo "$n,$TIEMPO" >> $OUTPUT_CSV
    echo "Ordenamiento de $n elementos completado en $TIEMPO segundos."

    # Limpia el archivo temporal
    rm temp_input.txt
done

echo "Ejecuciones completadas. Los tiempos se han guardado en $OUTPUT_CSV."