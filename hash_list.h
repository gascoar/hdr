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

void hd_loop(std::vector<git_oid> &hl, unsigned int in_pos, unsigned int step,
             unsigned int abbrv_len);
void filter1(unsigned char hd, std::vector<unsigned char> &buf, size_t idx, size_t end);
void cmp_loop(std::vector<unsigned long> &cuentas, std::vector<git_oid> &hl, size_t in_pos,
              size_t step, unsigned int abbrv_len);
void per_thread_hamming(std::vector<git_oid> &hl, size_t stp, size_t ipos, size_t chunk_size,
                        unsigned int alen, void (*proc_fun)(std::vector<unsigned char> &));

/**
 * @brief Clase que contiene los metodos y miembros necesarios para interactuar
 * con un repositorio de git.
 */
class HashList {
public:
    git_repository *repo; ///< Puntero a un objeto del tipo git_repository (ver libgit2 API)
    git_oid first_oid; ///< Primer objeto git_oid, necesario para iniciar el walk sobre el repositorio.
    git_revwalk *walker = NULL; ///< Puntero a un objeto git_revwalk (ver libgit2 API)
    std::vector<git_oid> hash_list; ///< Vector donde se guarda la lista de hashes en formato git_oid.
    unsigned int abbrv_len; ///< Largo abreviado de los hashes.

    /**
     * @brief Constructor default de HashList
     *
     * @param repo_path: path del repositorio de git (SHA-1)
     * @param alen largo abreviado de los hash.
     */
    HashList(std::string repo_path, unsigned int alen) {
        const char *rp = repo_path.c_str();
        abbrv_len = alen;

        if (git_libgit2_init() < 0) {
            throw std::runtime_error("Failed to initialize libgit2");
        }
        if (git_repository_open(&repo, rp) != 0) {
            throw std::runtime_error("Failed to open repository");
        }
        if (git_reference_name_to_id(&first_oid, repo, "HEAD") != 0) {
            throw std::runtime_error("Error getting first git_oid from HEAD");
        };
    }

    /**
     * @brief Metodo destructor de HashList
     */
    ~HashList() {
        git_repository_free(this->repo);
        /*
         * Si no se inicio el walker con init_and_walk(), walker es NULL
         */
        if (walker)
            git_revwalk_free(this->walker);
        git_libgit2_shutdown();
    }

    /**
     * @brief Obtiene la rama del repositorio
     *
     * @return Nombre de la rama como std::string
     */
    std::string get_current_branch() {
        git_reference *head = nullptr;
        if (git_repository_head(&head, this->repo) != 0) {
            throw std::runtime_error("Failed to get HEAD reference");
        }

        const char *branch_name;
        if (git_branch_name(&branch_name, head) != 0) {
            git_reference_free(head);
            throw std::runtime_error("No branch found");
        }
        std::string branch(branch_name);
        git_reference_free(head);

        return branch;
    }

    /**
     * @brief Inicia el walker y establece el orden en el que se leera el repo.
     *
     */
    void init_walker() {
        git_revwalk *walker;

        if (git_revwalk_new(&walker, this->repo) != 0) {
            throw std::runtime_error("Error allocating revwalk");
        }
        if (git_revwalk_sorting(walker,  GIT_SORT_TOPOLOGICAL) != 0) {
            throw std::runtime_error("Error setting up revwalk sorting");
        };

        if (git_revwalk_push(walker, &this->first_oid) != 0) {
            throw std::runtime_error("revwalk: Error pushing initial commit");
        };

        this->walker = walker;
    }

    /**
     * @brief Recorre todo el repo y guarda los hashes en el vector hash_list de la instancia.
     */
    int revwalking() {
        git_oid oid;

        while ((git_revwalk_next(&oid, this->walker)) == 0) {
            this->hash_list.push_back(oid);
        }

        return 0;
    }

    /**
     * @brief Inicializa y recorre todo el repo guardando los hashes en el vector hash_list de la instancia.
     */
    void init_and_walk() {
        this->init_walker();
        this->revwalking();
    }

    /**
     * @brief Imprime todos los hashes en stdout.
     */
    void print_hashes(bool print_abbrv) {
        char buf[GIT_OID_SHA1_HEXSIZE + 1];
        this->init_and_walk();

        for (long unsigned int i = 0; i < this->hash_list.size(); i++) {
            git_oid oid = this->hash_list[i];
            if (git_oid_fmt(buf, &oid) != 0) {
                throw std::runtime_error("print_hashes: error formatting git_oid");
            };
            buf[GIT_OID_SHA1_HEXSIZE] = '\0';
            if (print_abbrv) {
                std::string_view sv(buf, 2 * this->abbrv_len);
                std::println("{}", sv);
            }
            else {
                std::println("{}", buf);
            }
        }
    }

    void repo_stats() {
        this->init_and_walk();
        std::println("- Commits: {}", this->hash_list.size());
    }

    void hamming_calc(void (*proc_fun)(std::vector<unsigned char> &)) {
        unsigned int nthreads = std::thread::hardware_concurrency();
        std::vector<std::thread> t;
        t.reserve(nthreads);
        size_t len = this->hash_list.size();

        this->init_and_walk();
        size_t chunk_size = get_buffer_size(len);
        for (size_t i = 0; i < nthreads; i++) {
            t.push_back(std::thread(per_thread_hamming, std::ref(this->hash_list), nthreads, i,
                        chunk_size, this->abbrv_len, proc_fun));
        }

        for (size_t i = 0; i < nthreads; i++) {
            t.at(i).join();
        }
    }

    void histogram_calc() {
        std::vector<unsigned long> cuentas(BITS_PER_SHA, 0);
        size_t nthreads = std::thread::hardware_concurrency();
        std::vector<std::thread> t;
        t.reserve(nthreads);
        std::vector<std::vector<unsigned long>> res_v;
        /*
         * TODOs:
         *  - add check if walker is not initialized?
         *  - add check of hash_list len?
         */
        this->init_and_walk();

        for (size_t i = 0; i < nthreads; i++) {
            res_v.push_back(std::vector<unsigned long>(BITS_PER_SHA, 0));
        }

        try {
            for (size_t i = 0; i < nthreads; i++) {
                t.push_back(std::thread(cmp_loop, std::ref(res_v[i]), std::ref(this->hash_list),
                            i, nthreads, this->abbrv_len));
            }

            for (size_t i = 0; i < nthreads; i++) {
                t[i].join();
            }
        } catch (const std::exception& e) {
            std::cerr << "Thread error: " << e.what() << std::endl;
        }

        for (size_t i = 0; i < nthreads; i++ ) {
            for (size_t j = 0; j < BITS_PER_SHA; j++) {
                cuentas[j] = cuentas[j] + res_v[i][j];
            }
        }

        for (size_t i = 0; i < BITS_PER_SHA; i++) {
            std::println("{},{}", i, cuentas[i]);
        }
    }
};

void per_thread_hamming(std::vector<git_oid> &hl, size_t stp, size_t ipos, size_t chunk_size,
                        unsigned int alen, void (*proc_fun)(std::vector<unsigned char> &)) {
    std::vector<unsigned char> buf;
    buf.reserve(chunk_size);
    HDGen gen(stp, ipos, chunk_size, alen, hl);

    while (gen.get_chunk(buf)) {
        proc_fun(buf);
        buf.clear();
    }
    if (buf.size() != 0) {
        proc_fun(buf);
        buf.clear();
    }
}

void cmp_loop(std::vector<unsigned long> &cuentas, std::vector<git_oid> &hl, size_t in_pos,
              size_t step, unsigned int abbrv_len) {
    size_t len = hl.size();
    for (size_t i = in_pos; i < len - 1; i = i + step) {
        for (size_t j = i + 1; j < len; j++) {
            unsigned char hd = hamming_distance(hl[i], hl[j], abbrv_len);
            cuentas[hd]++;
        }
    }
}
