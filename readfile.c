#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Read integers from a file into a dynamically allocated array. */
int *readIntegers(const char *filename, size_t *count)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    size_t capacity = 16;
    *count = 0;

    int *numbers = malloc(capacity * sizeof(*numbers));

    if (numbers == NULL) {
        fclose(file);
        return NULL;
    }

    int value;
    int result;

    while ((result = fscanf(file, "%d", &value)) == 1) {
        if (*count == capacity) {
            capacity *= 2;

            int *temp = realloc(numbers, capacity * sizeof(*numbers));

            if (temp == NULL) {
                free(numbers);
                fclose(file);
                return NULL;
            }

            numbers = temp;
        }

        numbers[(*count)++] = value;
    }

    if (result != EOF || ferror(file)) {
        free(numbers);
        fclose(file);
        return NULL;
    }

    fclose(file);
    return numbers;
}

int main(void)
{
    size_t count = 0;

    /* Start measuring execution time. */
    clock_t start = clock();

    int *numbers = readIntegers("./data/integer_numbers.txt", &count);

    /* Stop measuring execution time. */
    clock_t end = clock();

    if (numbers == NULL) {
        fprintf(stderr, "Failed to read integers.\n");
        return EXIT_FAILURE;
    }

    /* Calculate elapsed CPU time in seconds. */
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Integers read: %zu\n", count);
    printf("Execution time: %.6f seconds\n", elapsed_time);

    free(numbers);

    return EXIT_SUCCESS;
}