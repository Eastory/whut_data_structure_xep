#include<iostream>
using namespace std;
#include"Graph.h"
#pragma warning(disable : 4996)
Vex vex[10];
Edge edge[10];
CGraph m_Graph;
int n, x;
void CreateGraph() {
	//cout << "请输入景点文件路径：";
	FILE* in1 = fopen("F:/Vex.txt", "r");
	if (in1 == NULL)
		printf("读取vex失败\n");
	
	if (fscanf(in1, "%d", &n) == NULL)
		printf("读取顶点个数失败\n");
	else
		//cout << "顶点个数：" << n << endl;
	 
	for (int i = 0; i < n; i++) {
		fscanf(in1, "%d", &vex[i].num);
		//cout << vex[i].num << endl;
		fscanf(in1, "%s", vex[i].name);
		//cout << vex[i].name << endl;
		fscanf(in1, "%s", vex[i].des);
		//cout << vex[i].des << endl;
	}

	FILE* in2 = fopen("F:/Edge.txt", "r");
	if (in2 == NULL) printf("读取edge失败\n");

	while (fscanf(in2, "%d %d %d", &edge[x].vex1, &edge[x].vex2, &edge[x].weight) != EOF) {
		//cout << edge[x].vex1 << "\t" << edge[x].vex2 << "\t" << edge[x].weight << "\t" << endl;
		x++;
	}
	//cout << "道路数量：" << x << endl;

	m_Graph.init();
	for (int i = 0; i < n; i++) {
		m_Graph.InsertVex(vex[i]);
	}
	for (int i = 0; i < x; i++) {
		m_Graph.InsertEdge(edge[i]);
	}
	
	//m_Graph.testvexs();
	//m_Graph.testA();
	
	cout << "======创建景区景点图=====" << endl;
	cout << "-----景点-----" << endl;
	cout << "顶点数量：" << n << endl;
	for (int i = 0; i < n; i++) {
		cout << vex[i].num << "-" << vex[i].name << endl;
	}
	cout << "-----道路-----" << endl;
	cout << "道路数量：" << x << endl;
	for (int i = 0; i < x; i++) {
		printf("<v%d,v%d> %d\n", edge[i].vex1, edge[i].vex2, edge[i].weight);
	}
}
void GetSpotInfo() {
	cout << "======查询景点信息=====" << endl;
	for (int i = 0; i < n; i++) {
		cout << m_Graph.GetVex(i).num << "-" << m_Graph.GetVex(i).name << endl;
	}
	cout << "请输入想要查询的景点编号：";
	int a;
	cin >> a;
	if (a >= n) {
		cout << "该景点不存在" << endl;
		return;
	}
	cout << m_Graph.GetVex(a).name << endl << m_Graph.GetVex(a).des << endl;
	cout << "-----周边美景-----" << endl;
	Edge path[10];
	int roadnum = m_Graph.FindEdge(a, path);
	for (int i = 0; i < roadnum; i++) {
		printf("%s->%s  %dm\n", m_Graph.GetVex(path[i].vex1).name, m_Graph.GetVex(path[i].vex2).name, path[i].weight);
	}
}
void TravelPath() {
	cout << "======旅游景点导航=====" << endl;
	cout << "输入起始点编号：" << endl;
	int start;
	cin >> start;
	if (start >= 7) {
		cout << "该景点不存在" << endl;
		return;
	}

	int road[20][7];//存多条路线
	int roadnum = 0;//路线数量
	
	bool bevisited[7] = { false };
	int index = 0;

	m_Graph.DFS(start, bevisited, index, road, roadnum);

	cout << "导游路线为：" << endl;
	for (int i = 0; i < roadnum; i++) {
		cout << m_Graph.GetVex(start).name;
		for (int j = 1; j < n; j++) {
			cout << "->" << m_Graph.GetVex(road[i][j]).name;
		}
		cout << endl;
	}
	
	return;
}
void DesignPath() {
	cout << "=====铺设电路规划=====" << endl;
	Edge path[7];
	int totol;
	cout << "在以下两个景点之间铺设道路：" << endl;
	totol = m_Graph.FindMinTree(path);
	for (int i = 1; i < n; i++) {//六条路
		printf("%s %s   %dm\n", m_Graph.GetVex(path[i].vex1).name, m_Graph.GetVex(path[i].vex2).name, path[i].weight);
	}
	cout << "铺设电路总长度为：" << totol << endl;
}
void FindShortPath() {
	cout << "======搜索最短路径=====" << endl;
	for (int i = 0; i < n; i++) {
		cout << m_Graph.GetVex(i).num << "-" << m_Graph.GetVex(i).name << endl;
	}
	int start, end;
	cout << "请输入起点的编号：";
	cin >> start;
	if (start < 0 || start >n) {
		cout << "起始景点不存在";
		return;
	}
	cout << "请输入终点的编号：";
	cin >> end;
	if (end < 0 || end >n) {
		cout << "终点不存在";
		return;
	}
	int path[10];
	int mintotalweight = m_Graph.FindShortPath(start, end, path);
	int out[10];
	int num = 0;
	int index = end;
	for (int i = 0; i < n; i++) {
		if (path[index] == -1)
			break;
		else {
			out[i] = path[index];
			index = path[index];
			num++;
		}
	}
	cout << "最短路线为：";
	for (int i = num - 1; i >= 0; i--)
		cout << m_Graph.GetVex(out[i]).name << "->";
	cout << m_Graph.GetVex(end).name << endl;
	cout << "最短距离为：" << mintotalweight << endl;
}