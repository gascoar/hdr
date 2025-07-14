#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

class Args {
public:
    unsigned short abbrv_len = 12; // Valor default en el kernel up-to 04/2025
    std::string repo_path;
    const char *cmd;
    std::vector<std::string> args;
    bool print_abbrv = false; // Por default imprimimos los hash completos
    int run_cmd();
    void usage();

    Args (int argc, char *argv[]) {
        std::vector<std::string> args(argv, argv + argc);
        args = args;
        repo_path = std::filesystem::current_path().string();

        if (argc == 1) {
            cmd = "help";
        } else {
            cmd = args[1].c_str();
        }

        auto it = std::find(args.begin(), args.end(), "--alen");
        if (it != args.end()) {
            it++;
            abbrv_len = stoul(*it);
            print_abbrv = true;
        }
    }
};

int Args::run_cmd() {
    int ret = 0;
    HashList hl(repo_path, abbrv_len);

    if (strcmp(cmd, "help") == 0) {
        usage();
    } else if (strcmp(cmd, "stats") == 0) {
        hl.repo_stats();
    } else if (strcmp(cmd, "print") == 0) {
        hl.print_hashes(print_abbrv);
    } else if (strcmp(cmd, "hist") == 0) {
        hl.histogram_calc();
    } else if (strcmp(cmd, "hd") == 0) {
        hl.hamming_calc(print_buf);
    } else if (strcmp(cmd, "hdstats") == 0) {
        hl.hamming_calc(hd_stats);
    } else if (strcmp(cmd, "branch") == 0) {
        std::string branch = hl.get_current_branch();
        std::println("{}", branch);
    } else {
        std::println(stderr, "Command '{}' not found!", cmd);
        std::print("");
        usage();
        ret = -1;
    }

    return ret;
}

void Args::usage(void) {
   
    std::string usage = "\nhdr\n"
        "Uso: hdr cmd [--alen val]\n\n"
        "$ cd <repo>\n\n"
        "Obtener distancias de Hamming:\n"
        "$ hdr hd [--alen <val>]\n\n"
        "Obtener histograma:\n"
        "$ hdr hist [--alen <val>]\n\n"
        "Obtener minimo, maximo y valor medio:\n"
        "$ hdr hdstats [--alen <val>]\n\n";

    std::println("{}", usage);
}
