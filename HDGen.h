#include <vector>
#include <git2.h>
#include "hamming.h"

/**
 * @file HDGen.h
 * @brief Archivo de definición de clase HDGen y métodos asociados.
 * @author Gaston Gonzalez (gascoar@gmail.com)
 */
class HDGen {
private:
    size_t step;
    size_t outer_pos;
    size_t inner_pos;
    size_t chunk_len;
    size_t endpos;
    unsigned int abbrv_len;
    std::vector<git_oid> hl;
public:
    HDGen(size_t stp, size_t current, size_t chunk_size, unsigned int alen,
          std::vector<git_oid> &dat);
    bool get_chunk(std::vector<unsigned char> &buf);
};
