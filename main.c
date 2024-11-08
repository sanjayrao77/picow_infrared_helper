#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
#define DEBUG
#include "common/conventions.h"


#define PASSWORD8	"password"

// see ~/src/rpi/irreader to get codes and parse them into C


struct command {
	char *name;
	char *neccode;
	int *ircodes;
};

#if 0
// nec 78-50
static int stereo_yamaha_soundbar_ircode[]={9066,4408,653,481,650,483,660,473,658,1583,653,1591,656,1585,653,1586,657,475,661,1582,650,1593,654,1588,651,480,658,475,658,475,658,475,659,1582,655,480,652,481,652,485,648,483,655,1587,654,479,653,1591,656,474,658,1586,650,1588,657,1584,651,1592,654,477,656,1588,652,480,653,1587,654,39720,9096,2164,650,0};

// nec 78-9c
static int mute_yamaha_soundbar_ircode[]={9037,4461,603,529,606,529,598,534,600,1642,603,1640,604,1638,601,1646,601,529,599,1643,602,1641,604,1639,600,533,603,533,601,532,602,532,602,1638,600,536,600,531,603,1640,602,1640,603,1639,605,530,604,529,601,1641,604,1640,600,1641,599,535,600,534,601,533,601,1640,600,1646,597,534,596,39801,9042,2214,600,0};

// nec 78-49
static int optical_yamaha_soundbar_ircode[]={9011,4455,604,527,604,529,602,532,604,1636,606,1635,602,1641,600,1640,604,528,606,1645,598,1635,605,1638,599,533,599,532,602,531,603,530,605,1637,602,1640,599,532,603,531,602,1639,600,534,601,532,603,1639,600,533,600,532,604,1638,600,1641,604,539,593,1639,607,1636,602,530,605,1636,603,39796,9032,2214,603,0};

// nec 78-29
static int bluetooth_yamaha_soundbar_ircode[]={9018,4463,599,529,604,529,600,533,601,1639,605,1636,603,1642,597,1642,602,531,603,1637,602,1641,604,1641,599,532,602,531,598,535,599,534,601,1640,600,1644,602,530,603,530,601,1640,603,532,597,1642,608,527,603,530,600,533,599,1643,598,1644,607,527,607,1635,606,529,606,1647,591,1638,600,39785,9046,2215,600,0};

// nec 78-1e
static int up_volume_yamaha_soundbar_ircode[]={9050,4468,604,532,603,530,604,533,602,1640,602,1640,602,1642,603,1642,602,532,605,1640,601,1639,607,1638,602,535,600,537,600,530,607,532,603,1637,602,535,602,1640,607,1637,602,1640,599,1645,605,530,607,527,608,527,610,1634,605,530,605,530,604,530,605,530,597,1646,607,1634,605,1640,602,39789,9047,2226,600,0};

// nec 78-1f
static int down_volume_yamaha_soundbar_ircode[]={9055,4462,603,535,599,535,603,532,604,1638,603,1641,604,1641,604,1638,602,533,605,1640,599,1646,598,1642,606,529,604,532,602,533,605,530,599,1643,605,1637,603,1642,600,1642,607,1637,605,1639,601,535,599,535,601,534,603,532,602,531,607,529,606,530,599,535,602,1640,603,1642,602,1642,598,39792,9053,2216,605,0};
static struct command commands_global[]={
{"stereo","7850",stereo_yamaha_soundbar_ircode},
{"mute","789c",mute_yamaha_soundbar_ircode},
{"optical","7849",optical_yamaha_soundbar_ircode},
{"bluetooth","7829",bluetooth_yamaha_soundbar_ircode},
{"up_volume","781e",up_volume_yamaha_soundbar_ircode},
{"down_volume","781f",down_volume_yamaha_soundbar_ircode},
{NULL,NULL,NULL}
};
#endif

static int down_volume_nad_ircode[]={7434,53459,8931,4439,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,542,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,1652,542,1652,542,542,542,542,542,542,542,1652,542,1652,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,542,542,38436,8931,2219,542,95225,0};

static int up_volume_nad_ircode[]={7434,53330,8570,4465,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,542,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,542,542,1652,542,542,542,542,542,542,542,1652,542,1652,542,1652,542,1652,542,542,542,1652,542,1652,542,1652,542,542,542,38436,8570,2219,542,95225,0};

static int mute_nad_ircode[]={7434,53640,8931,4439,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,542,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,1652,542,542,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,542,542,1652,542,542,542,1652,542,1652,542,542,542,38410,8931,2219,542,95225,0};

static int pronto_ircode[]={7434,53459,8931,4439,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,542,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,1652,542,1652,542,542,542,542,542,542,542,1652,542,1652,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,542,542,38436,8931,2219,542,95225,0};

static int power_nad_ircode[]={7640,53201,8931,4439,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,542,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,542,542,542,542,542,542,542,542,542,542,1652,542,1652,542,1652,542,1652,542,1652,542,1652,542,1652,542,1652,542,542,542,38436,8931,2219,542,95225,0};

static int sleep_nad_ircode[]={7485,57925,8983,4439,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,542,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,542,542,542,542,542,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,1652,542,1652,542,542,542,1652,542,1652,542,38436,8983,2219,542,95225,0};

static int late_nad_ircode[]={7253,65462,8699,4439,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,542,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,1652,542,1652,542,542,542,1652,542,1652,542,1652,542,1652,542,542,542,1652,542,542,542,542,542,542,542,542,542,542,542,542,542,1652,542,542,542,1652,542,1652,542,38410,8699,2219,542,95225,0};

static int left_nad_ircode[]={7253,64533,8518,4439,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,542,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,1652,542,1652,542,542,542,1652,542,542,542,542,542,1652,542,542,542,1652,542,542,542,542,542,542,542,1652,542,1652,542,542,542,1652,542,542,542,1652,542,1652,542,38436,8518,2219,542,95225,0};

static int right_nad_ircode[]={7253,64713,8879,4465,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,542,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,1652,542,1652,542,542,542,542,542,1652,542,542,542,1652,542,542,542,1652,542,542,542,542,542,1652,542,542,542,1652,542,542,542,1652,542,542,542,1652,542,1652,542,38436,8879,2219,542,95225,0};

static int up_nad_ircode[]={7253,64300,8931,4439,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,542,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,1652,542,1652,542,542,542,1652,542,1652,542,1652,542,542,542,542,542,1652,542,542,542,542,542,542,542,542,542,542,542,1652,542,1652,542,542,542,1652,542,1652,542,38436,8931,2219,542,95225,0};

static int down_nad_ircode[]={7253,64404,8931,4465,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,542,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,542,542,1652,542,542,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,542,542,1652,542,542,542,1652,542,1652,542,38436,8931,2219,542,95225,0};

// static int enter_nad_ircode[]={8884,4455,547,1667,547,547,547,1667,547,547,547,547,547,547,547,547,547,1667,547,547,547,1667,547,547,547,1667,547,1667,547,547,547,547,547,1667,547,547,547,1667,547,1667,547,547,547,547,547,1667,547,1667,547,547,547,1667,547,547,547,547,547,1667,547,1667,547,547,547,547,547,1667,547,40019,8884,2214,547,96141,0};
static int enter_nad_ircode[]={7253,65875,8931,4439,567,1652,567,1652,567,1652,567,567,567,567,567,567,567,567,567,1652,567,567,567,567,567,1652,567,1652,567,1652,567,1652,567,1652,567,567,567,567,567,1652,567,567,567,567,567,1652,567,1652,567,567,567,567,567,1652,567,567,567,1652,567,1652,567,567,567,567,567,1652,567,1652,567,20237,567,2219,567,125504,0};

static int speakera_nad_ircode[]={7537,53872,8931,4439,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,542,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,1652,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,1652,542,1652,542,542,542,542,542,38410,8931,2219,542,95225,0};

static int speakerb_nad_ircode[]={7485,54001,8466,4439,542,1652,542,1652,542,1652,542,542,542,542,542,542,542,542,542,1652,542,542,542,542,542,1652,542,1652,542,1652,542,1652,542,1652,542,542,542,1652,542,1652,542,1652,542,1652,542,542,542,542,542,1652,542,1652,542,542,542,542,542,542,542,542,542,1652,542,1652,542,542,542,542,542,38410,8466,2219,542,95225,0};

static struct command commands_global[]={
{"stereo","7850",NULL}, // stereo_yamaha_soundbar_ircode},
{"mute","789c",NULL}, // mute_yamaha_soundbar_ircode},
{"optical","7849",NULL}, // optical_yamaha_soundbar_ircode},
{"bluetooth","7829",NULL}, // bluetooth_yamaha_soundbar_ircode},
{"up_volume","781e",NULL}, // up_volume_yamaha_soundbar_ircode},
{"down_volume","781f",NULL}, // down_volume_yamaha_soundbar_ircode},
{"up_volume_nad",NULL,up_volume_nad_ircode},
{"down_volume_nad",NULL,down_volume_nad_ircode},
{"mute_nad",NULL,mute_nad_ircode},
{"power_nad",NULL,power_nad_ircode},
{"sleep_nad",NULL,sleep_nad_ircode},
{"late_nad",NULL,late_nad_ircode},
{"left_nad",NULL,left_nad_ircode},
{"right_nad",NULL,right_nad_ircode},
{"up_nad",NULL,up_nad_ircode},
{"down_nad",NULL,down_nad_ircode},
{"enter_nad",NULL,enter_nad_ircode},
{"speakera_nad",NULL,speakera_nad_ircode},
{"speakerb_nad",NULL,speakerb_nad_ircode},
{"pronto",NULL,pronto_ircode}, // test
{NULL,NULL,NULL}
};

static unsigned char password8_global[8]=PASSWORD8;

struct listen_udp {
	int fd;
	unsigned short port;
};
static void clear_listen_udp(struct listen_udp *l) {
static struct listen_udp blank={.fd=-1};
*l=blank;
}

static int init_listen_udp(struct listen_udp *l, unsigned short start_port, unsigned short stop_port) {
int fd=-1;
unsigned short port;
if (0>(fd=socket(AF_INET,SOCK_DGRAM,0))) GOTOERROR;

for (port=start_port;port<=stop_port;port++) {
	struct sockaddr_in sa;
	memset(&sa,0,sizeof(sa));
	sa.sin_family=AF_INET;
	sa.sin_port=htons(port);
	if (0>bind(fd,(struct sockaddr*)&sa,sizeof(sa))) {
		if (errno==EADDRINUSE) continue;
		GOTOERROR;
	}
	goto found;
}
GOTOERROR;
found:

l->fd=fd;
l->port=port;
return 0;
error:
	ifclose(fd);
	return -1;
}

static void deinit_listen_udp(struct listen_udp *l) {
ifclose(l->fd);
}

static unsigned int slowtou(char *str) {
unsigned int ret=0;
switch (*str) {
	case '1': ret=1; break;
	case '2': ret=2; break;
	case '3': ret=3; break;
	case '4': ret=4; break;
	case '5': ret=5; break;
	case '6': ret=6; break;
	case '7': ret=7; break;
	case '8': ret=8; break;
	case '9': ret=9; break;
	case '+':
	case '0': break;
	default: return 0; break;
}
while (1) {
	str++;
	switch (*str) {
		case '9': ret=ret*10+9; break;
		case '8': ret=ret*10+8; break;
		case '7': ret=ret*10+7; break;
		case '6': ret=ret*10+6; break;
		case '5': ret=ret*10+5; break;
		case '4': ret=ret*10+4; break;
		case '3': ret=ret*10+3; break;
		case '2': ret=ret*10+2; break;
		case '1': ret=ret*10+1; break;
		case '0': ret=ret*10; break;
		default: return ret; break;
	}
}
return ret;
}


struct ipv4address {
	unsigned char ipv4[4];
	unsigned short port;
};
SCLEARFUNC(ipv4address);

static void voidinit_ipv4address(struct ipv4address *ip, unsigned char ipv4_0, unsigned char ipv4_1, unsigned char ipv4_2,
		unsigned char ipv4_3, unsigned short port) {
ip->ipv4[0]=ipv4_0;
ip->ipv4[1]=ipv4_1;
ip->ipv4[2]=ipv4_2;
ip->ipv4[3]=ipv4_3;
ip->port=port;
}

static int init_ipv4address(struct ipv4address *dest, char *str, unsigned short default_port) {
unsigned char first=0,second=0,third=0,fourth=0;
unsigned short port=default_port;
if (!strchr(str,'.')) {
	uint32_t ip;
	ip=slowtou(str);
	first=ip&0xff;
	ip=ip>>8;
	second=ip&0xff;
	ip=ip>>8;
	third=ip&0xff;
	ip=ip>>8;
	fourth=ip&0xff;
} else {
	char *ip;
	ip=str;
	first=slowtou(ip);
	ip=strchr(ip,'.');
	if (ip) {
		ip++;
		second=slowtou(ip);
		ip=strchr(ip,'.');
		if (ip) {
			ip++;
			third=slowtou(ip);
			ip=strchr(ip,'.');
			if (ip) {
				ip++;
				fourth=slowtou(ip);
			}
		}
	}
}

{
	char *portstr;
	portstr=strchr(str,':');
	if (portstr) {
		port=slowtou(portstr+1);
	}
}

voidinit_ipv4address(dest,first,second,third,fourth,port);
return 0;
}

static int makepacket(unsigned int *packetlen_out, unsigned char *dest_in, unsigned int destlen, int *codes, 
		struct ipv4address *ipv4_reply, unsigned short sequence) {
unsigned int packetlen=26;
unsigned char *dest;

if (destlen<26) GOTOERROR;
dest=dest_in+26;
destlen-=26;

{
	while (1) {
		unsigned short s;
		s=*codes;
		if (!s) break;
		if (destlen<2) GOTOERROR;
		*dest=(s>>8)&0xff;
		dest+=1;
		*dest=s&0xff;
		dest+=1;
		codes+=1;
		destlen-=2;
		packetlen+=2;
	}

}

memcpy(dest_in,"UDP2IR01",8);
memcpy(dest_in+8,password8_global,8);
dest_in[16]=(packetlen>>8)&0xff;
dest_in[17]=packetlen&0xff;
dest_in[18]=(sequence>>8)&0xff;
dest_in[19]=sequence&0xff;
memcpy(dest_in+20,ipv4_reply->ipv4,4);
{
	unsigned short replyport;
	replyport=ipv4_reply->port;
	dest_in[24]=(replyport>>8)&0xff; // reply port, high
	dest_in[25]=replyport&0xff; // reply port, low
}


*packetlen_out=packetlen;
return 0;
error:
	return -1;
}

static int sendpacket(struct ipv4address *ipv4a, unsigned char *packet, unsigned int packetlen) {
struct sockaddr_in sa;
uint32_t ipv4;
int fd=-1;

memset(&sa,0,sizeof(sa));

if (0>(fd=socket(AF_INET,SOCK_DGRAM,0))) GOTOERROR;
sa.sin_family=AF_INET;
ipv4=ipv4a->ipv4[3];
ipv4=ipv4<<8;
ipv4+=ipv4a->ipv4[2];
ipv4=ipv4<<8;
ipv4+=ipv4a->ipv4[1];
ipv4=ipv4<<8;
ipv4+=ipv4a->ipv4[0];
sa.sin_addr.s_addr=ipv4;
sa.sin_port=htons(ipv4a->port);

if (0>sendto(fd,packet,packetlen,0,(struct sockaddr*)&sa,sizeof(sa))) GOTOERROR;

#if 0
#warning printing packet
{
	unsigned int ui;
	fprintf(stdout,"Sent packet: ");
	for (ui=0;ui<packetlen;ui++) {
		fprintf(stdout,"%02x ",packet[ui]);
	}
	fputs("\n",stdout);
}
#endif

close(fd);
return 0;
error:
	ifclose(fd);
	return -1;
}

static int waitforpacket_listener(int *istimeout_out, unsigned int *len_out, unsigned char *dest, struct ipv4address *ipv4src_out,
		struct listen_udp *listener, unsigned int destmax, uint64_t expires) {
int fd;

fd=listener->fd;

while (1) {
	fd_set rset;
	uint64_t now;
	struct timeval tv;

	now=time(NULL);
	if (expires < now) {
		*istimeout_out=1;
		return 0;
	}
	tv.tv_sec=1;
	tv.tv_usec=0;

	FD_ZERO(&rset);
	FD_SET(fd,&rset);
	switch(select(fd+1,&rset,NULL,NULL,&tv)) {
		case -1:
			if (errno==EINTR) break;
			GOTOERROR;
		case 0: break;
		case 1:
			if (FD_ISSET(fd,&rset)) {
				goto done;
			}
	}
}
done:
{
	int k;
	if (ipv4src_out) {
		struct sockaddr_in sa;
		socklen_t ssa;
		ssa=sizeof(sa);
		k=recvfrom(fd,dest,destmax,0,(struct sockaddr*)&sa,&ssa);
		if (k<0) {
			GOTOERROR;
		}
		if (ssa==sizeof(sa)) {
			uint32_t ipv4;
			ipv4=sa.sin_addr.s_addr;
			ipv4src_out->ipv4[0]=ipv4&0xff; ipv4=ipv4>>8;
			ipv4src_out->ipv4[1]=ipv4&0xff; ipv4=ipv4>>8;
			ipv4src_out->ipv4[2]=ipv4&0xff; ipv4=ipv4>>8;
			ipv4src_out->ipv4[3]=ipv4&0xff;
			ipv4src_out->port=ntohs(sa.sin_port);
		} else {
			clear_ipv4address(ipv4src_out);
		}
	} else {
		k=recv(fd,dest,destmax,0);
		if (k<0) {
			GOTOERROR;
		}
	}
	
	*istimeout_out=0;
	*len_out=(unsigned int)k;
}
return 0;
error:
	return -1;
}

static int send_irsender(unsigned int *sequence_out, struct ipv4address *ipv4_dest, int *ircodes, struct ipv4address *ipv4_listen,
		unsigned int sequence, struct listen_udp *listener) {
unsigned char packet[512];
unsigned int packetlen;
uint64_t expires;
int istimeout;
int fuse=4;

while (1) {
	fuse--;
	if (!fuse) {
		fprintf(stderr,"%s:%d no response from irserver\n",__FILE__,__LINE__);
		GOTOERROR;
	}
	if (makepacket(&packetlen,packet,512,ircodes,ipv4_listen,(unsigned short)sequence)) GOTOERROR;
	fprintf(stderr,"%s:%d sending packet with sequence %u\n",__FILE__,__LINE__,sequence);
	if (sendpacket(ipv4_dest,packet,packetlen)) GOTOERROR;
	expires=time(NULL)+5;
	while (1) {
		if (waitforpacket_listener(&istimeout,&packetlen,packet,NULL,listener,512,expires)) GOTOERROR;
		if (istimeout) {
			fprintf(stderr,"%s:%d timed out waiting for ACK\n",__FILE__,__LINE__);
		} else if ((packetlen>12) && !memcmp(packet,"UDP2IR01 ACK",12)) {
			char *temp;
			unsigned int seq,nseq;

			if (packetlen>511) GOTOERROR;
			packet[packetlen]=0;
			temp=(char *)packet+12;
			if (*temp!=' ') GOTOERROR;
			temp++;
			seq=slowtou(temp);
			if (sequence) {
				if (sequence!=seq) {
					fprintf(stderr,"%s:%d got ACK for sequence %u but we sent %u\n",__FILE__,__LINE__,seq,sequence);
					continue;
				}
			}
			temp=strchr(temp,' ');
			if (temp && !strncmp(temp+1,"next ",5)) {
				temp+=6;
				nseq=slowtou(temp);
				fprintf(stderr,"%s:%d next sequence is %u\n",__FILE__,__LINE__,nseq);
				sequence=nseq;
			}
			goto doublebreak;
		} else {
			fprintf(stderr,"%s:%d got stray packet\n",__FILE__,__LINE__);
			continue;
	#if 0
			unsigned int ui;
			for (ui=0;ui<packetlen;ui++) {
				fprintf(stdout,"%02x (%c)",packet[ui],isprint(packet[ui])?packet[ui]:'?');
			}
			fputs("\n",stdout);

	#endif
			
		}
		break;
	}
	if (!sequence) {
		fprintf(stderr,"%s:%d no response from irserver and won't retry without sequence\n",__FILE__,__LINE__);
		GOTOERROR;
	}
}
doublebreak:

*sequence_out=sequence;
return 0;
error:
	return -1;
}


static int findsequence_irsender(unsigned int *sequence_out, struct ipv4address *ipv4_dest, struct ipv4address *ipv4_listen,
		struct listen_udp *listener) {
unsigned char packet[512];
unsigned int packetlen;
unsigned int sequence=0;
int ircodes[]={0};
uint64_t expires;
int istimeout;

expires=time(NULL)+5;

if (makepacket(&packetlen,packet,512,ircodes,ipv4_listen,0)) GOTOERROR;
if (sendpacket(ipv4_dest,packet,packetlen)) GOTOERROR;
while (1) {
	if (waitforpacket_listener(&istimeout,&packetlen,packet,NULL,listener,512,expires)) GOTOERROR;
	if (istimeout) {
		fprintf(stderr,"%s:%d timed out waiting for ACK\n",__FILE__,__LINE__);
	} else if ((packetlen>12) && !memcmp(packet,"UDP2IR01 ACK",12)) {
		char *temp;

		if (packetlen>511) GOTOERROR;
		packet[packetlen]=0;
		temp=(char *)packet+12;
		if (*temp!=' ') GOTOERROR;
		temp++;
		sequence=slowtou(temp);
	} else {
		fprintf(stderr,"%s:%d got stray packet\n",__FILE__,__LINE__);
		continue;
#if 0
		unsigned int ui;
		for (ui=0;ui<packetlen;ui++) {
			fprintf(stdout,"%02x (%c)",packet[ui],isprint(packet[ui])?packet[ui]:'?');
		}
		fputs("\n",stdout);

#endif
		
	}
	break;
}

*sequence_out=sequence;
return 0;
error:
	return -1;
}

static int ipsearch_irsender(unsigned int *sequence_out, struct ipv4address *ipv4_dest_inout, struct ipv4address *ipv4_listen,
		struct listen_udp *listener) {
unsigned char packet[512];
unsigned int packetlen;
unsigned int sequence=0;
int ircodes[]={0};
uint64_t expires;
int istimeout;
unsigned char uc;

expires=time(NULL)+5;

if (makepacket(&packetlen,packet,512,ircodes,ipv4_listen,0)) GOTOERROR;

for (uc=1;uc<255;uc++) {
	ipv4_dest_inout->ipv4[3]=uc;
	if (sendpacket(ipv4_dest_inout,packet,packetlen)) GOTOERROR;
}

while (1) {
	struct ipv4address src_ipv4;

	if (waitforpacket_listener(&istimeout,&packetlen,packet,&src_ipv4,listener,512,expires)) GOTOERROR;
	if (istimeout) {
		fprintf(stderr,"%s:%d timed out waiting for ACK\n",__FILE__,__LINE__);
	} else if ((packetlen>12) && !memcmp(packet,"UDP2IR01 ACK",12)) {
		char *temp;

		if (packetlen>511) GOTOERROR;
		packet[packetlen]=0;
		temp=(char *)packet+12;
		if (*temp!=' ') GOTOERROR;
		temp++;
		sequence=slowtou(temp);
		*ipv4_dest_inout=src_ipv4;
	} else {
		continue;
	}
	break;
}

*sequence_out=sequence;
return 0;
error:
	return -1;
}

static inline unsigned char _hexval1(unsigned int b) {
if (!(b&64)) return (unsigned char)b&15;
return (unsigned char)(b&31)+9;
}

static void getbittimes32(int *dest, unsigned int code, unsigned int offtime, unsigned int ontime) {
int *idest;
int i=0;

idest=dest+16;
for (i=0;i<8;i++) {
	*dest=offtime; dest++;
	*idest=offtime; idest++;
	if (code&1) {
		*dest=ontime; dest++;
		*idest=offtime; idest++;
	} else {
		*dest=offtime; dest++;
		*idest=ontime; idest++;
	}
	code=code>>1;
}
}
static void getbittimes16(int *dest, unsigned int code, unsigned int offtime, unsigned int ontime) {
int i=0;

for (i=0;i<8;i++) {
	*dest=offtime; dest++;
	if (code&1) {
		*dest=ontime; dest++;
	} else {
		*dest=offtime; dest++;
	}
	code=code>>1;
}
}

static int nec_getircodes(int *dest, int max, char *str) {
int n;
n=strlen(str);
if (n==4) {
	unsigned int code1,code2;
	int ticks=29;
	unsigned int ontime=0x40*ticks,offtime=0x15*ticks;
	
	if (max<72) GOTOERROR;
	code1=_hexval1(str[0])*16+_hexval1(str[1]);
	code2=_hexval1(str[2])*16+_hexval1(str[3]);
	dest[0]=0x155*ticks;
	dest[1]=0xaa*ticks;
	(void)getbittimes32(dest+2,code1,offtime,ontime);
	(void)getbittimes32(dest+2+32,code2,offtime,ontime);
	dest[2+32+32]=offtime;
	dest[2+32+32+1]=0x5ed*ticks;
	dest[2+32+32+2]=0x155*ticks;
	dest[2+32+32+3]=0x55*ticks;
	dest[2+32+32+4]=offtime;
	dest[2+32+32+5]=0;
} else if (n==6) {
	unsigned int code1,code2,code3;
	int ticks=29;
	unsigned int ontime=0x40*ticks,offtime=0x15*ticks;
	
	if (max<72) GOTOERROR;
	code1=_hexval1(str[0])*16+_hexval1(str[1]);
	code2=_hexval1(str[2])*16+_hexval1(str[3]);
	code3=_hexval1(str[4])*16+_hexval1(str[5]);
	dest[0]=0x155*ticks;
	dest[1]=0xaa*ticks;
	(void)getbittimes32(dest+2,code1,offtime,ontime);
	(void)getbittimes16(dest+2+32,code2,offtime,ontime);
	(void)getbittimes16(dest+2+48,code3,offtime,ontime);
	dest[2+32+32]=offtime;
	dest[2+32+32+1]=0x5ed*ticks;
	dest[2+32+32+2]=0x155*ticks;
	dest[2+32+32+3]=0x55*ticks;
	dest[2+32+32+4]=offtime;
	dest[2+32+32+5]=0;
} else if (n==8) {
	unsigned int code1,code2,code3,code4;
	int ticks=29;
	unsigned int ontime=0x40*ticks,offtime=0x15*ticks;
	
	if (max<72) GOTOERROR;
	code1=_hexval1(str[0])*16+_hexval1(str[1]);
	code2=_hexval1(str[2])*16+_hexval1(str[3]);
	code3=_hexval1(str[4])*16+_hexval1(str[5]);
	code4=_hexval1(str[6])*16+_hexval1(str[7]);
	dest[0]=0x155*ticks;
	dest[1]=0xaa*ticks;
	(void)getbittimes16(dest+2,code1,offtime,ontime);
	(void)getbittimes16(dest+2+16,code2,offtime,ontime);
	(void)getbittimes16(dest+2+32,code3,offtime,ontime);
	(void)getbittimes16(dest+2+48,code4,offtime,ontime);
	dest[2+32+32]=offtime;
	dest[2+32+32+1]=0x5ed*ticks;
	dest[2+32+32+2]=0x155*ticks;
	dest[2+32+32+3]=0x55*ticks;
	dest[2+32+32+4]=offtime;
	dest[2+32+32+5]=0;
} else GOTOERROR;

return 0;
error:
	return -1;
}

void print_ircodes(int *ircodes) {
printf("static int noname_ircode[]={");
while (1) {
	int i;
	i=*ircodes;
	if (!i) break;
	printf("%d,",i);
	ircodes++;
}
fputs("0};\n",stdout);
}

int main(int argc, char **argv) {
struct listen_udp listener;
struct ipv4address ipv4_dest,ipv4_listen;
unsigned int sequence=0;
unsigned int multiple=1;

clear_listen_udp(&listener);

if (argc<4) {
	struct command *command;
	fprintf(stdout,"Usage: irsender OUR_IP DEST_IP CMD [CMD] [CMD] ...\n");
	fprintf(stdout,"CMD: ipsearch, sequence");
	for (command=commands_global;command->name;command+=1) {
		fprintf(stdout,", %s",command->name);
	}
	fprintf(stdout,"\n");
	fprintf(stdout,"Example: irsender 192.168.1.9 192.168.1.255 ipsearch\n");
	fprintf(stdout,"Example: irsender 192.168.1.9 192.168.1.177 sequence down_volume down_volume optical\n");
	return 0;
}

{
	char *our_ip,*dest_ip;

	our_ip=argv[1];
	dest_ip=argv[2];

	if (init_ipv4address(&ipv4_dest,dest_ip,3800)) GOTOERROR;
	// voidinit_ipv4address(&ipv4_dest,192,168,1,177,3800);
	if (init_listen_udp(&listener,3801,3900)) GOTOERROR;
	if (init_ipv4address(&ipv4_listen,our_ip,listener.port)) GOTOERROR;
	// voidinit_ipv4address(&ipv4_listen,192,168,1,9,listener.port);
	// fprintf(stderr,"%s:%d listening on port %u\n",__FILE__,__LINE__,listener.port);
}

int ircodes80[80];
int argvi;
int needpad=0;
// for (argvi=3;argvi<argc;argvi++) {
argvi=3;
if (argvi<argc) while (1) {
	struct command *command;
	char *name;
	name=argv[argvi];

	if (!strcmp(name,"sequence")) {
		int fuse=10;
		while (1) {
			if (findsequence_irsender(&sequence,&ipv4_dest,&ipv4_listen,&listener)) GOTOERROR;
			if (sequence) {
				fprintf(stdout,"%s:%d sequence is %u\n",__FILE__,__LINE__,sequence);
				break;
			}
			fuse--;
			if (!fuse) GOTOERROR;
		}
	} else if (!strcmp(name,"ipsearch")) {
		if (ipsearch_irsender(&sequence,&ipv4_dest,&ipv4_listen,&listener)) GOTOERROR;
		if (sequence) {
			fprintf(stdout,"%s:%d ip is %u.%u.%u.%u, sequence is %u\n",__FILE__,__LINE__,
					ipv4_dest.ipv4[0], ipv4_dest.ipv4[1], ipv4_dest.ipv4[2], ipv4_dest.ipv4[3], sequence);
		}
	} else if (*name=='x') {
		multiple=atoi(name+1);
		if (multiple>10) multiple=10;
	} else if (!strncmp(name,"nec",3)) {
		unsigned int ui=multiple;
		if (nec_getircodes(ircodes80,80,name+3)) GOTOERROR;
		if (needpad) { usleep(1000*250); needpad=0; }
		while (1) {
			ui--;
			if (send_irsender(&sequence,&ipv4_dest,ircodes80,&ipv4_listen,sequence,&listener)) GOTOERROR;
			if (!ui) break;
			usleep(1000*250);
		}
		needpad=1;
	} else if (!strncmp(name,"printnec",8)) {
		if (nec_getircodes(ircodes80,80,name+8)) GOTOERROR;
		print_ircodes(ircodes80);
	} else {
		for (command=commands_global;command->name;command+=1) {
			if (strcmp(command->name,name)) continue;
			if (needpad) { usleep(1000*250); needpad=0; }
			{
				unsigned int ui=multiple;
				while (1) {
					int *ircodes;
					ircodes=command->ircodes;
					if ((!ircodes)&&(command->neccode)) {
						if (nec_getircodes(ircodes80,80,command->neccode)) GOTOERROR;
						ircodes=ircodes80;
					}
					if (!ircodes) GOTOERROR;
					if (send_irsender(&sequence,&ipv4_dest,ircodes,&ipv4_listen,sequence,&listener)) GOTOERROR;
					ui--;
					if (!ui) break;
					usleep(1000*250);
				}
			}
			needpad=1;
			break;
		}
		if (!command->name) {
			fprintf(stderr,"Command not found: %s\n",name);
		}
	}
	argvi++;
	if (argvi==argc) break;
}

deinit_listen_udp(&listener);
return 0;
error:
	deinit_listen_udp(&listener);
	return -1;
}
