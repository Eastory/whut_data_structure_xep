#pragma once
typedef struct
{
	int weight;
	int parent;
	int lchild;
	int rchild;
}HTNode, *HuffmanTree;

void TestWeight(int weight[]);

void CreatHuffmanTree(HuffmanTree& HT, int *weight);//�����������

void Select(HuffmanTree HT, int i, int& s1, int& s2);//����ѡȡ����ֵ��С

void TestHuffTree(HuffmanTree HT);

void CreatHuffmanCode(HuffmanTree HT, char codes[][256]);//����������

void Codetest(char codes[][256]);