#include<iostream>
using namespace std;
#include"Graph.h"
#pragma warning(disable : 4996)
Vex vex[10];
Edge edge[10];
CGraph m_Graph;
int n, x;
void CreateGraph() {
	//cout << "�����뾰���ļ�·����";
	FILE* in1 = fopen("F:/Vex.txt", "r");
	if (in1 == NULL)
		printf("��ȡvexʧ��\n");
	
	if (fscanf(in1, "%d", &n) == NULL)
		printf("��ȡ�������ʧ��\n");
	else
		//cout << "���������" << n << endl;
	 
	for (int i = 0; i < n; i++) {
		fscanf(in1, "%d", &vex[i].num);
		//cout << vex[i].num << endl;
		fscanf(in1, "%s", vex[i].name);
		//cout << vex[i].name << endl;
		fscanf(in1, "%s", vex[i].des);
		//cout << vex[i].des << endl;
	}

	FILE* in2 = fopen("F:/Edge.txt", "r");
	if (in2 == NULL) printf("��ȡedgeʧ��\n");

	while (fscanf(in2, "%d %d %d", &edge[x].vex1, &edge[x].vex2, &edge[x].weight) != EOF) {
		//cout << edge[x].vex1 << "\t" << edge[x].vex2 << "\t" << edge[x].weight << "\t" << endl;
		x++;
	}
	//cout << "��·������" << x << endl;

	m_Graph.init();
	for (int i = 0; i < n; i++) {
		m_Graph.InsertVex(vex[i]);
	}
	for (int i = 0; i < x; i++) {
		m_Graph.InsertEdge(edge[i]);
	}
	
	//m_Graph.testvexs();
	//m_Graph.testA();
	
	cout << "======������������ͼ=====" << endl;
	cout << "-----����-----" << endl;
	cout << "����������" << n << endl;
	for (int i = 0; i < n; i++) {
		cout << vex[i].num << "-" << vex[i].name << endl;
	}
	cout << "-----��·-----" << endl;
	cout << "��·������" << x << endl;
	for (int i = 0; i < x; i++) {
		printf("<v%d,v%d> %d\n", edge[i].vex1, edge[i].vex2, edge[i].weight);
	}
}
void GetSpotInfo() {
	cout << "======��ѯ������Ϣ=====" << endl;
	for (int i = 0; i < n; i++) {
		cout << m_Graph.GetVex(i).num << "-" << m_Graph.GetVex(i).name << endl;
	}
	cout << "��������Ҫ��ѯ�ľ����ţ�";
	int a;
	cin >> a;
	if (a >= n) {
		cout << "�þ��㲻����" << endl;
		return;
	}
	cout << m_Graph.GetVex(a).name << endl << m_Graph.GetVex(a).des << endl;
	cout << "-----�ܱ�����-----" << endl;
	Edge path[10];
	int roadnum = m_Graph.FindEdge(a, path);
	for (int i = 0; i < roadnum; i++) {
		printf("%s->%s  %dm\n", m_Graph.GetVex(path[i].vex1).name, m_Graph.GetVex(path[i].vex2).name, path[i].weight);
	}
}
void TravelPath() {
	cout << "======���ξ��㵼��=====" << endl;
	cout << "������ʼ���ţ�" << endl;
	int start;
	cin >> start;
	if (start >= 7) {
		cout << "�þ��㲻����" << endl;
		return;
	}

	int road[20][7];//�����·��
	int roadnum = 0;//·������
	
	bool bevisited[7] = { false };
	int index = 0;

	m_Graph.DFS(start, bevisited, index, road, roadnum);

	cout << "����·��Ϊ��" << endl;
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
	cout << "=====�����·�滮=====" << endl;
	Edge path[7];
	int totol;
	cout << "��������������֮�������·��" << endl;
	totol = m_Graph.FindMinTree(path);
	for (int i = 1; i < n; i++) {//����·
		printf("%s %s   %dm\n", m_Graph.GetVex(path[i].vex1).name, m_Graph.GetVex(path[i].vex2).name, path[i].weight);
	}
	cout << "�����·�ܳ���Ϊ��" << totol << endl;
}
void FindShortPath() {
	cout << "======�������·��=====" << endl;
	for (int i = 0; i < n; i++) {
		cout << m_Graph.GetVex(i).num << "-" << m_Graph.GetVex(i).name << endl;
	}
	int start, end;
	cout << "���������ı�ţ�";
	cin >> start;
	if (start < 0 || start >n) {
		cout << "��ʼ���㲻����";
		return;
	}
	cout << "�������յ�ı�ţ�";
	cin >> end;
	if (end < 0 || end >n) {
		cout << "�յ㲻����";
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
	cout << "���·��Ϊ��";
	for (int i = num - 1; i >= 0; i--)
		cout << m_Graph.GetVex(out[i]).name << "->";
	cout << m_Graph.GetVex(end).name << endl;
	cout << "��̾���Ϊ��" << mintotalweight << endl;
}