// Dijkstra.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

struct node {
	int to;
	int w;
};

const int n = 195233;
const int maxValue = INT_MAX;

vector<node> G[n];

//Dijkstra
int dist[n];//dist[j], 0≤j<n, 是当前求到的从顶点v到顶点j的最短路径长度,
int path[n];//path[j], 0≤j<n, 存放求到的最短路径。
bool S[n];//最短路径顶点集
int edgeNum[n];
/*
void ShortestPath(int v) {
	for (int i = 0; i < n; i++) {
		dist[i] = maxValue;
	}
	dist[v] = 0;//顶点v加入顶点集合
	for (int i = 0; i < edgeNum[v]; i++) {
		int b = G[v][i].to;
		int w = G[v][i].w;
		dist[b] = w;
	}
	for (int i = 0; i < n; i++) {
		S[i] = false;
		if (i != v && dist[i] < maxValue) path[i] = v;
		else path[i] = -1;
	}
	S[v] = true;  
	for (int i = 0; i < n - 1; i++) {//求解各顶点最短路径	
		int min = maxValue;
		int u = v;//选不在S中具有最短路径的顶点u
		for (int j = 0; j < n; j++) {
			if (!S[j] && dist[j] < min) {
				u = j;
				min = dist[j];
			}
		}
		S[u] = true;//将顶点u加入集合S
		for (int k = 0; k < edgeNum[u]; k++) {//修改	
			int b = G[u][k].to;
			int w = G[u][k].w;
			if (!S[b] && dist[b] > dist[u] + w) {//顶点k未加入S   	
				dist[b] = dist[u] + w;
				path[b] = u;//修改到k的最短路径
			}
		}
	}
}
*/
//Dijkstra的堆优化
struct qnode {
	int i;
	int dist;
	qnode(int i, int dist) {
		this->i = i;
		this->dist = dist;
	}
};
struct cmp {
	bool operator()(qnode q1, qnode q2) {
		return q1.dist > q2.dist;
	}
};
priority_queue<qnode, vector<qnode>, cmp> q;
void dijkstra_queue(int v) { 
	for (int i = 0; i < n; i++) {
		dist[i] = maxValue;
		S[i] = false;
		path[i] = -1;
	}
	dist[v] = 0;
	q.push(qnode(v, dist[v]));
	while (!q.empty()) {
		qnode p = q.top();
		q.pop();
		int u = p.i;
		int min = p.dist;
		if (S[u]) continue;
		S[u] = true;
		for (int i = 0; i < edgeNum[u]; i++) {
			int b = G[u][i].to;
			int w = G[u][i].w;
			if (!S[b] && dist[b] > dist[u] + w) {
				dist[b] = dist[u] + w;
				path[b] = u;
				q.push(qnode(b, dist[b]));
			}
		}
	}
}

int d[n];
void printSP(int v1, int v2) {
	cout << v1 + 1 << "到" << v2 + 1 << "的最短路径为：" << endl;
	int a = v2, b, c = 0;
	if (a != v1)
	{
		b = a;
		while (b != v1) { d[c++] = b; b = path[b]; }
		cout << v1 + 1 << "->";
		while (c > 0) {
			if (c == 1) {
				cout << d[--c] + 1 << endl;
			}
			else {
				cout << d[--c] + 1 << "->";
			}
		}
		cout << "最短路径长度为：" << dist[a] << endl;
	}
}

int main()
{
	cout << "Loading dada..." << endl;
	ifstream fin("data.txt");
	string line;
	string item;
	int a[3], i;
	node p;
	while (getline(fin, line)) {
		istringstream items(line);
		i = 0;
		while (items >> item) {
			stringstream ss;
			ss << item;
			ss >> a[i];
			i++;
		}
		edgeNum[a[0] - 1]++;
		p.to = a[1] - 1;
	    p.w = a[2];
		G[a[0] - 1].push_back(p);
	}
	cout << "Done!" << endl;
	int start, end;
	cout << "请输入起点：";
	cin >> start;
	cout << "请输入终点：";
	cin >> end;
	//ShortestPath(start - 1);
	dijkstra_queue(start - 1);
	/*ofstream fout("result.txt");
	fout << "start_id" << "," << "end_id" << "," << "dist"<<endl;
	for (int i = 0; i < 10000; i++) {
		fout << 103 << "," << i + 1 << "," << dist[i] << endl;
	}
	fout.close();*/
	printSP(start - 1, end - 1);
	return 0;
}