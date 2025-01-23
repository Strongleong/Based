#include <stdio.h>
#include <string.h>

#define BASED_IMPLEMENTATION
#include <based.h>

static const unsigned char decode_table_z_base[256] =
{
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  18, 0,  25, 26, 27, 30, 29, 7,  31, 0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  24, 1,  12, 3,  8,  5,  6,  28, 21, 9,  10, 0,  11, 2,  16,
  13, 14, 4,  22, 17, 19, 0,  20, 15, 0,  23,
};

int main(void) {
    char *text = "jrogn5jyc7zsh5ubrbtgkedfp3ts63dfcoo8q4mwpyogg7muqtzs4edfp3ts63djp3uoXXXX";
    size_t text_length = strlen(text);
    size_t decoded_length = based32_get_clear_len(text_length);
    char decoded[decoded_length];

    based32_decode_custom(text, text_length, decoded, decode_table_z_base, 'X');

    printf("Decoded: %s\n", decoded);
    // outputs "Decoded: I am gonna be encoded with custom encoding"

    return 0;
}

