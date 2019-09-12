
//void pkt_handler(u_char *user, const struct pcap_pkthdr *pkt_header, const u_char *pkt_data);

namespace  capture{

#define TYPEMAC_IP	0x08
#define TYPEIP_UDP	0x11
#define TYPEIP_TCP	0x06
#define TYPEIP_ICMP 0x01

#pragma pack(1)
typedef struct mac_address{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
    u_char byte5;
    u_char byte6;
} mac_address;

#pragma pack(1)
/* 4 bytes IP address */
typedef struct ip_address{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
}ip_address;

//typedef struct ptype
//{
//    u_char byte1;
//    u_char byte2;
//} ptype;
#pragma pack(1)
typedef struct mac_header{
	mac_address src;
	mac_address dst;
	u_short type;
}mac_header;

#pragma pack(1)
/* IPv4 header */
typedef struct ip_header{
    u_char  ver_ihl;        // Version (4 bits) + Internet header length (4 bits)
    u_char  tos;            // Type of service 
    u_short tlen;           // Total length 
    u_short identification; // Identification
    u_short flags_fo;       // Flags (3 bits) + Fragment offset (13 bits)
    u_char  ttl;            // Time to live
    u_char  proto;          // Protocol
    u_short crc;            // Header checksum
    //ip_address  saddr;      // Source address
    //ip_address  daddr;      // Destination address
    u_int  saddr;      // Source address
    u_int  daddr;      // Destination address
	u_int   op_pad;         // Option + Padding
}ip_header;

#pragma pack(2)
/* UDP header*/
typedef struct udp_header{
    u_short sport;          // Source port
    u_short dport;          // Destination port
    u_short len;            // Datagram length
    u_short crc;            // Checksum
}udp_header;

#pragma pack(1)
typedef struct tcp_header { 
	u_short sport; 	// Source port 
	u_short dport; 	// Destination port 
	u_int seqnum; 	// Sequence Number 
	u_int acknum; 	// Acknowledgement number 
	u_char th_off; 	// Header length 
	u_char flags; 	// packet flags 
	u_short win; 	// Window size 
	u_short crc; 	// Header Checksum 
	u_short urgptr; // Urgent pointer...still don't know what this is...
}tcp_header; 
//http://en.wikipedia.org/wiki/Tcphdr
//struct tcphdr {
//	unsigned short source;
//	unsigned short dest;
//	unsigned long seq;
//	unsigned long ack_seq;	
//        #  if __BYTE_ORDER == __LITTLE_ENDIAN
//        unsigned short res1:4;
//        unsigned short doff:4;
//        unsigned short fin:1;
//        unsigned short syn:1;
//        unsigned short rst:1;
//        unsigned short psh:1;
//        unsigned short ack:1;
//        unsigned short urg:1;
//        unsigned short res2:2;
//        #  elif __BYTE_ORDER == __BIG_ENDIAN
//        unsigned short doff:4;
//        unsigned short res1:4;
//        unsigned short res2:2;
//        unsigned short urg:1;
//        unsigned short ack:1;
//        unsigned short psh:1;
//        unsigned short rst:1;
//        unsigned short syn:1;
//        unsigned short fin:1;
//        #  endif
//	unsigned short window;	
//	unsigned short check;
//	unsigned short urg_ptr;
//};




}