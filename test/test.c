#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define RED(str)   "\x1b[41m\x1b[30m"str"\x1b[0m"
#define GREEN(str) "\x1b[42m\x1b[30m"str"\x1b[0m"
#define BLUE(str)  "\x1b[34m"str"\x1b[0m"

#define BASED_IMPLEMENTATION
#include <based.h>

#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(*arr))

typedef enum BasedAlgo {
  B64,
  B64URL,
  B32,
  B32HEX,
  /* B16, */
} BasedAlgo;

static char *algo_names[] = {
  [B64]    = "based64",
  [B64URL] = "based64_url",
  [B32]    = "based32",
  [B32HEX] = "based32_hex",
  /* [B16]    = "based16", */
};

typedef struct BasedTestCase {
  BasedAlgo algo;
  char *clear_text;
  char *based_text;
} BasedTestCase;

const BasedTestCase test_cases[] = {
   { B64,    "",                            ""                                     },
   { B64,    "f",                           "Zg=="                                 },
   { B64,    "fo",                          "Zm8="                                 },
   { B64,    "foo",                         "Zm9v"                                 },
   { B64,    "foob",                        "Zm9vYg=="                             },
   { B64,    "fooba",                       "Zm9vYmE="                             },
   { B64,    "foobar",                      "Zm9vYmFy"                             },
   { B64,    "Many hands make light work.", "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu" },
   { B64,    "light work.",                 "bGlnaHQgd29yay4="                     },
   { B64,    "light work",                  "bGlnaHQgd29yaw=="                     },
   { B64,    "light wor",                   "bGlnaHQgd29y"                         },
   { B64,    "light wo",                    "bGlnaHQgd28="                         },
   { B64,    "light w",                     "bGlnaHQgdw=="                         },
   { B32,    "",                            ""                                     },
   { B32,    "f",                           "MY======"                             },
   { B32,    "fo",                          "MZXQ===="                             },
   { B32,    "foo",                         "MZXW6==="                             },
   { B32,    "foob",                        "MZXW6YQ="                             },
   { B32,    "fooba",                       "MZXW6YTB"                             },
   { B32,    "foobar",                      "MZXW6YTBOI======"                     },
   { B32HEX, "",                            ""                                     },
   { B32HEX, "f",                           "CO======"                             },
   { B32HEX, "fo",                          "CPNG===="                             },
   { B32HEX, "foo",                         "CPNMU==="                             },
   { B32HEX, "foob",                        "CPNMUOG="                             },
   { B32HEX, "fooba",                       "CPNMUOJ1"                             },
   { B32HEX, "foobar",                      "CPNMUOJ1E8======"                     },
   /* { B16,    "",                            ""                                     }, */
   /* { B16,    "f",                           "66"                                   }, */
   /* { B16,    "fo",                          "666F"                                 }, */
   /* { B16,    "foo",                         "666F6F"                               }, */
   /* { B16,    "foob",                        "666F6F62"                             }, */
   /* { B16,    "fooba",                       "666F6F6261"                           }, */
   /* { B16,    "foobar",                      "666F6F626172"                         }, */
};

int main(void) {
  printf("Begin testing based algorithms!\n");

  size_t test_cases_len = ARRAY_LENGTH(test_cases);
  size_t de_cases_failed = 0;
  size_t en_cases_failed = 0;

  for (size_t i = 0; i < test_cases_len; i++) {
    BasedTestCase test_case = test_cases[i];

    printf(
      BLUE("[%2zu/%-2zu]")" Testing %11s(\"%-16s\", \"%-16s\")... ",
      i + 1,
      test_cases_len,
      algo_names[test_case.algo],
      test_case.based_text,
      test_case.clear_text
    );

    fflush(stdout);

    fn_based_encode *based_encode;
    fn_based_decode *based_decode;
    fn_based_get_len *based_get_clear_len;
    fn_based_get_len *based_get_based_len;

    switch (test_case.algo) {
      case B64:
        based_decode        = based64_decode;
        based_encode        = based64_encode;
        based_get_clear_len = based64_get_clear_len;
        based_get_based_len = based64_get_based_len;
        break;
      case B64URL:
        based_decode = based64_url_decode;
        based_encode = based64_url_encode;
        based_get_clear_len = based64_get_clear_len;
        based_get_based_len = based64_get_based_len;
        break;
      case B32:
        based_decode = based32_decode;
        based_encode = based32_encode;
        based_get_clear_len = based32_get_clear_len;
        based_get_based_len = based32_get_based_len;
        break;
      case B32HEX:
        based_decode = based32_hex_decode;
        based_encode = based32_hex_encode;
        based_get_clear_len = based32_get_clear_len;
        based_get_based_len = based32_get_based_len;
        break;
      /* case B16: */
      /*   based_decode = based16_decode; */
      /*   based_encode = based16_encode; */
      /*   break; */
    }

    size_t clear_case_len = strlen(test_case.clear_text);
    size_t based_case_len = strlen(test_case.based_text);

    size_t clear_text_len = based_get_clear_len(based_case_len);
    size_t based_text_len = based_get_based_len(clear_case_len);

    char clear[clear_text_len];
    char based[based_text_len];

    printf("EN: ");
    fflush(stdout);

    based_encode(test_case.clear_text, clear_case_len, based);

    if (strcmp(based, test_case.based_text) != 0) {
      printf(RED("FAIL"));
      en_cases_failed++;
    } else {
      printf(GREEN("PASS"));
    }

    printf(" | DE: ");
    fflush(stdout);

    based_decode(test_case.based_text, based_case_len, clear);

    if (strcmp(clear, test_case.clear_text) != 0) {
      printf(RED("FAIL"));
      de_cases_failed++;
    } else {
      printf(GREEN("PASS"));
    }

    printf("\n");
  }

  if (de_cases_failed > 0 || en_cases_failed > 0) {
    printf(RED("%zu/%zu decode tests failed")"\n", de_cases_failed, test_cases_len);
    printf(RED("%zu/%zu encode tests failed")"\n", en_cases_failed, test_cases_len);
    return 1;
  }

  printf(GREEN("All done!")"\n");
  return 0;
}
