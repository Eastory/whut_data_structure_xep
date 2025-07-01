#pragma once
#include"Huffman.h"
#include"Compress.h"

void deCompress(const char* filename2);

bool ReadHead(const char* filename, HEAD& head);
void RebuildHuffmanTree(HuffmanTree& HT, int weight[]);
void Decode(const char* inputFileName, const char* outputFileName, HuffmanTree HT, int originalLength);