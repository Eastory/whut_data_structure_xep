#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include"Graph.h"
#include"Tourism.h"
void CGraph::init() {
	vexnum = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			A[i][j] = 0;
		}
	}
}
bool CGraph::InsertVex(Vex v) {
	if (vexnum + 1 == 20) {
		cout << "添加失败，顶点过多" << endl;
		return false;
	}
	vexs[vexnum++] = v;
	return true;
}
bool CGraph::InsertEdge(Edge e) {
	if (e.vex1 < 0 || e.vex1 >= 20 || e.vex2 < 0 || e.vex2 >= 20) {
		cout << "添加失败，信息错误" << endl;
		return false;
	}
	A[e.vex1][e.vex2] = e.weight;
	A[e.vex2][e.vex1] = e.weight;
	return true;
}
void CGraph::testvexs() {
	for (int i = 0; i < vexnum; i++)
		cout << vexs[i].num << endl << vexs[i].name << endl << vexs[i].des << endl;

}
void CGraph::testA() {
	for (int i = 0; i < vexnum; i++) {
		for (int j = 0; j < vexnum; j++) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
}
Vex CGraph::GetVex(int v) {
	if (v < 0 || v >= vexnum)
		cout << "无该编号景点" << endl;
	for (int i = 0; i < vexnum; i++) {
		if (vexs[i].num == v)
			return vexs[i];
	}
}
int CGraph::FindEdge(int v, Edge aedge[]) {
	int k = 0;
	for (int i = 0; i < vexnum; i++) {
		if (A[v][i] != 0) {
			aedge[k].vex1 = v;
			aedge[k].vex2 = i;
			aedge[k].weight = A[v][i];
			k++;
		}
	}
	return k;
}
void CGraph::DFS(int nVex, bool bVisited[], int& nIndex, int road[][7], int &roadnum) {
	bVisited[nVex] = true;
	road[roadnum][nIndex++] = nVex;
	if (nIndex == vexnum) {
		roadnum++;
		for (int i = 0; i < vexnum; i++)
			road[roadnum][i] = road[roadnum - 1][i];
	}
	else {
		for (int i = 0; i < vexnum; i++) {
			if (A[nVex][i] != 0 && !bVisited[i]) {
				DFS(i, bVisited, nIndex, road, roadnum);//递归
				bVisited[i] = false;//回溯
				nIndex--;
			}
		}
	}
}
int CGraph::FindMinTree(Edge Prth[]) {//Prim
	int lowcost[7];//每个点距离当前树的最小权值，0为已入树
	int parent[7];//每个点与哪个点铺路
	int start = 0;//起始点0，A区
	int totol = 0;//总道路长度

	//初始化
	for (int i = 0; i < vexnum; i++) {
		if (A[start][i] != 0) {
			lowcost[i] = A[start][i];
			parent[i] = start;
		}
		else {
			lowcost[i] = 999999;
			parent[i] = -1;
		}
	}
	lowcost[start] = 0;

	//构建树
	for (int i = 1; i < vexnum; i++) {
		int index = -1;
		int minweight = 999999;

		//找当前权值最小的邻节点
		for (int j = 0; j < vexnum; j++) {
			if (lowcost[j] != 0 && lowcost[j] < minweight) {
				minweight = lowcost[j];
				index = j;
			}
		}
		lowcost[index] = 0;//index入树

		//记录道路信息
		Prth[i].vex1 = parent[index];
		Prth[i].vex2 = index;
		Prth[i].weight = minweight;
		//printf("%s %s    %dm\n", GetVex(parent[index]).name, GetVex(index).name, minweight);
		totol += minweight;

		//更新lowcost和parent
		for (int j = 0; j < vexnum; j++) {
			if (lowcost[j] != 0 && lowcost[j] > A[index][j] && A[index][j] != 0) {
				lowcost[j] = A[index][j];
				parent[j] = index;
			}
		}
	}
	return totol;
}
int CGraph::FindShortPath(int nVexStart, int nVexEnd, int Path[]) {
	bool visit[7] = { false };//是否已找到最短路径
	int dist[7];//最短路径长度
	//int path[7];//路径上的前驱

	//初始化
	visit[nVexStart] = true;
	for (int i = 0; i < vexnum; i++) {
		if (A[nVexStart][i] != 0) {
			dist[i] = A[nVexStart][i];
			Path[i] = nVexStart;
		}
		else {
			dist[i] = 99999;
			Path[i] = -1;
		}
	}
	dist[nVexStart] = 0;

	for (int i = 0; i < vexnum - 1; i++) {
		int mindist = 99999;
		int index = -1;
		for (int j = 0; j < vexnum; j++) {
			if (!visit[j] && mindist > dist[j]) {
				mindist = dist[j];
				index = j;
			}
		}
		visit[index] = true;

		//更新dist
		for (int j = 0; j < vexnum; j++) {
			if (!visit[j] && A[index][j] + dist[index] < dist[j] && A[index][j] != 0) {
				dist[j] = A[index][j] + dist[index];
				Path[j] = index;
			}
		}

	}
	//for (int i = 0; i < vexnum; i++)
		//cout << Path[i] << " ";
	return dist[nVexEnd];
}