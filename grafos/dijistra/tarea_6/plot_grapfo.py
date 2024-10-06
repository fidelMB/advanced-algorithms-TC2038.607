import matplotlib.pyplot as plt
import networkx as nx

# Crear un grafo
G = nx.DiGraph()

# Añadir nodos y aristas
G.add_edges_from([(1, 0, {'weight': 4}), 
                  (4, 2, {'weight': 7}), 
                  (4, 3, {'weight': 10}),
                  (1, 4, {'weight': 8}),
                  (4, 5, {'weight': 8})])

color_map = []

for node in G:
    if node == 1:
        color_map.append('red')
    else:
        color_map.append('blue')

# Dibujar el grafo
pos = nx.spring_layout(G)  # Posicionamiento de los nodos
nx.draw(G, pos, with_labels=True, node_color = color_map)
labels = nx.get_edge_attributes(G, 'weight')
nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)
plt.show()

