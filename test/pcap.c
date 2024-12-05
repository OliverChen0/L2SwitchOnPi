#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>

void packet_handler(u_int8_t *user, const struct pcap_pkthdr *pkthdr, const u_int8_t *packet)
{
    printf("Packet captured: length = %d\n",pkthdr->len);
}

int main()
{
    pcap_if_t *alldevs, *d;
    pcap_t *handles;
    char errbuf[PCAP_ERRBUF_SIZE];

    if(pcap_findalldevs(&alldevs, errbuf) == -1 )
    {
        fprintf(stderr, "Error in pcap_findalldevs: %s\n",errbuf);
        return 1;
    }
    
    int i = 0;
    for ( d = alldevs; d != NULL; d = d->next)
    {
        printf("%d. %s", ++i ,d->name);
        if( d->description )
        {
            printf(" (%s)",d->description);
        }else{
            printf(" (No description available)");
        }

        printf("\n");
    }

    if (i == 0)
    {
        printf("\nNO interfaces found! Make sure libpcap is installed.\n");
        return 1;
    }

    int devnum;
    printf("Enter the interface number (1-%d):",i );
    scanf("%d",&devnum);

    if ( devnum < 1 || devnum > i )
    {
        printf("\ninterface number out of range.\n");
        return 1;
    }

    for (d = alldevs, i = 0; i < devnum - 1; d = d->next, i++);

    handles = pcap_open_live(d->name, BUFSIZ, 1, 1000, errbuf);
    if ( handles == NULL )
    {
        fprintf(stderr,"Couldn't open device %s: %s\n",d->name,errbuf);
        return 1;
    }

    printf("Listening on %s...\n",d->name);

    pcap_loop(handles, 10, packet_handler, NULL);

    pcap_close(handles);
    pcap_freealldevs(alldevs);

    return 0;
}