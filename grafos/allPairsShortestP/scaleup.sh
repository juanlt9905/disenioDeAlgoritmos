#!/bin/bash

#Archivo fuente
PROGRAMA_C="../allPairsShortestPath2.c"
# Nombre que le daremos al programa compilado (el ejecutable)
EJECUTABLE="../allPairsShortestPath2"
# Nombre del archivo de salida para los resultados
ARCHIVO_CSV="resultados_allPairsShortestPath2.csv"
# El nombre de tu script que genera los grafos
GENERADOR_GRAFOS="generar_grafos.sh" 


echo "Compilando el programa en C ($PROGRAMA_C)..."
gcc "$PROGRAMA_C" -o "$EJECUTABLE"
# Verificar si la compilación fue exitosa
if [ $? -ne 0 ]; then
  echo "Error: La compilación falló. Revisa el código en C."
  exit 1
fi
echo "Compilación exitosa. Ejecutable creado: $EJECUTABLE"
echo ""

# --- PREPARAR EL ARCHIVO DE RESULTADOS CSV ---
echo "Nodos,Aristas,Tiempo_Segundos" > "$ARCHIVO_CSV"


# Itera para los tamaños de nodos que especificaste
for nodos in 100 200 300 400 500
do
  # Define el nombre del archivo que se espera encontrar
  archivo_grafo="../grafo_scaleup_${nodos}.txt"

  echo "========================================================"
  echo " PRUEBA DE SCALE-UP: ${nodos} Nodos"
  echo "========================================================"
  
  # CAMBIO: Verificar si el archivo de entrada existe
  if [ -f "$archivo_grafo" ]; then
    # Si el archivo existe, procede con la prueba
    echo "Archivo encontrado: $archivo_grafo. Procesando..."
    
    aristas=$(head -n 2 "$archivo_grafo" | tail -n 1)

    for i in $(seq 1 15)
    do
      echo "  -> Ejecución $i de 15..."

      # Ejecuta el programa en C y captura su salida (el tiempo)
      tiempo_ejecucion=$(./"$EJECUTABLE" "$archivo_grafo")

      # Escribe la nueva línea de resultados en el CSV, sin el número de repetición
      echo "${nodos},${aristas},${tiempo_ejecucion}" >> "$ARCHIVO_CSV"

      echo "  Prueba $i finalizada. Tiempo registrado: ${tiempo_ejecucion}s"

    done # <-- Fin del bucle de 15 repeticiones
  
  else
    # Si el archivo no existe, muestra una advertencia y continua con el siguiente
    echo "Advertencia: No se encontró el archivo '$archivo_grafo'. Saltando esta prueba."
  fi
  
  echo "" #
done

echo "========================================================"
echo "Todas las pruebas han finalizado"
echo " resultados en archivo ${ARCHIVO_CSV}"