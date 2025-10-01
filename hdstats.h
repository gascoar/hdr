#include <vector>
#include <print>

class HDStats {
    unsigned char min;
    unsigned char max;
    double mean;

public:
    HDStats(unsigned char mi, unsigned char ma, double avg);
    HDStats(std::vector<unsigned char> &vec);
    void print();
};

double mean_of_vec(const std::vector<unsigned char> &data);
double variance(const std::vector<unsigned char> &data, double mean);
unsigned char min_of_vec(std::vector<unsigned char> &vec);
unsigned char max_of_vec(std::vector<unsigned char> &vec);
void print_buf(std::vector<unsigned char> &buf);
void hd_stats(std::vector<unsigned char> &buf);
