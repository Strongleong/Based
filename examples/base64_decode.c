#include <stdio.h>
#include <string.h>

#define BASED_IMPLEMENTATION
#include <based.h>

int main(void) {
    char *text = "SGVsbG8sIFdvcmxkIQ==";
    size_t text_length = strlen(text);
    size_t decoded_length = based64_get_clear_len(text_length);
    char decoded[decoded_length];

    based64_decode(text, text_length, decoded);

    printf("Decoded: %s\n", decoded);
    // outputs "Decoded: Hello, Wolrd!"

    return 0;
}
