#include <print>

unsigned char how_many_ones_in_a_byte(unsigned char d) {
    unsigned char ones = 0;

    for  (int i = 0; i < 8; i++) {
            ones = ones + ((d >> i) & 0x01);
    }

    return ones;
}

/*
 * hamming_distance()
 *
 * Devuelve la distancia de hamming entre dos objetos del tipo git_oid
 *
 */
unsigned char hamming_distance(git_oid oid1, git_oid oid2, unsigned int abbrv_len) {
    unsigned char ret = 0;

    for (unsigned int i = 0; i < abbrv_len; i++) {
        unsigned char tmp = oid1.id[i] ^ oid2.id[i];
        ret = ret + how_many_ones_in_a_byte(tmp);
    }

    return ret;
}
