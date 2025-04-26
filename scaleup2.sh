#!/bin/bash

# Nombre del archivo ejecutable
executable="./merge_sort"

# Nombre del archivo de entrada
input_file="lista_numeros_aleatorios.txt"

# Nombre del archivo CSV de salida
output_csv="scaleup_merge_sort.csv"

# Compilar el programa
gcc -o merge_sort merge_sort.c

# Escribir encabezado en el archivo CSV
echo "longitud_ordenamiento,tiempo" > $output_csv

# Lista de tamaños a probar
#sizes=(250000 500000 750000 1000000 1250000 1500000 1750000 2000000)

#sizes=(1000000)
min_size=100000
max_size=2000000
step=100000
# Ejecutar el programa para cada tamaño y capturar los resultados
for size in $(seq $min_size $step $max_size); do
    for i in {1..30}; do
        # Ejecutar el programa y capturar la salida
        result=$($executable $size < $input_file)
        
        # Agregar el resultado al archivo CSV
        echo "$size,$result" >> $output_csv

        echo "Termina Ordenacion de $size elementos."
    
    done
done

echo "Resultados guardados en $output_csv"