#include "CMDA.h"

//todo: ������� ������������ � CMDA

void CDMA::generate_gold_sequence(int user_num) { //��������� ������� ������������������ ��� ������� ������������
    bitarr x1, x2, c1, c2, seq1, seq2;
    x1.set(user_num);
    x2.set(user_num);
    int bit1, bit2;
    for (int i = 0; i < N; i++) { //��������� ������������������ ��� ������� ����������
        bit1 = x1[N - 1] ^ x1[1]; //���������� �������� XOR � ���� ����� ����������
        bit2 = x2[N - 1] ^ x2[2]; //���������� �������� XOR � ���� ����� ����������
        seq1[N - i - 1] = bit1; //���������� ���� � ������������������
        seq2[N - i - 1] = bit2; //���������� ���� � ������������������
        c1[i] = x1[0] ^ x1[1] ^ x1[2] ^ x1[3] ^ x1[4] ^ x1[6]; //��������� ������������ ���� 1
        c2[i] = x2[0] ^ x2[1] ^ x2[2] ^ x2[3] ^ x2[4] ^ x2[6]; //��������� ������������ ���� 2
        x1 >>= 1; //����� �������� �� 1 ��� ������
        x1[5] = bit1; //���������� ������ ����
        x2 >>= 1; //����� �������� �� 1 ��� ������
        x2[5] = bit2; //���������� ������ ����
    }
    gold_sequence = seq1 ^ seq2; //������������ ������� ������������������
}

void CDMA::add_user() { //���������� ������ ������������
    int user_num = users.size();
    bitarr packet;
    packet.set(); //��������� ���� ����� � 1, ����� ��� XOR �������� ������� ���
    for (int i = 0; i < N; i++) {
        packet[i] = packet[i] ^ gold_sequence[i]; //������ ���������� ������
    }
    users.push_back(packet); //���������� ������ ������������ � ������
}

bitarr CDMA::encode_packet(bitarr packet) { //���������� ������
    bitarr result;
    result.reset();
    for (int i = 0; i < users.size(); i++) { //���������� ������ ��� ������� ������������
        for (int j = 0; j < N; j++) {
            result[j] = result[j] ^ packet[i] ^ users[i][j]; //���������� ������ XOR � ���������������� ������
        }
    }
    return result;
}

bitarr CDMA::decode_packet(bitarr packet) { //������������ ������
    bitarr result = packet;
    for (int i = 0; i < users.size(); i++) { //������������ ������ ��� ������� ������������
        for (int j = 0; j < N; j++) {
            result[i] = result[i] ^ users[i][j]; //������������ ������ � ���������������� ������
        }
    }
    return result;
}