#include <iostream>
#include <vector>
#include <bitset>

#define N 1023 //длина генерируемой последовательности √олда

using namespace std;
typedef bitset<N> bitarr;

class CDMA {
public:
    vector<bitarr> users; //массив пользователей
    bitarr gold_sequence; //золота€ последовательность
    void generate_gold_sequence(int user_num); //генераци€ золотой последовательности
    void add_user(); //добавление нового пользовател€
    bitarr encode_packet(bitarr packet); //шифрование IP пакета
    bitarr decode_packet(bitarr packet); //дешифрование IP пакета
};