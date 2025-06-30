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

    if (strcmp(cmd, "help") == 0) {
        usage();
    } else if (strcmp(cmd, "stats") == 0) {
        HashList hl(repo_path, abbrv_len);
        hl.repo_stats();
    } else if (strcmp(cmd, "print") == 0) {
        HashList hl(repo_path, abbrv_len);
        hl.print_hashes(print_abbrv);
    } else if (strcmp(cmd, "hist") == 0) {
        HashList hl(repo_path,  abbrv_len);
        hl.histogram_calc();
    } else if (strcmp(cmd, "hd") == 0) {
        HashList hl(repo_path, abbrv_len);
        hl.hamming_calc(print_buf);
    } else if (strcmp(cmd, "hdstats") == 0) {
        HashList hl(repo_path, abbrv_len);
        hl.hamming_calc(hd_stats);
    } else if (strcmp(cmd, "branch") == 0) {
        HashList hl(repo_path, abbrv_len);
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
    std::println("\nHash Analyzer\n");
    std::println("Uso: hash_analzer [commit inicial] [cmd] [abbrev len]\n");
    std::println("cmd:");
}
/*    else if (strcmp(cmd, "print") == 0)
        hl.print_hashes();
    else if (strcmp(cmd, "hd") == 0)
        hl.hamming_calc();
    else if (strcmp(cmd, "hist") == 0)
        hl.histogram_calc();
    else {
        hl.hamming_calc();
    }
    if (argc < 3) {
        std::cerr << "Error: some argument is missing." << std::endl;
        usage();

        return -1;
    }
*/


