// UNMA3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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

//Dijkstra的堆优化
int dist[n];//dist[j], 0≤j<n, 是当前求到的从顶点v到顶点j的最短路径长度,
bool S[n];//最短路径顶点集
int edgeNum[n];
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
vector<int> vec;//存储在范围内的点
int start, range;//搜索范围起点与搜索范围
void dijkstra_queue(int v) {
	for (int i = 0; i < n; i++) {
		dist[i] = maxValue;
		S[i] = false;
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
		if (u!=v && dist[u] < range) {//如果在范围内，则加入容器
			vec.push_back(u + 1);
		}
		for (int i = 0; i < edgeNum[u]; i++) {
			int b = G[u][i].to;
			int w = G[u][i].w;
			if (!S[b] && dist[b] > dist[u] + w) {
				dist[b] = dist[u] + w;
				q.push(qnode(b, dist[b]));
			}
		}
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
	cout << "请输入搜索范围起点：";
	cin >> start;
	cout << "请输入搜索范围：";
	cin >> range;
	dijkstra_queue(start - 1);
	cout << "该范围内的点为：";
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}
	cout << endl;
	//cout << vec.size() << endl;
	/*int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (i!=start-1 && dist[i] < range) {
			cout << i + 1 << " ";
			cnt++;
		}
	}
	cout << endl;
	cout << cnt << endl;*/
	return 0;
}