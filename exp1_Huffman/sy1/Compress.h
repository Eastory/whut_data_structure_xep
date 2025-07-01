#pragma once
void Compress(const char* pFilename);
char Str2byte(const char* pBinStr);
int Encode(const char* pFilename, char codes[][256], char* pBuffer);

typedef struct
{
	char type[4];//文件类型
	int length;//原文件长度
	int weight[256];//权值数值
}HEAD;

int InitHead(const char* pFilename, HEAD& sHead, int len, int* xweight);
int WriteFile(const char* pFilename, const HEAD sHead, const char* pBuffer, const int nSize);
void TestHead(HEAD sHead);


