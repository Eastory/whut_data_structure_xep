#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include"Compress.h"
#include"deCompress.h"

int main() {
	
	printf("==========哈夫曼压缩==========\n请输入要压缩的文件路径：");
	char filename1[256];
	scanf("%s", filename1);
	Compress(filename1);

	char filename2[256];
	printf("==========哈夫曼解压==========\n请输入要解压的文件路径：");
	scanf("%s", filename2);
	deCompress(filename2);
	return 0;
}