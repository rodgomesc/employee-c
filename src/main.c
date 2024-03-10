#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>

#include "common.h"
#include "file.h"
#include "parse.h"

void print_usage(char *argv[])
{
  printf("Usage: %s -n -f <database file>\n", argv[0]);
  printf("\t -n: Create a new database file\n");
  printf("\t -f: (required) Path to database file\n");
}

int main(int argc, char *argv[])
{
  int dbfd = -1;
  char *filepath = NULL;
  int c;
  bool newfile = false;

  while (c = getopt(argc, argv, "nf:"), c != -1)
  {
    switch (c)
    {
    case 'n':
      newfile = true;
      break;

    case 'f':
      filepath = optarg;
      break;

    case '?':
      printf("Unknown option: %c\n", optopt);
      break;

    default:
      return -1;
    }
  }

  if (filepath == NULL)
  {
    printf("File path is required argument\n");
    print_usage(argv);
    return 0;
  }

  if (newfile)
  {
    dbfd = create_db_file(filepath);
  }

  printf("New file: %d\n", newfile);
  printf("File path: %s\n", filepath);
  return 0;
}