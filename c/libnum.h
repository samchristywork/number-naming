#ifndef LIBNUM_H
#define LIBNUM_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

struct triple {
  int a;
  int b;
  int c;
};

void usage();
void die(char *str);
char *generate_numerical_string(int num_digits);
struct triple *group_into_triples(char *num_string, int *len);
void print_with_separators(char *num_string, char separator, FILE *f);
char *triple_name(struct triple t);
char *base_from_index(int order);
char *representation_of_number(char *num_string);
void print_representation_of_number(char *number, FILE *f);
void set_program_name(char *name);

#endif
