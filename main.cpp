#include "arg_class.h"
#include <git2.h>

/**
 * @file main.cpp
 *
 * @brief Archivo principal del proyecto: crea una instancia de la clase Args y
 * ejecuta un comando (método de la clase Args)
 *
 */
int main(int argc, char *argv[]) {
   int ret;

   Args args(argc, argv);
   ret = args.run_cmd();

   return ret;
}
