#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <math.h>

#define ARR_LEN 16

void print_array(int * array, int length, int cswap_i, int cdir);
int * create_rand_list(int length);
void swap(int * array, int a, int b);
