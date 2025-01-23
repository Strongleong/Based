#include <stdio.h>
#include <string.h>

#define SHIFT_ARGS(argc, argv) do { argc--; argv++; } while (0)

void usage(const char *prog_name) {
  fprintf(stderr, "Usage: %s [params] <aphabet>\n", prog_name);
  fprintf(stderr, "Additional params:\n");
  fprintf(stderr, "    -h  --help     Prints this usage\n");
  fprintf(stderr, "    -v  --version  Prints version\n");
  fprintf(stderr, "    -n  --name     Name of alphabet\n");
  fprintf(stderr, "Examples:\n");
  fprintf(stderr, "    %s \"abcdABCD123!@#\"\n", prog_name);
  fprintf(stderr, "    %s --name base19_awesomeness \"AWESOMEawesome\"\n", prog_name);
}

static char *alphabet_name = "alphabet";

int main(int argc, char *argv[]) {
  char *prog_name = argv[0];
  SHIFT_ARGS(argc, argv);

  if (argc == 0) {
    usage(prog_name);
    return 1;
  }

  if (**argv == '-') {
    if (strcmp(*argv, "--name") == 0 || strcmp(*argv, "-n") == 0) {
      SHIFT_ARGS(argc, argv);
      alphabet_name = *argv;
      SHIFT_ARGS(argc, argv);
    } else if (strcmp(*argv, "--help") == 0 || strcmp(*argv, "-h") == 0) {
      usage(prog_name);
      return 0;
    } else if (strcmp(*argv, "--version") == 0 || strcmp(*argv, "-v") == 0) {
      printf("v1.0.0\n");
      return 0;
    } else {
      printf("ERROR: Unknown argument %s\n", *argv);
      return 1;
    }
  }

  if (argc == 0) {
    usage(prog_name);
    return 1;
  }

  char *alphabet = argv[0];
  size_t alphabet_len = strlen(alphabet);

  unsigned char decode_table[256] = {0};

  for (size_t i = 0; i < alphabet_len; i++) {
    decode_table[(unsigned)alphabet[i]] = i;
  }

  printf("static const unsigned char decode_table_%s[256] =\n", alphabet_name);
  printf("{\n  ");
  char buffer[5];

  for (size_t i = 0; i < 255; i++) {
    // Additional sprintf to align coma with digit
    sprintf(buffer, "%d,", decode_table[i]);
    printf("%-3s ", buffer);
    memset(buffer, 0, 5);

    if (i % 16 == 15) {
      printf("\n  ");
    }
  }

  printf("%-2d\n};\n", decode_table[255]);

  return 0;
}
