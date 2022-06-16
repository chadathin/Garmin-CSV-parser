

#include "parselib.h"
#include "actstr.h"

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

int calc_rss(int avghr, int lthr, double duration) {

    double stress = ((double)avghr / (double) lthr) * (duration / (double)60);
    stress = stress * 100;
    return (int) stress;

}



void print_array(int *arr, int size, int filter) {
    int i;
    printf("[");
    for (i = 0; i<size; i++) {
        if (filter) {
            if (*(arr + i) == 0) {
                printf("--");
            } else {
                printf("%d", *(arr + i));
            }
        } else {
            printf("%d", *(arr + i));
        }
        
        
        if (i<size-1) printf(", ");
    }
    printf("]\n");

}

void fprint_array(float *arr, int size, int filter) {
    int i;
    printf("[");
    for (i = 0; i<size; i++) {
        if (filter) {
            if (*(arr + i) == 0) {
                printf("--");
            } else {
                printf("%f", *(arr + i));
            }
        } else {
            printf("%f", *(arr + i));
        }
        
        
        if (i<size-1) printf(", ");
    }
    printf("]\n");

}


time_t get_epoch(char *date) {
 
    struct tm temp;
    sscanf(date, "%d-%d-%d", &temp.tm_year, 
        &temp.tm_mon, &temp.tm_mday);
        
    temp.tm_year -= 1900;
    temp.tm_min--;
    temp.tm_isdst = -1;
    temp.tm_sec = 0;
    temp.tm_min = 0;
    temp.tm_hour = 0;
    
    return mktime(&temp);
}

void reverse(int *list, int len) {
  int *start = list;
  int *end = (list + len) - 1;
  int temp;
  int i;
  
  
  for (i = 0; i< len/2; i++) {
    temp = *start;
    *start = *end;
    *end = temp;
    start++;
    end--;
  }
  
  
}

int *sliding_window_average(int wsize, int *arr, int asize) {
	// Calculates the rolling averages of an array
	// rolling window is size 'wsize'
	// 'wsize' must be <= to 'asize'
	// returns pointer to an array of floats containing averages
	// Output array created with malloc; caller must use free()
  
  float avg = 0;
  int *out = (int *)malloc((asize - wsize + 1)*sizeof(int));
	
  int *s, *e;
  s = arr;
  e = arr;

	int i, a_index, sum;
	a_index = 0;
	sum = 0;

	// Establish window
  for (i = 0; i < wsize; i++) {
    sum += *e;
    e++;
  }

	// place the first average and increment
  *(out + a_index) = round((float)sum/(float)(wsize));
  a_index++;

  // walk down the array
  while (i < asize) {

		// add the next, subtract the first, average and place
    sum += (*e - *s);
    *(out + a_index) = round((float)sum/(float)(wsize));
    
    a_index++;
    e++;
    s++;
    i++;
  }
  
  return out;
  
}

int *sliding_window_sum(int wsize, int *arr, int asize) {
	// Calculates the rolling averages of an array
	// rolling window is size 'wsize'
	// 'wsize' must be <= to 'asize'
	// returns pointer to an array of floats containing averages
	// Output array created with malloc; caller must use free()
  
//   float avg = 0;
  int *out = (int *)malloc((asize - wsize + 1)*sizeof(int));
	
  int *s, *e;
  s = arr;
  e = arr;

	int i, a_index, sum;
	a_index = 0;
	sum = 0;

	// Establish window
  for (i = 0; i < wsize; i++) {
    sum += *e;
    e++;
  }

	// place the first average and increment
  *(out + a_index) = round((float)sum);
  a_index++;

  // walk down the array
  while (i < asize) {

		// add the next, subtract the first, average and place
    sum += (*e - *s);
    *(out + a_index) = round((float)sum);
    
    a_index++;
    e++;
    s++;
    i++;
  }
  
  return out;
  
}