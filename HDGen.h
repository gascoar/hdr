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

HDGen::HDGen(size_t stp, size_t in_pos, size_t chunk_size, unsigned int alen,
             std::vector<git_oid> &hash_list) {
    step = stp;
    outer_pos = in_pos;
    inner_pos = outer_pos + 1;
    chunk_len = chunk_size;
    hl = hash_list;
    abbrv_len = alen;
    endpos = hl.size();
}

bool HDGen::get_chunk(std::vector<unsigned char> &buf) {
    size_t k = 0;

    while (outer_pos < endpos - 1) {
        while (inner_pos < endpos) {
            unsigned char hd = hamming_distance(hl.at(outer_pos), hl.at(inner_pos), abbrv_len);
            buf.push_back(hd);
            k++;
            inner_pos++;
            if (k == chunk_len)
                return true;
        }
        outer_pos = outer_pos + step;
        inner_pos = outer_pos + 1;
    }
    return false;
}
