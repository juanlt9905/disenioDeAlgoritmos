#!/bin/bash

#Archivo fuente
PROGRAMA_C="singleSourceShortestPath1.c"
# Nombre que le daremos al programa compilado (el ejecutable)
EJECUTABLE="singleSourceShortestPath1"
# Nombre del archivo de salida para los resultados
ARCHIVO_CSV="singleSourceScale/resultados_sigleSourceShortestPath1.csv"
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
  archivo_grafo="grafo_scaleup_${nodos}.txt"

  echo "========================================================"
  echo " PRUEBA DE SCALE-UP: ${nodos} Nodos"
  echo "========================================================"
  
  # CAMBIO: Verificar si el archivo de entrada existe
  if [ -f "$archivo_grafo" ]; then
    # Si el archivo existe, procede con la prueba
    echo "Archivo encontrado: $archivo_grafo. Procesando..."
    
    aristas=$(head -n 2 "$archivo_grafo" | tail -n 1)

    # Ejecuta el programa en C y captura su salida (el tiempo)
    tiempo_ejecucion=$(./"$EJECUTABLE" "$archivo_grafo")
    
    # Escribe la nueva línea de resultados en el archivo CSV
    echo "${nodos},${aristas},${tiempo_ejecucion}" >> "$ARCHIVO_CSV"
    
    echo "Prueba finalizada. Tiempo registrado: ${tiempo_ejecucion}s"
  
  else
    # Si el archivo no existe, muestra una advertencia y continua con el siguiente
    echo "Advertencia: No se encontró el archivo '$archivo_grafo'. Saltando esta prueba."
  fi
  
  echo "" # Línea en blanco para mejorar la legibilidad

done

echo "========================================================"
echo "Todas las pruebas han finalizado"
echo " resultados en archivo ${ARCHIVO_CSV}"