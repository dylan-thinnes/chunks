#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exit_usage (char* msg) {
    if (msg != NULL) fprintf(stderr, "ERROR: %s\n", msg);
    fprintf(stderr, "Usage: chunks [--help] [--delimiter <d> | --zero] <chunk size>.\n");
    exit(1);
}

void main (int argc, char** argv) {
  int chunk_size;
  char* delimiter = "\n";

  int delimiter_already_set = 0;
  int chunk_size_already_set = 0;

  for (int arg_ii = 1; arg_ii < argc; arg_ii++) {
    char* arg = argv[arg_ii];
    if (0 == strcmp("-d", arg) || 0 == strcmp("--delimiter", arg)) {
      if (delimiter_already_set)
        exit_usage("Tried to set delimiter more than once.");

      arg_ii++;
      if (arg_ii >= argc)
        exit_usage("Delimiter flag started, but no delimiter supplied.");

      delimiter = argv[arg_ii];
      delimiter_already_set = 1;
    } else if (0 == strcmp("-z", arg) || 0 == strcmp("--zero", arg)) {
      if (delimiter_already_set)
        exit_usage("Tried to set delimiter more than once.");

      delimiter = NULL;
      delimiter_already_set = 1;
    } else if (0 == strcmp("-h", arg) || 0 == strcmp("--help", arg)) {
      exit_usage(NULL);
    } else {
      if (chunk_size_already_set)
        exit_usage("Tried to set chunk size more than once.");

      int success = sscanf(arg, "%d", &chunk_size);
      if (success != 1)
        exit_usage("Chunk size is not a number.");

      chunk_size_already_set = 1;
    }
  }

  int i = chunk_size;

  int c;
  while (EOF != (c = getc(stdin))) {
    putc(c, stdout);

    i--;
    if (i == 0) {
      if (delimiter == NULL) {
        putc(0, stdout);
      } else {
        printf("%s", delimiter);
      }
      i = chunk_size;
    }
  }

  if (i != chunk_size) {
    if (delimiter == NULL) {
      putc(0, stdout);
    } else {
      printf("%s", delimiter);
    }
  }
}
