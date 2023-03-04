#ifndef CACHE_H
#define CACHE_H
#include<stdlib.h>
typedef struct{
bool Valid;
char tag;
char *data;
char index;
}Cache_Line;
typedef struct{
    char *data;
}RAM;
//Cache_Line cache[32];
int FIFO(int cacheSize,int data_set);
int Access(int cacheSize,int data_set,int accesed);
int LRU(int cacheSize,int data_set);
int LFU(int cacheSize,int data_set);
int Direct_Mapping(int memory_block,int cacheSize);
std::pair<int,bool> Associative_Mapping(Cache_Line cache[],int cacheSize,int cache_set,int replacement_alg);
std::pair<int,std::pair<int,bool>>K_WayAsociativeMapping(int k,Cache_Line cache[],int memoryBlock,int cacheSize,int replacement_alg);
char* check_cache(Cache_Line cache[],RAM ram_mem[],short address,int k,char data[],int cacheSize,int mappingType,int writeMode,int replacementAlg,int update_data);
void print_ram(RAM ram_mem[],int ram_size);
void print_memory(Cache_Line cache[],int cacheSize,int k);

#endif
