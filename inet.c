#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define DBG(args...)      \
    do{printf("fun:%s,%d ",__FUNCTION__,__LINE__); printf(args);} while(0)
int main(int argc, char **argv)
{
    int i=0,len=0;
    char netString[64]={0};
    char ipNetString[64]={0};
    char maskString[64]={0};
    unsigned int ipNet=0,dest_ip=0,maskLen=0,mask=0;
    if(argc < 3)
    {
        DBG("example:\n");
        DBG("./a.out 192.168.1.0/24 192.168.1.10\n");
        return -1;
    }
    len=strlen(argv[1]);
    memcpy(netString,argv[1],len);
    dest_ip=htonl(inet_addr(argv[2]));
    if(-1 == dest_ip)
    {
        DBG("destination ip err\n");
        return -1;
    }
    DBG("netString=%s\n",netString);
    DBG("destination ip=%08x\n",dest_ip);
    for(i=0;i<len;i++)
    {
        if(0x2f == netString[i])
            break;
    }
    if(i == len)
    {
        DBG("arg err\n");
        return -1;
    }
    memcpy(ipNetString,netString,i);
    memcpy(maskString,netString+i+1,len-i);
    ipNet=htonl(inet_addr(ipNetString));
    maskLen=atoi(maskString);
    if(-1 == ipNet)
    {
        DBG("ip net err\n");
        return -1;
    }
    if(maskLen > 32)
    {
        DBG("mask err\n");
        return -1;
    }
    for(i=0;i<maskLen;i++)
    {
        mask |= (1<<(32-i-1));
    }
    DBG("ipNetString=%s,ipNet=%08x\n",ipNetString,ipNet);
    DBG("maskString=%s,mask=%08x\n",maskString,mask);
    if((dest_ip&mask) == ipNet)
    {
        printf("destination IP is in subnet\n");
    }
    else
    {
        printf("destination IP is out subnet\n");
    }
    
    return 0;
}
