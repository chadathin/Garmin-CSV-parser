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
        fflush(stderr);
        exit(2);
    };
	
    while (fgets(buff, MAX_LINE, fd) > 0) {
        count += 1;
    }

	fclose(fd);

	return count;
	
}

void stripper(char in[]) {
	// removes extraneous double quotes
	// shifts each character to the left by one
    // replaces last character with null
    char *start = in;
    char *end = start + 1;
    while (*end != '\0') {
        *start = *end;
        start++;
        end++;
    }
    in[strlen(in)-2] = '\0';
}

double decTime(char strTime[]) {
  double out = 0.0;
  int separators = 0;
  
  char *start, *curr;
  start = strTime;
  curr = strTime;
  
  while (*curr != '\0') {
    if (*curr == ':') {
      *curr = '\0';
      curr++;
      if (!separators) {
        out += (atof(start)*60); 
      } else {
        out += atof(start); 
      }
      separators++;
      start = curr;
    } else {
      curr++;
    }
    
  }
  out += (atof(start)/60);
  return out;
  
}