/*
  Based v1.0.1
  Single file header only library for encoding/decoding `base64`, `base32` and `base16` encodings in C.
  This library supports encodings with custom padding (`=` at the end of encoded messages)
  and custom alphabets, if they are have length of 64, 32 or 16.
  Alphabets for `base64_url` and `base32_hex` encodings are included.
  Based also don't allocate on heap.
  Check out examples to see how to use this library

  See licese at the end of this file

  I did not came up with core logic, but I baseically rewrite what I found on the internet.
  Sources:
    - List of different solutions with performance: https://stackoverflow.com/a/41094722 https://github.com/gaspardpetit/base64  @GaspardP

    - Encoder: https://web.mit.edu/freebsd/head/contrib/wpa/src/utils/base64.c @jounimalinen
      Encoder code was modified and orignal code was distributed uner this licese:
      ------------------------------------------------
      This software may be distributed, used, and modified under the terms of
      BSD license:

      Redistribution and use in source and binary forms, with or without
      modification, are permitted provided that the following conditions are
      met:

      1. Redistributions of source code must retain the above copyright
         notice, this list of conditions and the following disclaimer.

      2. Redistributions in binary form must reproduce the above copyright
         notice, this list of conditions and the following disclaimer in the
         documentation and/or other materials provided with the distribution.

      3. Neither the name(s) of the above-listed copyright holder(s) nor the
         names of its contributors may be used to endorse or promote products
         derived from this software without specific prior written permission.

      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
      ------------------------------------------------

    - Decoder: https://stackoverflow.com/a/37109258   @polfosol
      Decoder code was modified and orignal code was not licensed


  Dependencies:
    - `stddef.h`: `size_t`
    - `stdint.h`:  `uint8_t` and `uint32_t`

  You can define `BASED_NO_STD` and if will not include dependencies and replace types like this:
    - `size_t`: `unsigned long long`
    - `uint8_t`: `unsigned char`
    - `uint32_t`: `unsigned int`

  If those types already defined, `BASED_NO_STD` will not redefined them. Just exclude std headers.
*/

#ifndef BASED_H
#define BASED_H

#ifndef BASED_DEF
#define BASED_DEF extern
#endif

#ifdef BASED_NO_STD
  #ifndef size_t
    #define size_t unsigned long long
  #endif
#else
  #include <stddef.h>
#endif

#define BASED_VERSION_MAJOR    0
#define BASED_VERSION_MINOR    0
#define BASED_VERSION_RELEASE  1
#define BASED_VERSION_NUMBER (BASED_VERSION_MAJOR *100*100 + BASED_VERSION_MINOR *100 + BASED_VERSION_RELEASE)

#define BASED_VERSION_FULL BASED_VERSION_MAJOR.BASED_VERSION_MINOR.BASED_VERSION_RELEASE
#define BASED_QUOTE(str) #str
#define BASED_EXPAND_AND_QUOTE(str) BASED_QUOTE(str)
#define BASED_VERSION_STRING BASED_EXPAND_AND_QUOTE(BASED_VERSION_FULL)

#ifdef __cplusplus
extern "C" {
#endif

typedef int (fn_based_encode)(const char *clear_text, size_t clear_text_len, char *based_text);
typedef int (fn_based_decode)(const char *based_text, size_t based_text_len, char *clear_text);
typedef size_t (fn_based_get_len)(size_t input_len);

//
// -------------- Based64 --------------
//

BASED_DEF size_t based64_get_based_len(size_t clear_text_len);
BASED_DEF size_t based64_get_clear_len(size_t based_text_len);

BASED_DEF int based64_encode_custom(const char *clear_text, size_t clear_text_len, char *based_text, const unsigned char *alphabet, const char padding);
BASED_DEF int based64_decode_custom(const char *based_text, size_t based_text_len, char *clear_text, const unsigned char *decode_table, const char padding);

BASED_DEF int based64_encode(const char *clear_text, size_t clear_text_len, char *based_text);
BASED_DEF int based64_decode(const char *based_text, size_t based_text_len, char *clear_text);

BASED_DEF int based64_url_encode(const char *clear_text, size_t clear_text_len, char *based_text);
BASED_DEF int based64_url_decode(const char *based_text, size_t based_text_len, char *clear_text);

//
// -------------- Based32 --------------
//

BASED_DEF size_t based32_get_based_len(size_t clear_text_len);
BASED_DEF size_t based32_get_clear_len(size_t based_text_len);

BASED_DEF int based32_encode_custom(const char *clear_text, size_t clear_text_len, char *based_text, const unsigned char *alphabet, const char padding);
BASED_DEF int based32_decode_custom(const char *based_text, size_t based_text_len, char *clear_text, const unsigned char *decode_table, const char padding);

BASED_DEF int based32_encode(const char *clear_text, size_t clear_text_len, char *based_text);
BASED_DEF int based32_decode(const char *based_text, size_t based_text_len, char *clear_text);

BASED_DEF int based32_hex_encode(const char *clear_text, size_t clear_text_len, char *based_text);
BASED_DEF int based32_hex_decode(const char *based_text, size_t based_text_len, char *clear_text);

//
// -------------- Based16 --------------
//

BASED_DEF size_t based16_get_based_len(size_t clear_text_len);
BASED_DEF size_t based16_get_clear_len(size_t based_text_len);

BASED_DEF int based16_encode_custom(const char *clear_text, size_t clear_text_len, char *based_text, const unsigned char *alphabet);
BASED_DEF int based16_decode_custom(const char *based_text, size_t based_text_len, char *clear_text, const unsigned char *decode_table);

BASED_DEF int based16_encode(const char *clear_text, size_t clear_text_len, char *based_text);
BASED_DEF int based16_decode(const char *clear_text, size_t clear_text_len, char *based_text);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard: BASED_H */

#ifdef BASED_IMPLEMENTATION

#ifdef BASED_NO_STD
  #ifndef uint8_t
    #define uint8_t unsigned char
  #endif
  #ifndef uint32_t
    #define uint32_t unsigned int
  #endif
#else
  #include <stdint.h>
#endif

static const unsigned char based_padding       = '=';
static const unsigned char alphabet_64[64]     = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const unsigned char alphabet_64_url[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
static const unsigned char alphabet_32[32]     = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
static const unsigned char alphabet_32_hex[32] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
static const unsigned char alphabet_16[16]     = "0123456789ABCDEF";

// Thanks polfosol for this https://stackoverflow.com/a/37109258
static const unsigned char decode_table_64[256] =
{
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  62, 63, 62, 62, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0,  0,  0,  0,  63,
    0,  26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
};

static const unsigned char decode_table_64_url[256] =
{
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  62, 63, 62, 62, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0,  0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0,  0,  0,  0,  63,
    0,  26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
};

static const unsigned char decode_table_32[256] =
 {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,
    0,  0,  26, 27, 28, 29, 30, 31, 0,  0,  0, 0,  0,  0,  0,  0,
    0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25
 };

static const unsigned char decode_table_32_hex[256] =
{
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  0,  0,  0,  0,  0,  0,
    0,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27, 28, 29, 30, 31,
};

static const unsigned char decode_table_16[256] =
{
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  0,  0,  0,  0,  0,  0,
  0,  10, 11, 12, 13, 14, 15
};

//
// -------------- Based64 --------------
//

BASED_DEF size_t based64_get_based_len(size_t clear_text_len) {
  if (clear_text_len == 0) {
    return 1; // For \0 to return proper empty string
  }

  return (clear_text_len + 4) / 5 * 8 + 1;
}

BASED_DEF size_t based64_get_clear_len(size_t based_text_len) {
  if (based_text_len == 0) {
    return 1; // For \0 to return proper empty string
  }

  return 3 * ((based_text_len >> 2) + 1);
}

BASED_DEF int based64_encode_custom(const char *clear_text, size_t clear_text_len, char *based_text, const unsigned char *alphabet, const char padding) {
  if (clear_text_len == 0) {
    *based_text = '\0';
    return 1;
  }

  char *cursor = based_text;

  size_t i = 0;
  for (; clear_text_len - i >= 3; i += 3) {
    *cursor++ = alphabet[clear_text[i] >> 2];
    *cursor++ = alphabet[(clear_text[i] & 0x03) << 4 | (clear_text[i + 1] >> 4)];
    *cursor++ = alphabet[((clear_text[i + 1] & 0x0F) << 2) | (clear_text[i + 2] >> 6)];
    *cursor++ = alphabet[clear_text[i + 2] & 0x3F];
  }

  uint8_t unprocessed_clear_left = clear_text_len - i;

  if (unprocessed_clear_left > 0) {
    *cursor++ = alphabet[clear_text[i] >> 2];

    if (unprocessed_clear_left == 1) {
      *cursor++ = alphabet[(clear_text[i] & 0x03) << 4 | (clear_text[i + 1] >> 4)];
      *cursor++ = padding;
    } else {
      *cursor++ = alphabet[(clear_text[i] & 0x03) << 4 | (clear_text[i + 1] >> 4)];
      *cursor++ = alphabet[(clear_text[i + 1] & 0x0F) << 2];
    }

    *cursor++ = padding;
  }

  *cursor = '\0';
  return 0;
}

BASED_DEF int based64_decode_custom(const char *based_text, size_t based_text_len, char *clear_text, const unsigned char *decode_table, const char padding) {
  if (based_text_len == 0) {
    *clear_text = '\0';
    return 1;
  }

  const unsigned char *based = (unsigned char *)based_text;
  uint8_t pad1 = (based_text_len) % 4 || based_text[based_text_len - 1] == padding;
  uint8_t pad2 = pad1 && ((based_text_len) % 4 > 2 || based_text[based_text_len - 2] != '=');
  const size_t last = (based_text_len - pad1) / 4 << 2;

  char *cursor = clear_text;

  for (size_t i = 0; i < last; i += 4) {
    uint32_t n = decode_table[based[i]]     << 18 |
                 decode_table[based[i + 1]] << 12 |
                 decode_table[based[i + 2]] << 6  |
                 decode_table[based[i + 3]];
    *cursor++ = n >> 16;
    *cursor++ = n >> 8 & 0xFF;
    *cursor++ = n & 0xFF;
  }

  if (pad1) {
    int n = decode_table[based[last]] << 18 | decode_table[based[last + 1]] << 12;
    *cursor++ = n >> 16;

    if (pad2) {
      n |= decode_table[based[last + 2]] << 6;
      *cursor++ = n >> 8 & 0xFF;
    }
  }

  *cursor = '\0';
  return 0;
}

BASED_DEF int based64_encode(const char *clear_text, size_t clear_text_len, char *based_text) {
  return based64_encode_custom(clear_text, clear_text_len, based_text, alphabet_64, based_padding);
}

BASED_DEF int based64_decode(const char *based_text, size_t based_text_len, char *clear_text) {
  return based64_decode_custom(based_text, based_text_len, clear_text, decode_table_64, based_padding);
}

BASED_DEF int based64_url_encode(const char *clear_text, size_t clear_text_len, char *based_text) {
  return based64_encode_custom(clear_text, clear_text_len, based_text, alphabet_64_url, based_padding);
}

BASED_DEF int based64_url_decode(const char *based_text, size_t based_text_len, char *clear_text) {
  return based64_decode_custom(based_text, based_text_len, clear_text, decode_table_64_url, based_padding);
}

//
// -------------- Based32 --------------
//

BASED_DEF size_t based32_get_based_len(size_t clear_text_len) {
  if (clear_text_len == 0) {
    return 1; // For \0 to return proper empty string
  }

  return ((clear_text_len + 5 - 1) / 5) * 8 + 1;
}

BASED_DEF size_t based32_get_clear_len(size_t based_text_len) {
  if (based_text_len == 0) {
    return 1; // For \0 to return proper empty string
  }

  return based_text_len * 5 / 8 + 1;
}

BASED_DEF int based32_encode_custom(const char *clear_text, size_t clear_text_len, char *based_text, const unsigned char *alphabet, const char padding) {
  if (clear_text_len == 0) {
    *based_text = '\0';
    return 1;
  }

  char *cursor = based_text;

  size_t i = 0;
  for (; clear_text_len - i >= 5; i += 5) {
    *cursor++ = alphabet[clear_text[i] >> 3];
    *cursor++ = alphabet[(clear_text[i] & 0x07) << 2 | (clear_text[i + 1] >> 6)];
    *cursor++ = alphabet[(clear_text[i + 1] & 0x3E) >> 1];
    *cursor++ = alphabet[(clear_text[i + 1] & 0x01) << 4 | (clear_text[i + 2] >> 4)];
    *cursor++ = alphabet[(clear_text[i + 2] & 0x0F) << 1 | (clear_text[i + 3] >> 7)];
    *cursor++ = alphabet[(clear_text[i + 3] & 0x7C) >> 2];
    *cursor++ = alphabet[(clear_text[i + 3] & 0x03) << 3 | (clear_text[i + 4] >> 5)];
    *cursor++ = alphabet[clear_text[i + 4] & 0x1F];
  }

  uint8_t unprocessed_clear_left = clear_text_len - i;

  if (unprocessed_clear_left > 0) {
    *cursor++ = alphabet[clear_text[i] >> 3];

    switch (unprocessed_clear_left) {
      case 4:
        *cursor++ = alphabet[(clear_text[i] & 0x07) << 2 | (clear_text[i + 1] >> 6)];
        *cursor++ = alphabet[(clear_text[i + 1] & 0x3E) >> 1];
        *cursor++ = alphabet[(clear_text[i + 1] & 0x01) << 4 | (clear_text[i + 2] >> 4)];
        *cursor++ = alphabet[(clear_text[i + 2] & 0x0F) << 1 | (clear_text[i + 3] >> 7)];
        *cursor++ = alphabet[(clear_text[i + 3] & 0x7C) >> 2];
        *cursor++ = alphabet[(clear_text[i + 3] & 0x03) << 3 | (clear_text[i + 4] >> 5)];
        break;
      case 3:
        *cursor++ = alphabet[(clear_text[i] & 0x07) << 2 | (clear_text[i + 1] >> 6)];
        *cursor++ = alphabet[(clear_text[i + 1] & 0x3E) >> 1];
        *cursor++ = alphabet[(clear_text[i + 1] & 0x01) << 4 | (clear_text[i + 2] >> 4)];
        *cursor++ = alphabet[(clear_text[i + 2] & 0x0F) << 1 | (clear_text[i + 3] >> 7)];
        *cursor++ = padding;
        *cursor++ = padding;
        break;
      case 2:
        *cursor++ = alphabet[(clear_text[i] & 0x07) << 2 | (clear_text[i + 1] >> 6)];
        *cursor++ = alphabet[(clear_text[i + 1] & 0x3E) >> 1];
        *cursor++ = alphabet[(clear_text[i + 1] & 0x01) << 4 | (clear_text[i + 2] >> 4)];
        *cursor++ = padding;
        *cursor++ = padding;
        *cursor++ = padding;
        break;
      case 1:
        *cursor++ = alphabet[(clear_text[i] & 0x07) << 2 | (clear_text[i + 1] >> 6)];
        *cursor++ = padding;
        *cursor++ = padding;
        *cursor++ = padding;
        *cursor++ = padding;
        *cursor++ = padding;
        break;
    }

    *cursor++ = padding;
  }

  *cursor = '\0';
  return 0;
}

BASED_DEF int based32_decode_custom(const char *based_text, size_t based_text_len, char *clear_text, const unsigned char *decode_table, const char padding) {
  (void) padding;
  if (based_text_len == 0) {
    *clear_text = '\0';
    return 1;
  }

  const unsigned char *based = (unsigned char *)based_text;
  char *cursor = clear_text;

  // TODO: Mabye rewrite the loop using iterator instead of index? (like char it = *based; it != '='; i++)
  for (size_t i = 0; i < based_text_len; i += 8) {
    *cursor++ = ((decode_table[based[i + 0]] << 3) & 0xF8) | ((decode_table[based[i + 1]] >> 2) & 0x7);
    *cursor++ = ((decode_table[based[i + 1]] << 6) & 0xC0) | ((decode_table[based[i + 2]] << 1) & 0x3E) | ((decode_table[based[i + 3]] >> 4) & 0x1);
    *cursor++ = ((decode_table[based[i + 3]] << 4) & 0xF0) | ((decode_table[based[i + 4]] >> 1) & 0xF);
    *cursor++ = ((decode_table[based[i + 4]] << 7) & 0x80) | ((decode_table[based[i + 5]] << 2) & 0x7C) | ((decode_table[based[i + 6]] >> 3) & 0x3);
    *cursor++ = ((decode_table[based[i + 6]] << 5) & 0xE0) |  (decode_table[based[i + 7]] & 0x1F);
  }

  *cursor = '\0';
  return 0;
}

BASED_DEF int based32_encode(const char *clear_text, size_t clear_text_len, char *based_text) {
  return based32_encode_custom(clear_text, clear_text_len, based_text, alphabet_32, based_padding);
}

BASED_DEF int based32_decode(const char *based_text, size_t based_text_len, char *clear_text) {
  return based32_decode_custom(based_text, based_text_len, clear_text, decode_table_32, based_padding);
}

BASED_DEF int based32_hex_encode(const char *clear_text, size_t clear_text_len, char *based_text) {
  return based32_encode_custom(clear_text, clear_text_len, based_text, alphabet_32_hex, based_padding);
}

BASED_DEF int based32_hex_decode(const char *based_text, size_t based_text_len, char *clear_text) {
  return based32_decode_custom(based_text, based_text_len, clear_text, decode_table_32_hex, based_padding);
}

//
// -------------- Based16 --------------
//

BASED_DEF size_t based16_get_based_len(size_t clear_text_len) {
  if (clear_text_len == 0) {
    return 1; // For \0 to return proper empty string
  }

  return clear_text_len * 2 + 1;
}

BASED_DEF size_t based16_get_clear_len(size_t based_text_len) {
  if (based_text_len == 0) {
    return 1; // For \0 to return proper empty string
  }

  return based_text_len / 2 + 1;
}

BASED_DEF int based16_encode_custom(const char *clear_text, size_t clear_text_len, char *based_text, const unsigned char *alphabet) {
  if (clear_text_len == 0) {
    *based_text = '\0';
    return 1;
  }

  char *cursor = based_text;

  for (size_t i = 0; i < clear_text_len; i++) {
    *cursor++ = alphabet[clear_text[i] >> 4];
    *cursor++ = alphabet[clear_text[i] & 0x0F];
  }

  *cursor = '\0';
  return 0;
}

BASED_DEF int based16_decode_custom(const char *based_text, size_t based_text_len, char *clear_text, const unsigned char *decode_table) {
  if (based_text_len == 0) {
    *clear_text = '\0';
    return 1;
  }

  const unsigned char *based = (unsigned char *)based_text;
  char *cursor = clear_text;

  for (size_t i = 0; i < based_text_len; i += 2) {
    *cursor++ = decode_table[based[i]] << 4 | decode_table[based[i + 1]];
  }

  *cursor = '\0';
  return 0;
}

BASED_DEF int based16_encode(const char *clear_text, size_t clear_text_len, char *based_text) {
  return based16_encode_custom(clear_text, clear_text_len, based_text, alphabet_16);
}

BASED_DEF int based16_decode(const char *based_text, size_t based_text_len, char *clear_text) {
  return based16_decode_custom(based_text, based_text_len, clear_text, decode_table_16);
}

#endif /* end of include guard: BASED_IMPLEMENTATION */


/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2024 Nikita (Strongleong) Chulkov
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/
