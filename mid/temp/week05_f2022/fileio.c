#include <stdio.h>

typedef enum {
  read_text,   /* = 0 */
  write_text,  /* = 1 */
  read_binary, /* ... */
  write_binary
} action_t;

typedef struct {
  int i;
  float f;
} file_data_t;

/* Switches -rt, -wt, -rb, -wb to read/write text/binary */
int main(int argc, char *argv[])
{
  action_t a;
  FILE *f;
  file_data_t d;
  
  if (argc != 3) {
    fprintf(stderr, "Usage [-rt|-wt|-rb|-wb] <file>\n");

    return -1;
  }

  if (argv[1][1] == 'r') {    // Reading
    if (argv[1][2] == 't') {  // Text
      a = read_text;
    } else {                  // Binary
      a = read_binary;
    }
  } else {                    // Writing
    if (argv[1][2] == 't') {  // Text
      a = write_text;
    } else {                  // Binary
      a = write_binary;
    }
  }

  switch (a) {
  case read_text:
    if ((f = fopen(argv[2], "r"))) {
      d.i = 0;
      d.f = 0;

      fscanf(f, "%d %f\n", &d.i, &d.f);

      printf("Read %d %f\n", d.i, d.f);
      
      fclose(f);
    } else {
      fprintf(stderr, "Failed to open %s.\n", argv[2]);
    }
    break;
  case write_text:
    if ((f = fopen(argv[2], "w"))) {
      d.i = 10;
      d.f = 3.14;

      fprintf(f, "%d %f\n", d.i, d.f);

      fclose(f);
    } else {
      fprintf(stderr, "Failed to open %s.\n", argv[2]);
    }
    break;
  case read_binary:
    if ((f = fopen(argv[2], "r"))) {
      d.i = 0;
      d.f = 0;

      if (fread(&d, sizeof (d), 1, f) != 1) {
        fprintf(stderr, "Error writing to %s.\n", argv[2]);
      }

      printf("Read %d %f\n", d.i, d.f);
      
      fclose(f);
    } else {
      fprintf(stderr, "Failed to open %s.\n", argv[2]);
    }
    break;
  case write_binary:
    if ((f = fopen(argv[2], "w"))) {
      d.i = 10;
      d.f = 3.14;

      if (fwrite(&d, sizeof (d), 1, f) != 1) {
        fprintf(stderr, "Error writing to %s.\n", argv[2]);
      }

      fclose(f);
    } else {
      fprintf(stderr, "Failed to open %s.\n", argv[2]);
    }
    break;
  }
  
  return 0;
}
