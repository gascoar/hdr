/**
 * @file hash_list.h
 * @brief Archivo de definición de clase HashList y métodos asociados.
 * @author Gaston Gonzalez (gascoar@gmail.com)
 */
#include <print>
#include <git2.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <thread>
#include <cstring>
#include "utils.h"
#include "hamming.h"
#include "HDGen.h"
#include "hdstats.h"

const unsigned int BITS_PER_SHA = 160;
const unsigned int HEX_SYMBOLS_PER_SHA = 40;

void filter1(unsigned char hd, std::vector<unsigned char> &buf, size_t idx, size_t end);
void cmp_loop(std::vector<unsigned long> &cuentas, std::vector<git_oid> &hl, size_t in_pos,
              size_t step, unsigned int abbrv_len);
void per_thread_hamming(std::vector<git_oid> &hl, size_t stp, size_t ipos, size_t chunk_size,
                        unsigned int alen, void (*proc_fun)(std::vector<unsigned char> &));

/**
 * @brief Clase que contiene los metodos y miembros necesarios para interactuar
 *
 */
class HashList {
public:
    git_repository *repo; ///< Puntero a un objeto del tipo git_repository (ver libgit2 API)
    git_oid first_oid; ///< Primer objeto git_oid, necesario para iniciar el walk sobre el repositorio.
    git_revwalk *walker = NULL; ///< Puntero a un objeto git_revwalk (ver libgit2 API)
    std::vector<git_oid> hash_list; ///< Vector donde se guarda la lista de hashes en formato git_oid.
    unsigned int abbrv_len; ///< Largo abreviado de los hashes.
    
    HashList(std::string repo_path, unsigned int alen);
    ~HashList();
    std::string get_current_branch();
    void init_walker();
    int revwalking();
    void init_and_walk();
    void print_hashes(bool print_abbrv);
    void repo_stats();
    void hamming_calc(void (*proc_fun)(std::vector<unsigned char> &));
    void histogram_calc();
};

