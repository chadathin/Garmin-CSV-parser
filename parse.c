#include "parselib.h"
#include "actstr.h"


int main(int argc, char *argv[]) {

    FILE *in; 
    int lthr = -1;
    int lines;

    // Expects two CL args: .csv filename and lthr
    if (argc != 3 || ((lthr = atoi(argv[2])) == 0)) {
        WrongArg();
        exit(1);
    }

    // Make sure at least a POSITIVE number is entered
    if (lthr < 1) {
        WrongArg();
        exit(1);
    }

    // open activities file
    if ((in = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s:%s\n", argv[1], strerror(errno));
        fflush(stderr);
        exit(2);
    }

    lines = count_lines(argv[1]);
    // printf("%d\n", lines);

    

    fclose(in);

    return 0;
}