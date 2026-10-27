// Prompt: Implement the Generic Merge Sort algorithm in C. The code should be functional, readable, and self-documenting, with concise comments where necessary.
// Date: October 27, 2026
// Model: GPT-6
// Mode: Think mode enabled
// Platform: OpenAI ChatGPT


// #include <stdbool.h>
// #include <stddef.h>
// #include <stdio.h>
// #include <stdlib.h>
// These libraries seemed to be unused, so I commented them out.
#include <stdint.h>
#include <string.h>

/* Compares two elements:
   Returns a negative value if a < b,
   zero if a == b,
   a positive value if a > b. */
typedef int (*CompareFn)(const void *a, const void *b);

/*
 * Sorts the half-open range [left, right) using Merge Sort.
 *
 * array   - Array to sort.
 * scratch - Temporary buffer used during merging.
 * left    - First index of the range.
 * right   - One past the last index of the range.
 * size    - Size of each element in bytes.
 * compare - Function used to compare elements.
 */
static void merge_sort_range(
    unsigned char *array,
    unsigned char *scratch,
    size_t left,
    size_t right,
    size_t size,
    CompareFn compare
) {
    /* A range containing zero or one element is already sorted. */
    if (right - left < 2) {
        return;
    }

    /* Split the range into two smaller ranges. */
    size_t mid = left + (right - left) / 2;

    merge_sort_range(array, scratch, left, mid, size, compare);
    merge_sort_range(array, scratch, mid, right, size, compare);

    /* Merge the two sorted ranges into the scratch buffer. */
    size_t i = left;
    size_t j = mid;
    size_t k = left;

    while (i < mid && j < right) {
        void *left_element = array + i * size;
        void *right_element = array + j * size;

        /* Take the left element first to preserve stability. */
        if (compare(left_element, right_element) <= 0) {
            memcpy(scratch + k * size, array + i * size, size);
            i++;
        } else {
            memcpy(scratch + k * size, array + j * size, size);
            j++;
        }

        k++;
    }

    /* Copy any remaining elements from the left range. */
    while (i < mid) {
        memcpy(scratch + k * size, array + i * size, size);
        i++;
        k++;
    }

    /* Copy any remaining elements from the right range. */
    while (j < right) {
        memcpy(scratch + k * size, array + j * size, size);
        j++;
        k++;
    }

    /* Copy the merged, sorted range back into the original array. */
    memcpy(array + left * size,
           scratch + left * size,
           (right - left) * size);
}

/*
 * Sorts an array of arbitrary element types using Merge Sort.
 *
 * Parameters:
 *   base        - Pointer to the first array element.
 *   count       - Number of elements.
 *   element_size- Size of each element in bytes.
 *   compare     - Function that compares two elements.
 *
 * Returns:
 *   true  - Sorting succeeded.
 *   false - Invalid arguments or memory allocation failure.
 *
 * An empty array is considered successfully sorted.
 */
bool generic_merge_sort(
    void *base,
    size_t count,
    size_t element_size,
    CompareFn compare
) {
    if (count == 0) {
        return true;
    }

    if (base == NULL || element_size == 0) {
        return false;
    }

    if (count == 1) {
        return true;
    }

    if (compare == NULL || count > SIZE_MAX / element_size) {
        return false;
    }

    /* Allocate one temporary buffer for the entire sorting operation. */
    unsigned char *scratch = malloc(count * element_size);

    if (scratch == NULL) {
        return false;
    }

    merge_sort_range(
        (unsigned char *)base,
        scratch,
        0,
        count,
        element_size,
        compare
    );

    free(scratch);
    return true;
}
