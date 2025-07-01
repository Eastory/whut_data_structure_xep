#include<iostream>
using namespace std;
#include"Tourism.h"
#include"Graph.h"

int main() {
	int n;
	int t = 1;
	while (t) {
		cout << "=====景区信息管理系统=====" << endl;
		cout << "1.创建景区景点图" << endl;
		cout << "2.查询景点信息" << endl;
		cout << "3.旅游景点导航" << endl;
		cout << "4.搜索最短路径" << endl;
		cout << "5.铺设电路规划" << endl;
		cout << "0.退出" << endl;

		
		cout << "请输入操作编号(0~5):";
		cin >> n;

		switch (n) {
		case 1:
			CreateGraph();
			break;
		case 2:
			GetSpotInfo();
			break;
		case 3:
			TravelPath();
			break;
		case 4:
			FindShortPath();
			break;
		case 5:
			DesignPath();
			break;
		case 0:
			cout << "退出程序" << endl;
			t = 0;
		}
		
	}
	
}