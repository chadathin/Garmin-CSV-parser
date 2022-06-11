#include "parselib.h"

int main(int argc, char *argv[]) {
    // Expects two CL args: .csv filename and lthr
    if (argc != 3 || atoi(argv[2]) == 0) {
        WrongArg();
        exit(1);
    }

    



    return 0;
}