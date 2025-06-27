#!/bin/bash

NUM_NODOS=500
NUM_ARISTAS=24950
NOMBRE_ARCHIVO="grafo_scaleup_500.txt"

echo "$NUM_NODOS" > "$NOMBRE_ARCHIVO"
echo "$NUM_ARISTAS" >> "$NOMBRE_ARCHIVO"

# Array para almacenar aristas ya generadas
declare -A aristas_generadas

contador=0
while [ $contador -lt $NUM_ARISTAS ]
do
  u=$(($RANDOM % $NUM_NODOS))
  v=$(($RANDOM % $NUM_NODOS))
  
  # Evitar lazos
  while [ "$u" -eq "$v" ]
  do
    v=$(($RANDOM % $NUM_NODOS))
  done
  
  # Crear clave única para la arista (menor primero para evitar duplicados)
  if [ $u -lt $v ]; then
    clave="${u}_${v}"
  else
    clave="${v}_${u}"
  fi
  
  # Verificar si la arista ya existe
  if [ -z "${aristas_generadas[$clave]}" ]; then
    aristas_generadas[$clave]=1
    echo "$u $v" >> "$NOMBRE_ARCHIVO"
    contador=$((contador + 1))
  fi
done

echo "Grafo guardado en $NOMBRE_ARCHIVO"