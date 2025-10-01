#ifndef HAMMING
#define HAMMING
/**
 * @file hamming.h
 * @brief Archivo de definición de funciones para evualuación de distancias de Hamming.
 * @author Gaston Gonzalez (gascoar@gmail.com)
 */
#include <print>
#include <git2.h>

const unsigned char BYTE_LEN = 8;
const unsigned char HALF_BYTE_LEN = 4;


unsigned char how_many_ones(unsigned char d, unsigned char len);
unsigned char hamming_distance(git_oid oid1, git_oid oid2, unsigned int abbrv_len);
#endif
