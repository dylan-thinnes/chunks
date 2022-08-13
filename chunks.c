#include <stdio.h>
#include <stdlib.h>

void main (int argc, char** argv) {
  int n;

  if (argc <= 1 || argc > 2) {
    printf("Usage: chunks <n>, where n is the number of bytes per chunk.\n");
    printf("Received %d arguments instead.\n", argc - 1);
    exit(1);
  }

  int success = sscanf(argv[1], "%d", &n);
  if (success != 1) {
    printf("Usage: chunks <n>, where n is the number of bytes per chunk.\n");
    printf("Argument '%s' is not a number.\n", argv[1]);
    exit(1);
  }

  int i = n;

  int c;
  while (EOF != (c = getc(stdin))) {
    putc(c, stdout);

    i--;
    if (i == 0) {
      putc('\n', stdout);
      i = n;
    }
  }

  if (i != n) {
    putc('\n', stdout);
  }
}
