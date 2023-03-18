// ip_packet_generator.cpp: определяет точку входа для приложения.
//


//todo: реализовать протокол передачи оптической информации
//todo: доделать UDP протокол для ip пакетов
//todo: написать API для подводного аппарата для передачи акустических и оптических данных 

#pragma comment(lib, "Ws2_32.lib")

#define SIO_RCVALL 0x98000001
#define MAX_PACKET_SIZE 0x10000

#define uint8 unsigned char
#define uint16 unsigned int
#include "ip_packet_generator.h"

using namespace std;

class ip_packet
{
	//todo: 
private:
	uint8 ver = 0x04;
	uint8 h_length = 0x00;
	uint8 tos = 0x00;
	uint16 len = 0x0000;
	uint16 id = 0x0000;
	uint8 flags = 0b000;
	uint16 f_offset = 0x0000;
	uint8 ttl = 0x00;
	uint8 protocol = 0x00;
	uint16 checksumm = 0x0000;

	uint8 ip_src[4] = { 200, 200, 0, 1 };
	uint8 ip_dest[4] = { 178,200,0,55 };
	string ip_src_str = iparr_to_str(ip_src);
	string ip_dest_str = iparr_to_str(ip_src);

	string DATA = "Hey-hey-heeeey!";
public:

	string iparr_to_str(unsigned char int_ip[])
	{
		string ip = "";
		for (int i = 0; i < 4; i++)
		{
			ip += to_string(int_ip[i]);
			if (i < 3)
				ip += ".";
		}
		return ip;
	}

	string header()
	{
		return to_string(this->ver) +
			to_string(this->h_length) +
			to_string(this->tos) +
			to_string(this->len) +
			to_string(this->id) +
			to_string(this->flags) +
			to_string(this->f_offset) +
			to_string(this->ttl) +
			this->ip_src_str + this->ip_dest_str;
	}

	void ShowIPFields()
	{
		printf("version and length: %u\t%u\n", this->ver, this->len);
		printf("type of service %u\n", this->tos);
		printf("length of packet: %hu\n", this->len);
		printf("id = %hu\n", this->id);
		printf("flags and offset: %hu\t%hu\n", this->flags,this->f_offset);
		printf("ttl = %u\n", this->ttl);
		printf("protocol = %u\n", this->protocol);
		printf("crc32: %hu\n", this->checksumm);
		printf("src = %u.%u.%u.%u\n", this->ip_src[0], this->ip_src[1], this->ip_src[2], this->ip_src[3]);
		printf("dst = %u.%u.%u.%u\n", this->ip_dest[0], this->ip_dest[1], this->ip_dest[2], this->ip_dest[3]);
	}
	
	void ShowIPData()
	{
		cout << "data = " << this->DATA << "\n";
	}

	void setData(string data)
	{
		this->DATA = data;
	}

	string getData()
	{
		return this->DATA;
	}

	bitarr ipPacket_bin()
	{
		bitarr a;
		string ip_data = this->header() + this->getData();
		std::string str = ip_data;
		for (char const& c : str) {
			std::cout << std::bitset<8>(c) << ' ';
		}
		return a;
	}
};

int main()
{
	CDMA cdma;
	cdma.generate_gold_sequence(0);
	cdma.add_user();
	ip_packet a;
	bitarr packet = a.ipPacket_bin();
	packet.set(); //установка всех битов в 1, чтобы при XOR получить нулевой бит
	bitarr encrypted_packet = cdma.encode_packet(packet); //шифрование IP пакета
	bitarr decrypted_packet = cdma.decode_packet(encrypted_packet); //дешифрование IP пакета

	return 0;
}