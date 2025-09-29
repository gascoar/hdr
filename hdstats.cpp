double mean_of_vec(const std::vector<unsigned char> &data) {
    unsigned long long sum = 0;
    size_t len = data.size();

    for (size_t i = 0; i < len; i++) {
        sum = sum + data.at(i);
    }
    return static_cast<double>(sum) / len;
}

double variance(const std::vector<unsigned char> &data, double mean) {
    double var = 0.0;
    size_t len = data.size();

    for (size_t i = 0; i < len; i++) {

        var = var +  (data.at(i) - mean) * (data.at(i) - mean);
    }
    return var / len;
}

unsigned char min_of_vec(std::vector<unsigned char> &vec) {
    return *min_element(vec.begin(), vec.end());
}

unsigned char max_of_vec(std::vector<unsigned char> &vec) {
    return *max_element(vec.begin(), vec.end());
}

void print_buf(std::vector<unsigned char> &buf) {
    for (size_t i = 0; i < buf.size(); i++) {
        std::println("{}", buf.at(i));
    }
}

class HDStats {
    unsigned char min;
    unsigned char max;
    double mean;

public:
    HDStats(unsigned char mi, unsigned char ma, double avg);
    HDStats(std::vector<unsigned char> &vec);
    void print();
};

void hd_stats(std::vector<unsigned char> &buf) {
    HDStats hds(buf);
    hds.print();
}

HDStats::HDStats(unsigned char mi, unsigned char ma, double avg) {
    min = mi;
    max = ma;
    mean = avg;
}

HDStats::HDStats(std::vector<unsigned char> &vec) {
    min = min_of_vec(vec);
    max = max_of_vec(vec);
    mean = mean_of_vec(vec);
}

void HDStats::print() {
    std::println("{},{},{:.2f}", min, max, mean);
}
