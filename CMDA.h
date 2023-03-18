#include <iostream>
#include <vector>
#include <bitset>

#define N 1023 //����� ������������ ������������������ �����

using namespace std;
typedef bitset<N> bitarr;

class CDMA {
public:
    vector<bitarr> users; //������ �������������
    bitarr gold_sequence; //������� ������������������
    void generate_gold_sequence(int user_num); //��������� ������� ������������������
    void add_user(); //���������� ������ ������������
    bitarr encode_packet(bitarr packet); //���������� IP ������
    bitarr decode_packet(bitarr packet); //������������ IP ������
};