#include <print>
#include <vector>
#include <numeric>
#include <cmath>
#include <git2.h>

const size_t MAX_BUF_SIZE = 65536;
const size_t MIN_BUF_SIZE = 64;

void print_hash(git_oid oid);
void print_short_hash(git_oid oid, unsigned char len);
size_t get_buffer_size(size_t len);
