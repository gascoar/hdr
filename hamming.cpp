#include "hamming.h"

unsigned char how_many_ones(unsigned char d, unsigned char len) {
    unsigned char ones = 0;

    for  (int i = 0; i < len; i++) {
            ones = ones + ((d >> i) & 0x01);
    }

    return ones;
}

/**
 * @brief
 * @param oid1: primer de los dos objetos del tipo git_oid entre los que se evaluará la distancia de Hamming.
 * @param oid2: segundo de los dos objetos del tipo git_oid entre los que se evaluará la distancia de Hamming.
 * @param abbrv_len: largo en hex del Hash abreviado a evaluar.
 * @return Devuelve la distancia de hamming entre dos objetos del tipo git_oid
 */
unsigned char hamming_distance(git_oid oid1, git_oid oid2, unsigned int abbrv_len) {
    unsigned char ret = 0;

    /*
     * TODO: handle 'terminate called recursively'
     */
    if ((abbrv_len > 40) || (abbrv_len) <= 0)
        throw std::runtime_error("hamming: short length must be a number between 0 and 40");

    unsigned char bytes = abbrv_len / 2;
    unsigned char r = abbrv_len % 2;

    for (unsigned int i = 0; i < bytes; i++) {
        unsigned char tmp = oid1.id[i] ^ oid2.id[i];
        ret = ret + how_many_ones(tmp, BYTE_LEN);
    }

    if (r) {
        int pos = bytes;
        unsigned char tmp = (oid1.id[pos] & 0xF0) ^ (oid2.id[pos] & 0xF0);
        tmp = tmp >> 4;
        ret = ret + how_many_ones(tmp, HALF_BYTE_LEN);
    }

    return ret;
}
