import networkx as nx
import matplotlib.pyplot as plt

'''
秃鹫(A)；雄狮(B)；飞鹰(C)；海狸(D)；猛虎(E)；山猫(F)。
每个队每周只赛一场；
其中A-B,A-C；B-D,B-F已赛，
要求每个队与其他队互赛一场且时间最短。
'''

n=6
m=15

G=nx.Graph()
G.add_node(1,S='A')
G.add_node(2,S='B')
G.add_node(3,S='C')
G.add_node(4,S='D')
G.add_node(5,S='E')
G.add_node(6,S='F')
G.add_edges_from([(1,2,{'hadVS':1,'color':0}),(1,3,{'hadVS':1,'color':0}),(1,4,{'hadVS':0,'color':0}),(1,5,{'hadVS':0,'color':0}),(1,6,{'hadVS':0,'color':0}),
                  (2,3,{'hadVS':0,'color':0}),(2,4,{'hadVS':1,'color':0}),(2,5,{'hadVS':0,'color':0}),(2,6,{'hadVS':1,'color':0}),
                  (3,4,{'hadVS':0,'color':0}),(3,5,{'hadVS':0,'color':0}),(3,6,{'hadVS':0,'color':0}),
                  (4,5,{'hadVS':0,'color':0}),(4,6,{'hadVS':0,'color':0}),
                  (5,6,{'hadVS':0,'color':0})])

cnt=0#周数
tag=[]#本周该队是否已赛标志
for i in range(n):
    tag.append(0)
num=0#还需比赛场数
for (u,v,d) in G.edges(data='hadVS'):
    if d==0:
        num+=1

while num:
    for i in range(n-1):
        for j in range(i+1,n):
            if not tag[i] and not tag[j] and j+1 in G.neighbors(i+1) and G[i+1][j+1]['hadVS']==0:
                G[i+1][j+1]['hadVS']=1
                G[i + 1][j + 1]['color'] = cnt+1
                tag[i]=1
                tag[j]=1
                num -= 1
    for k in range(n):
        tag[k]=0
    cnt+=1

colors=[]
for (u,v,d) in G.edges(data='color'):
    colors.append(d)

print("比赛需进行%d周!"%cnt)
nx.draw(G,with_labels=True,edge_color=colors,width=3)
plt.savefig("result.png")
plt.show()
