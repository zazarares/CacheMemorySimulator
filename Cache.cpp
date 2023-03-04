//#include
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <queue>
#include "Cache.h"
//#include
using namespace std;
int index_of_queue[129]= {0};
int Last_accessed[129][256]= {0};
int Access_Freq[129][256]= {0};
int FIFO(int cacheSize,int data_set)
{
    if(index_of_queue[data_set]>=cacheSize-1)
        {index_of_queue[data_set]=0;
        return 0;}
    else
        index_of_queue[data_set]++;
    return index_of_queue[data_set]-1;
}
int Access(int cacheSize,int data_set,int accesed)
{
    Last_accessed[data_set][accesed]=0;
    for(int i=0; i<cacheSize; i++)
        Last_accessed[data_set][i]++;
    Access_Freq[data_set][accesed]++;
}
int LRU(int cacheSize,int data_set)
{
    int maxi=-1;
    int line_index;
    for(int i=0; i<cacheSize; i++)
        if(maxi<Last_accessed[data_set][i])
        {
            maxi=Last_accessed[data_set][i];
            line_index=i;
        }
    return line_index;
}
int LFU(int cacheSize,int data_set)
{
    int mini=10000;
    int line_index;
    for(int i=0; i<cacheSize; i++)
        if(Access_Freq[data_set][i]<mini)
        {
            mini=Access_Freq[data_set][i];
            line_index=i;
        }
    return line_index;
}
int Direct_Mapping(int memory_block,int cacheSize)
{
    return memory_block%cacheSize;
}
void Write_Through(RAM ram_mem[],short address,Cache_Line cache[],char data[],int cacheSize,int cache_Address,int k,int update)
{

    for(int i=0; i<=31; i++)
        cache[cache_Address].data[i]=data[i];
    cache[cache_Address].tag=address/cacheSize;
    cache[cache_Address].index=address%cacheSize;
    cache[cache_Address].Valid=true;
    if(update)
        ram_mem[address].data=data;
    /*
    case 2:
    {int temp=Associative_Mapping(cache,cacheSize,0,replacement_alg).first;
    for(int i=0;i<=31;i++)
        cache[temp].data[i]=data[i];
    cache[temp].tag=address/cacheSize;
    cache[temp].index=address%cacheSize;
    if(update)
    ram_mem[address].data=data;
    cache[temp].Valid=true;
    break;}
    case 3:
    pair<int,pair<int,bool>> temp=K_WayAsociativeMapping(k,cache,address,cacheSize,replacement_alg);
    for(int i=0;i<=31;i++)
        cache[temp.first*k+temp.second.first].data[i]=data[i];
    cache[temp.first*k+temp.second.first].tag=address/cacheSize;
    cache[temp.first*k+temp.second.first].index=address%cacheSize;

    ram_mem[address].data=data;
    cache[temp.first*k+temp.second.first].Valid=true;
    break;
    */

}
void Write_Back(RAM ram_mem[],short address,Cache_Line cache[],char data[],int cacheSize,int cache_Address,int k,int update)
{

    if(update)
        ram_mem[address].data=cache[cache_Address].data;
    for(int i=0; i<=31; i++)
        cache[cache_Address].data[i]=data[i];
    cache[cache_Address].tag=address/cacheSize;
    cache[cache_Address].index=address%cacheSize;
    cache[cache_Address].Valid=true;
    /*
            {int temp=Associative_Mapping(cache,cacheSize,0,replacement_alg).first;
            if(update)
            ram_mem[address].data=cache[temp].data;
            for(int i=0;i<=31;i++)
                cache[temp].data[i]=data[i];
            cache[temp].tag=address/cacheSize;
            cache[temp].index=address%cacheSize;
            cache[temp].Valid=true;
            break;}
        case 3:
            pair<int,pair<int,bool>> temp=K_WayAsociativeMapping(k,cache,address,cacheSize,replacement_alg);
            ram_mem[address].data=cache[temp.first*k+temp.second.first].data;
            for(int i=0;i<=31;i++)
                cache[temp.first*k+temp.second.first].data[i]=data[i];
            cache[temp.first*k+temp.second.first].tag=address/cacheSize;
            cache[temp.first*k+temp.second.first].index=address/cacheSize;
            cache[temp.first*k+temp.second.first].Valid=true;
            break;
            */
}

pair<int,bool> Associative_Mapping(Cache_Line cache[],int cacheSize,int cache_set,int replacement_alg)
{
    pair<int,bool> toReturn;
    for(int i=0; i<cacheSize; i++)
        if(cache[i].Valid==false)
        {
            toReturn.first=i;
            toReturn.second=1;
            return toReturn;
        }
    toReturn.second=0;
    ///REPLACEMENT ALGORITHM
    switch(replacement_alg)
    {
    ///FIFO
    case 1:
        toReturn.first=FIFO(cacheSize,cache_set);
        break;
    ///LRU
    case 2:
        toReturn.first= LRU(cacheSize,cache_set);
        break;
    ///LFU
    case 3:
        toReturn.first= LFU(cacheSize,cache_set);
        break;
    default:
        exit(-1);
    }
    return toReturn;
}
pair<int,pair<int,bool>>K_WayAsociativeMapping(int k,Cache_Line cache[],int memoryBlock,int cacheSize,int replacement_alg)
{
    int numberofSets=cacheSize/k;
    pair<int,pair<int,bool>> toreturn;
    toreturn.first=Direct_Mapping(memoryBlock,numberofSets);
    Cache_Line cache_set[k];
    for(int i=0; i<k; i++)
        cache_set[i]=cache[toreturn.first*k+i];
    toreturn.second=Associative_Mapping(cache_set,k,toreturn.first,replacement_alg);
    return toreturn;
}
char* check_cache(Cache_Line cache[],RAM ram_mem[],short address,int k,char data[],int cacheSize,int mappingType,int writeMode,int replacementAlg,int update_data)
{
    int ok=-1;
    switch(mappingType)
    {
    case 1:
        if(update_data)
        {
            if(writeMode==0)
                Write_Back(ram_mem,address,cache,data,cacheSize,Direct_Mapping(address,cacheSize),k,update_data);
            else
                Write_Through(ram_mem,address,cache,data,cacheSize,Direct_Mapping(address,cacheSize),k,update_data);
        }
        if(cache[address%cacheSize].tag==address/cacheSize && cache[address%cacheSize].Valid==true)
            return cache[address%cacheSize].data;
        else
        {
            if(writeMode==0)
                Write_Back(ram_mem,address,cache,ram_mem[address].data,cacheSize,Direct_Mapping(address,cacheSize),k,update_data);
            else
                Write_Through(ram_mem,address,cache,ram_mem[address].data,cacheSize,Direct_Mapping(address,cacheSize),k,update_data);
        }

        Access(cacheSize,1,address%cacheSize);
        return cache[address%cacheSize].data;
        break;
    case 2:

    {
        for(int i=0; i<cacheSize; i++)
        {
            if(cache[i].tag==address/cacheSize && cache[i].index==address%cacheSize && cache[i].Valid==true)
            {
                Access(cacheSize,1,i);
                return cache[i].data;
            }
        }
        int temp=Associative_Mapping(cache,cacheSize,k,replacementAlg).first;
        if(update_data)
            if(writeMode==0)
                Write_Back(ram_mem,address,cache,data,cacheSize,temp,k,update_data);
            else
                Write_Through(ram_mem,address,cache,data,cacheSize,temp,k,update_data);

        Access(cacheSize,1,temp);
        if(writeMode==0)
            Write_Back(ram_mem,address,cache,ram_mem[address].data,cacheSize,temp,k,update_data);
        else
            Write_Through(ram_mem,address,cache,ram_mem[address].data,cacheSize,temp,k,update_data);
        return ram_mem[address].data;

        break;
    }


    case 3:
        for(int i=address%(cacheSize/k);i<address%(cacheSize/k)+k;i++)
            if(cache[i].tag==address/cacheSize && cache[i].index==address%cacheSize && cache[i].Valid==true)
        {
            Access(cacheSize,address%(cacheSize/k),i);
            return cache[i].data;
        }
        pair<int,pair<int,bool>> temp=K_WayAsociativeMapping(k,cache,address,cacheSize,replacementAlg);
        if(update_data)
            if(writeMode==0)
                Write_Back(ram_mem,address,cache,data,cacheSize,temp.first*(cacheSize/k)+temp.second.first,k,update_data);
            else
                Write_Through(ram_mem,address,cache,data,cacheSize,temp.first*(cacheSize/k)+temp.second.first,k,update_data);
        Access(cacheSize,temp.first,temp.second.first);
        if(writeMode==0)
            Write_Back(ram_mem,address,cache,ram_mem[address].data,cacheSize,temp.first*k+temp.second.first,k,update_data);
        else
            Write_Through(ram_mem,address,cache,ram_mem[address].data,cacheSize,temp.first*k+temp.second.first,k,update_data);
        break;
    }

}
void print_memory(Cache_Line cache[],int cacheSize,int k)
{
    FILE* f=fopen("cache.txt","w+");
    for(int j=0; j<cacheSize; j++)
    {
        if(k>1)
        if(j%k==0)
            fprintf_s(f,"\n");
        for(int i=0; i<32; i++)
            fprintf_s(f,"%hhu ",cache[j].data[i]);
        fprintf(f,"\n");
    }
}
void print_ram(RAM ram_mem[],int ram_size)
{
    FILE* f=fopen("ram.txt","w+");
    for(int j=0; j<ram_size; j++)
    {
        for(int i=0; i<32; i++)
            fprintf_s(f,"%hhu ",ram_mem[j].data[i]);
        fprintf(f,"\n");
    }
}
