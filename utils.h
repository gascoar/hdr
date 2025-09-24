#include <print>
#include <vector>
#include <numeric>
#include <cmath>

const size_t MAX_BUF_SIZE = 65536;
const size_t MIN_BUF_SIZE = 64;

void print_hash(git_oid oid) {
    char buf[GIT_OID_SHA1_HEXSIZE + 1];
    if (git_oid_fmt(buf, &oid) != 0) {
        throw std::runtime_error("print_hashes: error formatting git_oid");
    };

    buf[GIT_OID_SHA1_HEXSIZE] = '\0';

    std::println("{}", buf);
}

void print_short_hash(git_oid oid, unsigned char len) {
    char buf[GIT_OID_SHA1_HEXSIZE + 1];
    if (git_oid_fmt(buf, &oid) != 0) {
        throw std::runtime_error("print_hashes: error formatting git_oid");
    };
    buf[GIT_OID_SHA1_HEXSIZE] = '\0';

    std::string_view v = std::string_view(buf).substr(0, len);

    std::println("{}", v);
}

/*
 *
 * TODO: lo unico que hace esta funcion es establecer un maximo de tamaño de
 * buffer y, por otro lado, garantizar que el buffer sea potencia de dos.
 */
size_t get_buffer_size(size_t len) {
    int n = 0;
    size_t ret = 1;

    if (len > MAX_BUF_SIZE)
        return MAX_BUF_SIZE;
    else if (len < MIN_BUF_SIZE)
        return MIN_BUF_SIZE;

    n = static_cast<int>(log2(len));
    std::println("{}", n);
    for (int i = 1; i < n + 1; i++) {
        ret = 2 * ret;
    }

    return ret;
}
