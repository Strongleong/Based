# Based

Single file header only library for encoding/decoding `base64`, `base32` and `base16` encodings in C

There are also `base64_url` and `base32_hex` encodings supported

## How to run tests

```console
./build.sh && ./out/test
```

Run `./build.sh --help` to see which build flags you can customize

## Example

Encode string into `base64`:

```c
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
#define BASED_IMPLEMENTATION
#include <based.h>

int main(void) {
    char *text = "SGVsbG8sIFdvcmxkIQ==";
    size_t text_length = strlen(text);
    size_t decoded_length = based64_get_clear_len(text, text_length);
    char decoded[decoded_length];

    based64_decode(text, text_length, decoded);

    printf("Decoded: %s\n", decoded);
    // outputs "Decoded: Hello, Wolrd!"

    return 0;
}
```

## TODO

 - [X] Base64 encoding
 - [X]        encoding
 - [ ] Base32 encoding
 - [ ]        encoding
 - [ ] Base16 encoding
 - [ ]        encoding
 - [ ] More documentation and guides
