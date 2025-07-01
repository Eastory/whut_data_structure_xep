struct Vex
{
	int num;//±àºÅ
	char name[20];
	char des[1024];
};
struct Edge
{
	int vex1;
	int vex2;
	int weight;
};
class CGraph
{
private:
	int A[20][20];
	Vex vexs[20];
	int vexnum;
public:
	void init();
	bool InsertVex(Vex v);
	bool InsertEdge(Edge e);
	void testvexs();
	void testA();
	Vex GetVex(int v);
	int FindEdge(int v, Edge aedge[]);
	void DFS(int nVex, bool bVisited[], int& nIndex, int road[][7], int& roadnum);
	int FindShortPath(int nVexStart, int nVexEnd, int Path[]);
	int FindMinTree(Edge Prth[]);
	
};
