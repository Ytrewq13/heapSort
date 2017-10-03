#include "sort.h"

#define DEBUG 0
#define ARR_SIZE 15

int parent(int);
void heap_sort(int*, int);

void print_ref_tree() {
    printf("           0\n");
    printf("    1             2\n");
    printf(" 3     4       5      6\n");
    printf("7 8   9 10   11 12  13 14\n");
}

void build_max_heap(int *array, int length) {
    int i;
    for (i = 0; i < length; i++) {
        //print_array(array, length, i, 0);
        int a = i;
        while (*(array+parent(a)) < *(array+a)) {
            swap(array, a, parent(a));
            a = parent(a);
        }
    }
}

int depth(int index) {
    index++;
    return (int) ceil(log(index)/log(2));
}

int first_index_at(int depth) {
    return pow(2, depth) - 1;
}

int parent(int index) {
    int d = depth(index);
    return first_index_at(d-1) + floor((index - first_index_at(d))/2.0f);
}

int child(int index, int dir) {
    // dir: 0 for left child, 1 for right child.
    int d = depth(index);
    int cd = d + 1;
    int offset = index - first_index_at(d);
    int coffset = offset * 2 + dir;
    return first_index_at(cd) + coffset;
}

void heapify(int *array, int length) {
    if (DEBUG) printf("Heapifying:\n");
    if (DEBUG) print_array(array, length, 0, 0);
    if (length < 2) return;
    int i = 0;
    while ((child(i, 1) < length) &&
            (*(array+child(i, 0)) > *(array+i) ||
             *(array+child(i, 1)) > *(array+i)) || 
            (*(array+child(i, 0)) > *(array+i) &&
             (child(i, 1) == length))) {
        int l = child(i, 0);
        int r = child(i, 1);
        int swap_index = l;
        if (*(array+r) > *(array+l) && !(r >= length)) swap_index = r;
        swap(array, i, swap_index);
        i = swap_index;
        if (child(i, 1) >= length) break;
    }
    if (DEBUG) printf("Result:\n");
    if (DEBUG) print_array(array, length, 0, 1);
}

int is_sorted(int *array, int length) {
    int i;
    for (i = 0; i < length-1; i++) {
        if (*(array+i) > *(array+i+1)) return 0;
    }
    return 1;
}

void test_sort() {
    int num_tests = 1000000;
    int i;
    int working = 1;
    for (i = 1; i < 1000001; i++) {
        if (i % 10000 == 0) {
            float percentage = (float) i * 100.0f / (float) num_tests;
            if (working) printf("\033[32;1mALL IS FINE (%3.1f %% complete).\n\033[0m", percentage);
            else printf("\033[31;1mNOT GOOD SOMETHING BROKE (%3.1f %% complete).\n\033[0m", percentage);
        }
        int *arr = create_rand_list(ARR_SIZE);
        heap_sort(arr, ARR_SIZE);
        if (!is_sorted(arr, ARR_SIZE)) {
            printf("FIX YO CODE.\n");
            working = 0;
        }
    }
}

void heap_sort(int *array, int length) {
    int i;
    build_max_heap(array, length);
    for (i = 1; i < length; i++) {
        swap(array, 0, length-i); // Remove the largest element from the heap.
        if (DEBUG) print_array(array, length, length-i, 1);
        heapify(array, length-(i)); // Rearrange the heap.
        if (DEBUG) print_array(array, length, length-i, 1);
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));
    test_sort();
    return 0;
}
