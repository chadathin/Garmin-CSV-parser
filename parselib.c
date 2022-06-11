#include "parselib.h"

void WrongArg() {
    errno = EINVAL;
    fprintf(stderr, "%s: Expects './parse [activity].csv [lthr]'\n", strerror(errno));
    fflush(stderr);
}

int count_lines(char *fname) {
	// Gives the number of lines in an activity csv file
	int count = 0;
    char buff[MAX_LINE];
	FILE *fd;
    
    if ((fd = fopen(fname, "r")) == NULL) {
        fprintf(stderr, "%s: Count_line unable to open file \"%s\"\n", strerror(errno), fname);
        exit(2);
    };
	
    while (fgets(buff, MAX_LINE, fd) > 0) {
        count += 1;
    }

	fclose(fd);

	return count;
	
}