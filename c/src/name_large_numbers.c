#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "libnum.h"

char *program_name;

void usage() {
  fprintf(stderr,
      "Usage: %s [-o output file] [-n number] [-i input file] [-l length] [-d delimiter]\n"
      " -e\tDon't print the number with a delimiter.\n"
      " -h\tDisplay this usage statement.\n"
      "",
      program_name);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  program_name=malloc(strlen(argv[0])+1);
  strcpy(program_name, argv[0]);

  srand(time(0));
  char *number = NULL;
  char delimiter = 0;
  int length = 306;
  int no_delimiter = 0;

  FILE *outfile = stdout;
  FILE *infile = NULL;

  // Handle program arguments.
  int opt;
  char *optstring = "ho:n:i:l:d:er";
  while ((opt = getopt(argc, argv, optstring)) != -1) {
    if (opt == 'o') {
      outfile = fopen(optarg, "wb");
      if (outfile == 0) {
        perror("fopen");
        usage();
      }
    }
    if (opt == 'n') {
      number=malloc(strlen(optarg)+1);
      bzero(number, strlen(optarg)+1);
      strncpy(number, optarg, strlen(optarg));
    }
    if (opt == 'i') {
      infile = fopen(optarg, "rb");
      if (infile == 0) {
        perror("fopen");
        usage();
      }
    }
    if (opt == 'l') {
      length = atoi(optarg);
      if(length <= 0){
        die("Invalid length.");
      }
    }
    if (opt == 'd') {
      delimiter = optarg[0];
    }
    if (opt == 'e') {
      no_delimiter=1;
    }
    if (opt == 'h') {
      usage();
    }
  }

  if (optind != argc) {
    fprintf(stderr, "Wrong number of arguments.\n");
    usage();
  }

  // Handle the case where a number was specified.
  if(number){
    if(!no_delimiter){
      print_with_separators(number, delimiter, outfile);
    }
    print_representation_of_number(number, outfile);
    exit(EXIT_SUCCESS);
  }

  // Handle the case where the program is taking a file full of numbers.
  if(infile){
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while ((nread = getline(&line, &len, infile)) != -1) {
      line[strlen(line)-1] = 0;
      if(!no_delimiter){
        print_with_separators(number, delimiter, outfile);
      }
      print_representation_of_number(line, outfile);
      fprintf(outfile, "\n");
    }

    free(line);
    fclose(infile);
    exit(EXIT_SUCCESS);
  }

  // Handle the case where the program returns a random number.
  number = generate_numerical_string(length);
  if(!no_delimiter){
    print_with_separators(number, delimiter, outfile);
  }
  print_representation_of_number(number, outfile);
  free(number);
  free(program_name);
  exit(EXIT_SUCCESS);
}
