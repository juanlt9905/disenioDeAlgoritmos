import networkx as nx
import sys

#python3 /home/juan/disenioDeAlgoritmos/grafos/minimunST/validacion.py <archivo>

# --- Script para calcular el peso del MST correcto ---

def calcular_peso_mst_correcto(nombre_archivo):
    """
    Lee un archivo de grafo en dot, calcula el peso total del MST
    """
    try:
        with open(nombre_archivo, 'r') as f:
            # Leer número de nodos y aristas (aunque no los usaremos directamente)
            num_nodos = int(f.readline())
            num_aristas = int(f.readline())
            
            # Crear un grafo vacío
            G = nx.Graph()
            
            # Leer cada arista y añadirla al grafo con su peso
            for linea in f:
                partes = linea.strip().split()
                if len(partes) == 3:
                    u, v, peso = int(partes[0]), int(partes[1]), int(partes[2])
                    G.add_edge(u, v, weight=peso)
            
            print(f"Archivo '{nombre_archivo}' leído. Nodos: {G.number_of_nodes()}, Aristas: {G.number_of_edges()}")
            
            # NetworkX calcula el MST con un algoritmo bien probado (basado en Kruskal)
            mst = nx.minimum_spanning_tree(G)
            
            # Calculamos el peso total del MST
            peso_total = mst.size(weight='weight')
            
            print("--------------------------------------------------")
            print(f"VERIFICACIÓN: El peso total del MST correcto es: {peso_total}")
            print("--------------------------------------------------")

    except FileNotFoundError:
        print(f"Error: No se pudo encontrar el archivo '{nombre_archivo}'")
    except Exception as e:
        print(f"Ocurrió un error: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f"Uso: python3 {sys.argv[0]} <nombre_del_archivo.txt>")
    else:
        calcular_peso_mst_correcto(sys.argv[1])