#include<iostream>
using namespace std;
#include"Tourism.h"
#include"Graph.h"

int main() {
	int n;
	int t = 1;
	while (t) {
		cout << "=====������Ϣ����ϵͳ=====" << endl;
		cout << "1.������������ͼ" << endl;
		cout << "2.��ѯ������Ϣ" << endl;
		cout << "3.���ξ��㵼��" << endl;
		cout << "4.�������·��" << endl;
		cout << "5.�����·�滮" << endl;
		cout << "0.�˳�" << endl;

		
		cout << "������������(0~5):";
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
			cout << "�˳�����" << endl;
			t = 0;
		}
		
	}
	
}