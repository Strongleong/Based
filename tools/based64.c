#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define SHIFT_ARGS(argc, argv) do { argc--; argv++; } while (0)

static bool is_arg(char *str, char *a, char *b, char *c) {
  return strcmp(str, a) == 0 || strcmp(str, b) == 0 || strcmp(str, c) == 0;
}

static void usage(void) {
  fprintf(stderr, "Usage: based64 [OPTIONS] ... [FILE]\n");
  fprintf(stderr, "Based64 encode or decode FILE or standart input, to standard output.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "With no FILE, or when FILE is -, read standard input.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "Mandatory arguments to long options are mandatory for short options too.\n");
  fprintf(stderr, "  -d  --decode          decode data\n");
  fprintf(stderr, "  -i  --ignore-garbage  when decoding, ignore non-alphabet characters\n");
  fprintf(stderr, "  -w  --wrap=COLS       wrap encoded lines after COLS character (default 76).\n");
  fprintf(stderr, "                          Use 0 to disable line wrapping\n");
  fprintf(stderr, "      --help        wrap encoded lines after COLS character (default 76).\n");
  fprintf(stderr, "      --version     wrap encoded lines after COLS character (default 76).\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "The data are encoded as described for the based64 alphabet in RFC 4648.\n");
  fprintf(stderr, "When decoding, the input may contain newlines in addition to the bytes of\n");
  fprintf(stderr, "the formal based64 alphabet.  Use --ignore-garbage to attempt to recover\n");
  fprintf(stderr, "from any other non-alphabet bytes in the encoded stream.\n");
}

int main(int argc, char* argv[]) {
  SHIFT_ARGS(argc, argv);

  if (argc == 0) {
    usage();
    return 1;
  }

  bool decode = false;
  bool ignore_garbage = false;

  if (**argv == '-') {
    if (is_arg(*argv, "--decode", "-d", "d")) {
      SHIFT_ARGS(argc, argv);
      decode = true;
    } else if (is_arg(*argv, "--ignore-garbage", "-i", "i")) {
      SHIFT_ARGS(argc, argv);
      ignore_garbage = true;
    } else if (strcmp(*argv, "--help") == 0) {
      usage();
      return 0;
    } else if (strcmp(*argv, "--version") == 0) {
      fprintf(stderr, "based64 (based) 1.0\n");
      return 0;
    } else {
      fprintf(stderr, "based64: unrecognized optnon '%s'\n", *argv);
      fprintf(stderr, "based64: Try 'based64 --help' for more information.\n");
      return 1;
    }
  }

  return 0;
}
