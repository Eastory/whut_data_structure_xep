#include"huffman.h"
#include"Compress.h"
#include"deCompress.h"
#include<iostream>
using namespace std;
#include<stdlib.h>
#pragma warning(disable : 4996)
void Compress(const char* filename) {

	FILE* in = fopen(filename, "rb");
	int ch;
	int len1 = 0;
	int xweight[256] = { 0 };
	while ((ch = getc(in)) != EOF) {
		xweight[ch]++;
		//获取原文件每个字符的权值
		len1++;
	}
	//printf("%d\n", len1);
	fclose(in);
	//TestWeight(xweight);

	HuffmanTree HT = new HTNode[511];
	CreatHuffmanTree(HT, xweight);
	//TestHuffTree(HT);

	char codes[256][256];
	CreatHuffmanCode(HT, codes);
	//Codetest(codes);

	int nSize = 0;
	for (int i = 0; i < 256; i++) {
		nSize += xweight[i] * strlen(codes[i]);
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;
	//printf("nSize = %d", nSize);

	char* pBuffer = (char*)malloc(nSize * sizeof(char));//临时动态字符数组存储编码
	for (int i = 0; i < nSize; i++)
		pBuffer[i] = 0;

	Encode(filename, codes, pBuffer);

	HEAD head;
	InitHead(filename, head, len1, xweight);
	//TestHead(head1);

	int len2;
	len2 = WriteFile(filename, head, pBuffer, nSize);
	if (len2 == -1) {
		printf("压缩失败");
		return;
	}
	printf("压缩前文件：%d字节\n", len1);
	printf("压缩后文件：%d字节\n", len2);
	printf("压缩比率：%f%%\n", (double)len2 / len1 * 100);

	return;
}

char Str2byte(const char* pBinStr)
{
	char b = 0x00;
	for (int i = 0; i < 8; i++){
		b = b << 1;// 左移1位 
		if (pBinStr[i] == '1') {
			b = b | 0x01;
		}
	}
	return b;
}
int Encode(const char* pFilename, char codes[][256], char* pBuffer) {

	FILE* in = fopen(pFilename, "rb");
	int ch;
	int x = 0;
	char code[256] = { 0 };
	while ((ch = fgetc(in)) != EOF) {
		strcat(code, codes[ch]);

		//printf("%s", codes[ch]);

		while (strlen(code) >= 8) {
			pBuffer[x++] = Str2byte(code);

			for (int i = 0; i < 256 - 8; i++) 
				code[i] = code[i + 8];
		}
	}
	//printf("\n");
	if (strlen(code) > 0)
		pBuffer[x++] = Str2byte(code);
	
	fclose(in);
	return 0;
}

int InitHead(const char* pFilename, HEAD& sHead, int len, int *xweight) {
	strcpy(sHead.type, "HUF");
	sHead.length = len;
	for (int i = 0; i < 256; i++)
		sHead.weight[i] = xweight[i];
	return 0;
}


int WriteFile(const char* pFilename, const HEAD sHead, const char* pBuffer, const int nSize) {
	char filename[256];
	strcpy(filename, pFilename);
	strcat(filename, ".huf");
	//以二进制流形式打开文件
	FILE* out = fopen(filename, "wb");
	//写文件头
	if (fwrite(&sHead, sizeof(HEAD), 1, out) != 1) {
		printf("头文件写入失败，压缩失败\n");
		fclose(out);
		return - 1;
	}
	//写压缩后的编码
	if (fwrite(pBuffer, sizeof(char), nSize, out) != nSize) {
		printf("压缩数据写入失败，压缩失败\n");
		fclose(out);
		return -1;
	}
	
	fclose(out);
	printf("生成压缩文件：%s\n", filename);
	int len = sizeof(HEAD) + strlen(pFilename) + 1 + nSize;
	//cout << len << endl;
	return len;

}

void TestHead(HEAD sHead) {
	printf("文件类型\t\t原文件长度\n%s\t%d\n结点\t权值\n", sHead.type, sHead.length);
		for (int i = 0; i < 256; i++)
			printf("%d\t%d\n", i, sHead.weight[i]);
}