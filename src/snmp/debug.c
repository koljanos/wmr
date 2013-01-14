#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "snmp.h"
#include "oiddb.h"

void debugg(unsigned char *packet, int length)
{
	int position=0;
	int width=16;
	int i;
	unsigned char displayNumb[width];
	unsigned char displayChar[width];
	while (position<length) {
		for (i=0; i<width;i++) {
			displayNumb[i]=0x00;
			displayChar[i]=0x00;
		}
		for (i=0; i<(width); i++) {

			char temp;
			temp=packet[position++];
			displayNumb[i]=temp;
			if (temp<32) {
				temp='-';
			};
			displayChar[i]=temp;
			if (position>=length) {
				i=width;
			}
		}
		for (i=0; i<(width); i++) {
			printf("%02X", displayNumb[i]);
            if (i < (width - 1)) {
                printf(" ");
            }
		}
		printf(" -->   ");
		for (i=0;i< (width); i++) {
			printf("%c", displayChar[i]);
		}
		printf("\n");
	}
}
