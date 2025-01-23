# Based

Single file header only library for encoding/decoding `base64`, `base32` and `base16` encodings in C.

This library supports encodings with custom padding (`=` at the end of encoded messages)
and custom alphabets, if they are have length of 64, 32 or 16.

Alphabets for `base64_url` and `base32_hex` encodings are included.

Based also don't allocate on heap.

Check out examples to see how to use this library

## Dependencies

Only `stddef.h` (for `size_t`) and `stdint.h`

## How to run tests

```console
./build.sh && ./out/test
```

Run `./build.sh --help` to see which build flags you can customize

## Tools

`./utils/generate_decoding_table.c` - generates C lookup table for decoding custom alphabets

```console
Usage: ./out/generate_decoding_table [params] <aphabet>
Additional params:
    -h  --help     Prints this usage
    -v  --version  Prints version
    -n  --name     Name of alphabet
Examples:
    ./out/generate_decoding_table "abcdABCD123!@#"
    ./out/generate_decoding_table --name base19_awesomeness "AWESOMEawesome"
```

## Examples

Encode string into `base64`:

```c
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
```

Decode string from `base64`:

```c
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
```

Encode with custom 32-bit encoding (`z-base-32` in this case)

```c
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
```

To decode you should use `generate_decoding_table` util first.

```
./out/generate_decoding_table --name z_base ybndrfg8ejkmcpqxot1uwisza345h769
```

Output:

```console
static const unsigned char decode_table_z_base[256] =
{
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  18, 0,  25, 26, 27, 30, 29, 7,  31, 0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  24, 1,  12, 3,  8,  5,  6,  28, 21, 9,  10, 0,  11, 2,  16,
  13, 14, 4,  22, 17, 19, 0,  20, 15, 0,  23, 0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};
```

You should put this somewhere in your code. You can remove leading zeroes (everything after last '23').

The code should look something like this:

```c
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

```

And for last here is encdoding/decoding for `base16`

```c
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
```

Examples code in `./examples/` folder

## TODO

 - [X] Base64 encoding
 - [X]        encoding
 - [X] Base32 encoding
 - [X]        encoding
 - [X] Base16 encoding
 - [X]        encoding
 - [X] `NO_STD` option
 - [X] More examples
 - [X] More documentation and guides
