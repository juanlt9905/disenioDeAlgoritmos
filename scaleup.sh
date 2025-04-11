#!/bin/bash

# Nombre del archivo ejecutable
executable="./ordenamiento3"

# Nombre del archivo de entrada
input_file="lista_numeros_aleatorios.txt"

# Nombre del archivo CSV de salida
output_csv="scaleup_ordenamiento3.csv"

# Compilar el programa
gcc -o ordenamiento3 ordenamiento3.c

# Escribir encabezado en el archivo CSV
echo "longitud_ordenamiento,tiempo" > $output_csv

# Lista de tamaños a probar
sizes=(100000 200000 300000 400000 500000 600000 700000)

# Ejecutar el programa para cada tamaño y capturar los resultados
for size in "${sizes[@]}"; do
    # Ejecutar el programa y capturar la salida
    result=$($executable $size < $input_file)
    
    # Agregar el resultado al archivo CSV
    echo "$size,$result" >> $output_csv

    echo "Termina Ordenacion de $size elementos."
done

echo "Resultados guardados en $output_csv"