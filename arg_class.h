#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include "hash_list.h"

/**
 * @file arg_class.h
 *
 * @brief Archivo que define la clase Args
 */

/**
 * @brief Clase para manejar los argumentos pasados por el usuario al programa.
 *
 */
class Args {
public:
    unsigned short abbrv_len = 12; ///< Valor default en el kernel up-to 04/2025
    std::string repo_path;
    const char *cmd;
    std::vector<std::string> args;
    bool print_abbrv = false; ///< Por default imprimimos los hash completos

    Args(int argc, char *argv[]);
    int run_cmd();
    void usage();
};
