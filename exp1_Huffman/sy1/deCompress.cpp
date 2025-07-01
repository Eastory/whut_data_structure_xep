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
    printf("请输入生成解压文件路径（以.bmp为后缀）：");
    scanf("%s", filename3);
    Decode(filename2, filename3, HT, head.length);

}
bool ReadHead(const char* pfilename, HEAD& head) {

    FILE* in = fopen(pfilename, "rb");
    if (!in) {
        printf("读文件失败");
        return false;
    }
    if (fread(head.type, sizeof(head.type), 1, in) != 1) {
        perror("读文件类型失败");
        fclose(in);
        return false;
    }
    if (fread(&head.length, sizeof(head.length), 1, in) != 1) {
        perror("读文件长度失败");
        fclose(in);
        return false;
    }
    if (fread(head.weight, sizeof(head.weight), 1, in) != 1) {
        perror("读权值失败");
        fclose(in);
        return false;
    }
    
	fclose(in);
    printf("读取头文件成功\n");
	return true;
}
void RebuildHuffmanTree(HuffmanTree& HT, int weight[]) {
    printf("重建哈夫曼树\n");
    CreatHuffmanTree(HT, weight);
}
 
void Decode(const char* inputFileName, const char* outputFileName, HuffmanTree HT, int length) {
    FILE* in = fopen(inputFileName, "rb");
    FILE* out = fopen(outputFileName, "wb");
    if (!in) {
        printf("解压文件读取失败\n");
        return;
    }
    if (!out) {
        printf("写文件失败\n");
        return;
    }

    int ch;
    int pos = 510; // 从哈夫曼树的根节点开始, 从0开始，第510个结点
    int len = 0;

    fseek(in, sizeof(HEAD), SEEK_SET); // 跳过文件头

    while ((ch = fgetc(in)) != EOF && len < length) {
        for (int i = 7; i >= 0; i--) {
            int bit = (ch >> i) & 1; // 逐位读取字节，获取当前位的值（0或1）
            if (bit == 0) {
                pos = HT[pos].lchild;
            }
            else {
                pos = HT[pos].rchild;
            }
            if (HT[pos].lchild == 0 && HT[pos].rchild == 0) {
                fputc(pos, out); // 输出叶子节点对应的字节
                pos = 510; // 返回根节点
                len++;
                if (len == length) {
                    break;
                }
            }
        }
    }

    fclose(in);
    fclose(out);
    printf("解压成功\n生成解压文件%s", outputFileName);
}