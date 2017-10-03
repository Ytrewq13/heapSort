#include "sort.h"

int * create_rand_list(int length) {
	int * list = (int*) malloc(length * sizeof(int));
	int i;
	for (i = 0; i < length; i++) {
		int r = rand();
		*(list + i) = r / (int)((double) RAND_MAX / 32.0);
	}
	return list;
}

void print_array(int * array, int length, int cswap_i, int cdir) {
	/* cswap_i is the index at which the color swaps (first index of second color).
	 * if cdir is 0, green is first. If it is 1, red is first.
	 */
	char *first_color = (cdir == 1)? "\033[31;1m": "\033[32;1m";
	char *second_color = (cdir == 0)? "\033[31;1m": "\033[32;1m";
	char *reset_colors = "\033[0m";
	int i;
	printf("%s", first_color);
	for (i = 0; i < length; i++) {
		if (i == cswap_i) printf("%s", second_color);
		printf("%d", *(array+i));
		if (i < length - 1) {
			printf(", ");
		}
	}
	printf("%s", reset_colors);
	printf("\n");
}

void swap(int * array, int a, int b) {
	/* XOR, XOR, XOR equals swap with no temporary value storage --> no extra memory is used.
	 * this means we save a whopping 32 bits at the cost of slightly reduced speed on modern systems.
	 * On an older system, where memory (and speed) is actually important, this method is actually
	 * quite a bit faster. For this reason, I think it is better to use this method, as it makes
	 * very little difference on modern systems, but can speed up execution on systems which will
	 * have a longer execution time anyway.
	 */
    /* 
     * Having said that, the heap sort ends up swapping an element with itself, which (if we use the XOR
     * method) results in a zero value at that memory location, since when a number is XOR'ed with itelf
     * the result is always zero. As a compromise, let's first check that the two indices are not equal
     * before we use the XOR method. If they are equal, we can return.
     */
    /* It turns out that if the VALUES are the same we need to do nothing, not just if the INDICES are
     * the same. I'll fix that now...
     */
    if (a == b) return;
    if (*(array+a) == *(array+b)) return;
	*(array+a) = *(array+a)^*(array+b);
	*(array+b) = *(array+a)^*(array+b);
	*(array+a) = *(array+a)^*(array+b);
}
