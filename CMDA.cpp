#include "CMDA.h"

//todo: получше ознакомиться с CMDA

void CDMA::generate_gold_sequence(int user_num) { //генерация золотой последовательности для каждого пользователя
    bitarr x1, x2, c1, c2, seq1, seq2;
    x1.set(user_num);
    x2.set(user_num);
    int bit1, bit2;
    for (int i = 0; i < N; i++) { //генерация последовательности для первого генератора
        bit1 = x1[N - 1] ^ x1[1]; //Применение операции XOR к двум битам генератора
        bit2 = x2[N - 1] ^ x2[2]; //Применение операции XOR к двум битам генератора
        seq1[N - i - 1] = bit1; //Добавление бита в последовательность
        seq2[N - i - 1] = bit2; //Добавление бита в последовательность
        c1[i] = x1[0] ^ x1[1] ^ x1[2] ^ x1[3] ^ x1[4] ^ x1[6]; //Генерация управляющего бита 1
        c2[i] = x2[0] ^ x2[1] ^ x2[2] ^ x2[3] ^ x2[4] ^ x2[6]; //Генерация управляющего бита 2
        x1 >>= 1; //Сдвиг регистра на 1 бит вправо
        x1[5] = bit1; //Добавление нового бита
        x2 >>= 1; //Сдвиг регистра на 1 бит вправо
        x2[5] = bit2; //Добавление нового бита
    }
    gold_sequence = seq1 ^ seq2; //Формирование золотой последовательности
}

void CDMA::add_user() { //добавление нового пользователя
    int user_num = users.size();
    bitarr packet;
    packet.set(); //установка всех битов в 1, чтобы при XOR получить нулевой бит
    for (int i = 0; i < N; i++) {
        packet[i] = packet[i] ^ gold_sequence[i]; //первое шифрование пакета
    }
    users.push_back(packet); //добавление нового пользователя в массив
}

bitarr CDMA::encode_packet(bitarr packet) { //шифрование пакета
    bitarr result;
    result.reset();
    for (int i = 0; i < users.size(); i++) { //шифрование пакета для каждого пользователя
        for (int j = 0; j < N; j++) {
            result[j] = result[j] ^ packet[i] ^ users[i][j]; //шифрование пакета XOR с пользовательским ключом
        }
    }
    return result;
}

bitarr CDMA::decode_packet(bitarr packet) { //дешифрование пакета
    bitarr result = packet;
    for (int i = 0; i < users.size(); i++) { //дешифрование пакета для каждого пользователя
        for (int j = 0; j < N; j++) {
            result[i] = result[i] ^ users[i][j]; //дешифрование пакета с пользовательским ключом
        }
    }
    return result;
}