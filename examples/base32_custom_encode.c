#include <stdio.h>
#include <string.h>

#define BASED_IMPLEMENTATION
#include <based.h>

int main(void) {
    char *text = "I am gonna be encoded with custom encoding";
    const unsigned char z_base_alphabet[32] = "ybndrfg8ejkmcpqxot1uwisza345h769";
    size_t text_length = strlen(text);
    size_t encoded_length = based32_get_based_len(text_length);
    char encoded[encoded_length];

    based32_encode_custom(text, text_length, encoded, z_base_alphabet, 'X');

    printf("Encoded: %s\n", encoded);
    // outputs "Encoded: jrogn5jyc7zsh5ubrbtgkedfp3ts63dfcoo8q4mwpyogg7muqtzs4edfp3ts63djp3uoXXXX"

    return 0;
}

