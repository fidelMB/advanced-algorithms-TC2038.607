import random
import sys

# Función para generar puntos aleatorios
def generar_puntos_aleatorios(n, rango):
    puntos = []
    for _ in range(n):
        x = random.uniform(rango[0], rango[1])
        y = random.uniform(rango[0], rango[1])
        puntos.append((x, y))
    return puntos

# Función para guardar puntos en un archivo
def guardar_puntos_en_txt(puntos, nombre_archivo):
    with open(nombre_archivo, 'w') as archivo:
        for punto in puntos:
            archivo.write(f"{punto[0]},{punto[1]}\n")

# Parámetros
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Error! python generator.py numero_puntos")
        exit(-1)
    numero_de_puntos = int(sys.argv[1])  # Número de puntos a generar
    rango = (0, 10)  # Rango para las coordenadas (x, y)
    nombre_archivo = "puntos_aleatorios.txt"

    # Generar y guardar puntos
    puntos = generar_puntos_aleatorios(numero_de_puntos, rango)
    guardar_puntos_en_txt(puntos, nombre_archivo)
    print(f"{numero_de_puntos} puntos aleatorios generados y guardados en {nombre_archivo}.")
