#pragma once
typedef struct
{
	int weight;
	int parent;
	int lchild;
	int rchild;
}HTNode, *HuffmanTree;

void TestWeight(int weight[]);

void CreatHuffmanTree(HuffmanTree& HT, int *weight);//构造哈夫曼树

void Select(HuffmanTree HT, int i, int& s1, int& s2);//用于选取两个值最小

void TestHuffTree(HuffmanTree HT);

void CreatHuffmanCode(HuffmanTree HT, char codes[][256]);//哈夫曼编码

void Codetest(char codes[][256]);