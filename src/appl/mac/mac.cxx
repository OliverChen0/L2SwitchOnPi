#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>


#define PCAP_ERRBUF_SIZE


void packet_handler(u_char *user, const struct pcap_pkthdr *header, const u_char *packet)
{
    printf("Cpatured a packet with length of [%d]\n",header->len);
}

int main()
{
    char *dev,errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    dev = pcap_lookupdev(errbuf);
    
}






