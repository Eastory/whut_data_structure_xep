#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include"Compress.h"
#include"deCompress.h"

int main() {
	
	printf("==========������ѹ��==========\n������Ҫѹ�����ļ�����");
	char filename1[256];
	scanf("%s", filename1);
	Compress(filename1);

	char filename2[256];
	printf("==========��������ѹ==========\n������Ҫ��ѹ���ļ�����");
	scanf("%s", filename2);
	deCompress(filename2);
	return 0;
}