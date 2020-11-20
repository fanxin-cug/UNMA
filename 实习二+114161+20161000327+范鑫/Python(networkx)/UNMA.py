import networkx as nx
import numpy as np

G=nx.DiGraph()

v=np.loadtxt('node.txt',dtype=int)
v_num=v.shape[0]

for i in range(v_num):
    G.add_node(v[i][0],X=v[i][1],Y=v[i][2])

e=np.loadtxt('edge.txt',dtype=int)
e_num=e.shape[0]

data=[]
for i in range(e_num):
    temp=(e[i][0],e[i][1],e[i][2])
    data.append(temp)
G.add_weighted_edges_from(data)

print(nx.dijkstra_path(G,101,1))
print(nx.dijkstra_path_length(G, 101, 1))
