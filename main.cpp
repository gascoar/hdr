#include "hash_list.h"
#include "arg_class.h"

int main(int argc, char *argv[]) {
    int ret;

    Args args(argc, argv);
    ret = args.run_cmd();

    return ret;
}
