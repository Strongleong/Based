#include <stdio.h>
#include <string.h>

#define BASED_IMPLEMENTATION
#include <based.h>

int main(void) {
    char *text = "Hello, World!";
    size_t text_length = strlen(text);
    size_t encoded_length = based64_get_based_len(text_length);
    char encoded[encoded_length];

    based64_encode(text, text_length, encoded);

    printf("Encoded: %s\n", encoded);
    // outputs "Encoded: SGVsbG8sIFdvcmxkIQ=="

    return 0;
}

