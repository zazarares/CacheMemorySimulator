#include <iostream>
#include "Cache.h"
using namespace std;

int main()
{
    int COMMAND,REPLACEMENT,WRITEMODE;
    Cache_Line cache[256]= {0};
    char data[32];
    char *data2;
    int k=1;
    data[0]=5;
    data[7]=12;
    RAM ram_mem[32768];
    for(int i=0; i<32768; i++)
        {ram_mem[i].data=(char*)malloc(32*sizeof(char));
        for(int j=0;j<32;j++)
            ram_mem[i].data[j]=j;
        }
    print_ram(ram_mem,32768);
    for(int i=0; i<256; i++)
    {
        cache[i].data=(char*)malloc(32*sizeof(char));

    }
    ram_mem[256].data[4]=122;
    ram_mem[257].data[4]=121;
    cout<<"WELCOME TO THE CACHE MEMORY SIMULATOR\n";
    cout<<"CHOOSE MAPPING TYPE:\n1.DirectMapping\n2.AssociativeMapping\n3.KWayAssociative\n";
    cin>>COMMAND;
    switch(COMMAND)
    {
    case 1:
    {
        cout<<"CHOOSE WRITE MODE:\n1.WRITE TROUGH\n2.WRITE BACK\n";
        cin>>WRITEMODE;
        /*check_cache(cache,ram_mem,0,1,data,256,1,WRITEMODE-1,1,0);
        data2=check_cache(cache,ram_mem,0,1,data,256,1,WRITEMODE-1,1,0);
        check_cache(cache,ram_mem,1,1,data2,256,1,WRITEMODE-1,1,0);
        */
        for(int i=0;i<258;i++)
            check_cache(cache,ram_mem,i,k,data,256,COMMAND,WRITEMODE,1,0);
        print_memory(cache,256,1);
        print_ram(ram_mem,32768);
        break;
    }
    case 2:
    {
        cout<<"CHOOSE REPLACEMENT ALGORITHM:\n1.FIFO\n2.LRU\n3.LFU\n";
        cin>>REPLACEMENT;
        REPLACEMENT+=3;
        switch(REPLACEMENT)
        {
        case 4:
        {
            ///FIFO
            cout<<"CHOOSE WRITE MODE:\n1.WRITE TROUGH\n2.WRITE BACK\n";
            cin>>WRITEMODE;
            for(int i=0;i<258;i++)
               check_cache(cache,ram_mem,i,k,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            print_memory(cache,256,1);
            print_ram(ram_mem,32768);

            break;
        }
        case 5:
        {
            ///LRU
            cout<<"CHOOSE WRITE MODE:\n1.WRITE TROUGH\n2.WRITE BACK\n";
            cin>>WRITEMODE;
            for(int i=0;i<256;i++)
               check_cache(cache,ram_mem,i,k,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            for(int i=0;i<123;i++)
            check_cache(cache,ram_mem,i,k,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            check_cache(cache,ram_mem,256,k,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            check_cache(cache,ram_mem,257,k,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);

            print_memory(cache,256,1);
            print_ram(ram_mem,32768);
            break;
        }
        case 6:
        {
            ///LFU
                        cout<<"CHOOSE WRITE MODE:\n1.WRITE TROUGH\n2.WRITE BACK\n";
            cin>>WRITEMODE;
            for(int i=0;i<256;i++)
               check_cache(cache,ram_mem,i,k,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            check_cache(cache,ram_mem,0,k,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,1);
            check_cache(cache,ram_mem,256,k,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);


            print_memory(cache,256,1);
            print_ram(ram_mem,32768);
            break;
            break;
        }
        default:
            break;
        }
        break;

    }
    case 3:
    {
        cout<<"CHOOSE REPLACEMENT ALGORITHM:\n1.FIFO\n2.LRU\n3.LFU\n";
        cin>>REPLACEMENT;
        cout<<"k=?";
        cin>>k;
        if(k==1)
            COMMAND-=2;
        if(k==256)
            COMMAND-=1;
        REPLACEMENT+=3;
        switch(REPLACEMENT)
        {

        case 4:
        {
            ///FIFO
            cout<<"CHOOSE WRITE MODE:\n1.WRITE TROUGH\n2.WRITE BACK\n";
            cin>>WRITEMODE;
            //check_cache(cache,ram_mem,0,2,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            //check_cache(cache,ram_mem,1,2,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            //check_cache(cache,ram_mem,2,2,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            for(int i=0;i<258;i++)
               check_cache(cache,ram_mem,i,k,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);

            print_memory(cache,256,k);
            print_ram(ram_mem,32768);
            break;
        }
        case 5:
        {
            ///LRU
            cout<<"CHOOSE WRITE MODE:\n1.WRITE TROUGH\n2.WRITE BACK\n";
            cin>>WRITEMODE;
            //check_cache(cache,ram_mem,0,2,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            //check_cache(cache,ram_mem,1,2,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            //check_cache(cache,ram_mem,2,2,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            for(int i=0;i<255;i++)
               check_cache(cache,ram_mem,i,k,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            check_cache(cache,ram_mem,0,k,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            check_cache(cache,ram_mem,256,k,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);

            print_memory(cache,256,k);
            print_ram(ram_mem,32768);
            break;
        }
        case 6:
        {
            ///LFU
            cout<<"CHOOSE WRITE MODE:\n1.WRITE TROUGH\n2.WRITE BACK\n";
            cin>>WRITEMODE;
            //check_cache(cache,ram_mem,0,2,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            //check_cache(cache,ram_mem,1,2,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            //check_cache(cache,ram_mem,2,2,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            for(int i=0;i<255;i++)
               check_cache(cache,ram_mem,i,k,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            check_cache(cache,ram_mem,0,k,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            check_cache(cache,ram_mem,64,k,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            check_cache(cache,ram_mem,256,k,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            //check_cache(cache,ram_mem,128,4,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);
            check_cache(cache,ram_mem,256,k,data,256,COMMAND,WRITEMODE,REPLACEMENT-3,0);

            print_memory(cache,256,k);
            print_ram(ram_mem,32768);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
    return 0;
}
