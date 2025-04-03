#!/bin/bash

# Archivo de entrada con los números a ordenar
INPUT_FILE="lista_numeros_aleatorios.txt"
# Archivo CSV donde se guardarán los tiempos
OUTPUT_CSV="tiempos.csv"

# Escribe la cabecera del archivo CSV
echo "Ejecución,Tiempo_Ordenamiento1 (segundos),Tiempo_Ordenamiento2 (segundos),Tiempo_Ordenamiento3 (segundos)" > $OUTPUT_CSV

# Ejecuta el programa 30 veces
for i in {1..2}
do
    # Redirige la entrada y ejecuta en segundo plano, capturando la salida
    { taskset -c 0 ./ordenamiento_clase < $INPUT_FILE ; } > temp1.txt &
    { taskset -c 1 ./ordenamiento2 < $INPUT_FILE ; } > temp2.txt &
    { taskset -c 2 ./ordenamiento3 < $INPUT_FILE ; } > temp3.txt &

    # Espera a que todos los procesos en segundo plano finalicen
    wait

    # Lee los tiempos de los archivos temporales
    TIEMPO1=$(cat temp1.txt)
    TIEMPO2=$(cat temp2.txt)
    TIEMPO3=$(cat temp3.txt)

    echo "Ejecucion $i terminada."
    
    # Guarda el número de ejecución y el tiempo en el archivo CSV
    echo "$i,$TIEMPO1,$TIEMPO2,$TIEMPO3" >> $OUTPUT_CSV
    echo "Ejecucion $i guardada."

    #Limpia los archivos temporales (opcional)
    rm temp*.txt
done

echo "Ejecuciones completadas. Los tiempos se han guardado en $OUTPUT_CSV."