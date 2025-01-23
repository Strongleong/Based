#include <stdio.h>
#include <string.h>

#define BASED_IMPLEMENTATION
#include <based.h>

int main(void) {
    char *text = "I am 16 now";
    size_t text_length = strlen(text);
    size_t encoded_length = based16_get_based_len(text_length);
    char encoded[encoded_length];

    based16_encode(text, text_length, encoded);

    printf("encoded: %s\n", encoded);
    // outputs "encoded: 4920616D203136206E6F77"

    size_t decoded_length = based16_get_clear_len(encoded_length);
    char decoded[decoded_length];

    based16_decode(encoded, encoded_length, decoded);
    printf("decoded: %s\n", decoded);
    // outputs "decoded: I am 16 now"

    return 0;
}
