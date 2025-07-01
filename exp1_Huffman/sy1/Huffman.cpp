#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include"Huffman.h"

void TestWeight(int weight[]) {
    printf("原文件字符的权值：\n");
    printf("Byte    Weight\n");
    for (int i = 0; i < 256; i++)
        printf("0x%02X  %d\n", i, weight[i]);
}

void CreatHuffmanTree(HuffmanTree& HT, int *w) {
    int i;
    for (int i = 0; i < 511; i++) {
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].weight = (i < 256) ? w[i] : 0; // 初始化叶子节点的权重
    }

    for (i = 256; i < 511; i++) {
        int s1, s2;
        Select(HT, i, s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}

void Select(HuffmanTree HT, int x, int& s1, int& s2) {
    double min1 = 99999999, min2 = 99999999;
    s1 = s2 = -1;
    int j;
    for (j = 0; j < x; j++) {
        if (HT[j].weight < min1 && HT[j].parent == 0) {
            min1 = HT[j].weight;
            s1 = j;
        }
    }
    int k;
    for (k = 0; k < x; k++) {
        if (HT[k].weight < min2 && HT[k].parent == 0 && k != s1) {
            min2 = HT[k].weight;
            s2 = k;
        }
    }
}

void TestHuffTree(HuffmanTree HT) {
    printf("Byte    weight  Parent  Lchild  Rchild\n");
    for (int i = 0; i < 511; i++)
    {
        printf("pHT[%d]\t%d\t%d\t%d\t%d\n", i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);

    }
}

void CreatHuffmanCode(HuffmanTree HT, char codes[][256]) {
    char code[256];//临时存放编码
    code[255] = '\0';//便于 strcpy 复制
    int nowchild, nowparent;
    int len;
    for (int i = 0; i < 256; i++) {
        nowchild = i;
        nowparent = HT[i].parent;
        len = 255;
        while (nowparent != 0) {
            if (HT[nowparent].lchild == nowchild)
                code[--len] = '0';
            else
                code[--len] = '1';

            nowchild = nowparent;
            nowparent = HT[nowchild].parent;
        }
        strcpy(codes[i], &code[len]);
    }
    
}

void Codetest(char codes[][256]) {
    printf("结点           编码\n");
    for(int i = 0; i < 256; i++)
        printf("pHT[%d]\t%s\n", i, codes[i]);
}