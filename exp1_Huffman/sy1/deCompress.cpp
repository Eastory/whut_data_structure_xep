#include"deCompress.h"
#include"Compress.h"
#include"Huffman.h"
#include <iostream>
using namespace std;
#include <string.h>
#pragma warning(disable : 4996)

void deCompress(const char* filename2) {
    HuffmanTree HT = new HTNode[511];
    HEAD head;
    if (!ReadHead(filename2, head))
        return;
    //TestHead(head);

    RebuildHuffmanTree(HT, head.weight);
    //TestHuffTree(HT);
    char filename3[256];
    printf("���������ɽ�ѹ�ļ�·������.bmpΪ��׺����");
    scanf("%s", filename3);
    Decode(filename2, filename3, HT, head.length);

}
bool ReadHead(const char* pfilename, HEAD& head) {

    FILE* in = fopen(pfilename, "rb");
    if (!in) {
        printf("���ļ�ʧ��");
        return false;
    }
    if (fread(head.type, sizeof(head.type), 1, in) != 1) {
        perror("���ļ�����ʧ��");
        fclose(in);
        return false;
    }
    if (fread(&head.length, sizeof(head.length), 1, in) != 1) {
        perror("���ļ�����ʧ��");
        fclose(in);
        return false;
    }
    if (fread(head.weight, sizeof(head.weight), 1, in) != 1) {
        perror("��Ȩֵʧ��");
        fclose(in);
        return false;
    }
    
	fclose(in);
    printf("��ȡͷ�ļ��ɹ�\n");
	return true;
}
void RebuildHuffmanTree(HuffmanTree& HT, int weight[]) {
    printf("�ؽ���������\n");
    CreatHuffmanTree(HT, weight);
}
 
void Decode(const char* inputFileName, const char* outputFileName, HuffmanTree HT, int length) {
    FILE* in = fopen(inputFileName, "rb");
    FILE* out = fopen(outputFileName, "wb");
    if (!in) {
        printf("��ѹ�ļ���ȡʧ��\n");
        return;
    }
    if (!out) {
        printf("д�ļ�ʧ��\n");
        return;
    }

    int ch;
    int pos = 510; // �ӹ��������ĸ��ڵ㿪ʼ, ��0��ʼ����510�����
    int len = 0;

    fseek(in, sizeof(HEAD), SEEK_SET); // �����ļ�ͷ

    while ((ch = fgetc(in)) != EOF && len < length) {
        for (int i = 7; i >= 0; i--) {
            int bit = (ch >> i) & 1; // ��λ��ȡ�ֽڣ���ȡ��ǰλ��ֵ��0��1��
            if (bit == 0) {
                pos = HT[pos].lchild;
            }
            else {
                pos = HT[pos].rchild;
            }
            if (HT[pos].lchild == 0 && HT[pos].rchild == 0) {
                fputc(pos, out); // ���Ҷ�ӽڵ��Ӧ���ֽ�
                pos = 510; // ���ظ��ڵ�
                len++;
                if (len == length) {
                    break;
                }
            }
        }
    }

    fclose(in);
    fclose(out);
    printf("��ѹ�ɹ�\n���ɽ�ѹ�ļ�%s", outputFileName);
}