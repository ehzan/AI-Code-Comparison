#include <stdio.h>
#include <stdlib.h>
#include "merge-sort-GPT.c"

/* Comparator for integers. */
static int compare_ints(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;

    return (int_a > int_b) - (int_a < int_b);
}

/* Comparator for doubles. */
static int compare_doubles(const void *a, const void *b) {
    double double_a = *(const double *)a;
    double double_b = *(const double *)b;

    return (double_a > double_b) - (double_a < double_b);
}

/* Comparator for strings (lexicographical order). */
static int compare_strings(const void *a, const void *b) {
    const char *str_a = *(const char * const *)a;
    const char *str_b = *(const char * const *)b;

    return strcmp(str_a, str_b);
}


int main(void) {
    /* Test 1: Sort integers. */
    int numbers[] = {38, 12, 27, 43, 9, 31, 18, 25};
    size_t number_count = sizeof(numbers) / sizeof(numbers[0]);

    if (!generic_merge_sort(
            numbers,
            number_count,
            sizeof(numbers[0]),
            compare_ints
        )) {
        fprintf(stderr, "Error: Integer Merge Sort failed.\n");
        return EXIT_FAILURE;
    }

    printf("Sorted integers: ");

    for (size_t i = 0; i < number_count; i++) {
        printf("%d%s", numbers[i],
               i + 1 < number_count ? " " : "\n");
    }

    /* Test 2: Sort strings lexicographically. */
    const char *words[] = {
        "pear", "apple", "orange", "banana", "grape", "apple"
    };
    size_t word_count = sizeof(words) / sizeof(words[0]);

    if (!generic_merge_sort(
            words,
            word_count,
            sizeof(words[0]),
            compare_strings
        )) {
        fprintf(stderr, "Error: String Merge Sort failed.\n");
        return EXIT_FAILURE;
    }

    printf("Sorted strings:  ");

    for (size_t i = 0; i < word_count; i++) {
        printf("%s%s", words[i],
               i + 1 < word_count ? " " : "\n");
    }


    /* Test 3: Sort real numbers. */
double real_numbers[] = {
    3.14, -2.5, 0.0, 7.89, -1.25, 3.14, 2.718
};

size_t real_count =
    sizeof(real_numbers) / sizeof(real_numbers[0]);

if (!generic_merge_sort(
        real_numbers,
        real_count,
        sizeof(real_numbers[0]),
        compare_doubles
    )) {
    fprintf(stderr, "Error: Real-number Merge Sort failed.\n");
    return EXIT_FAILURE;
}

printf("Sorted real numbers: ");

for (size_t i = 0; i < real_count; i++) {
    printf("%.3f%s",
           real_numbers[i],
           i + 1 < real_count ? " " : "\n");
}

    return EXIT_SUCCESS;
}