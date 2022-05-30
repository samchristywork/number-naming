#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

char *digits[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
char *teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
char *tens[] = {"zero", "one", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"};
char *digit_prefixes[] = {"", "un", "duo", "tres", "quattuor", "quin", "ses", "sept", "octo", "noven"};
char *small_base[] = {"", "million", "billion", "trillion", "quadrillion", "quintillion", "sextillion", "septillion", "octillion", "nonillion"};
char *tens_base[] = {"", "thousand", "million", "billion", "trillion", "quadrillion", "quintillion", "sextillion", "septillion", "octillion", "nonillion", "decillion"};
char *teens_base[] = {"", "decillion", "vigintillion", "trigintillion", "quadragintillion", "quinquagintillion", "sexagintillion", "septuagintillion", "octogintillion", "nonagintillion"};

struct triple {
  int a;
  int b;
  int c;
};

void usage(char *argv[]) {
  fprintf(stderr,
          "Usage: %s [-o output file]\n"
          " -h\tDisplay this usage statement.\n"
          "",
          argv[0]);
  exit(EXIT_FAILURE);
}

/*
 * Print an error message and exit the program.
 *
 * Parameters:
 *     str: The message to print.
 */
void die(char *str) {
  printf("Error: %s\n", str);
  exit(EXIT_FAILURE);
}

/*
 * Generates a numerical string of the specified length.
 *
 * Parameters:
 *     num_digits (integer): The length of the desired numerical string.
 *
 * Returns:
 *     num_string: A string made from random digits.
 */
char *generate_numerical_string(int num_digits) {
  if (num_digits <= 0) {
    die("Number must be positive and nonzero.");
  }

  // The first digit should be 1-9.
  char *str = malloc(num_digits + 1);
  bzero(str, num_digits + 1);
  str[0] = random() % 9 + '1';

  // Subsequent digits may be 0-9.
  for (int i = 1; i < num_digits; i++) {
    str[i] = random() % 10 + '0';
  }

  return str;
}

/*
 * Turns a numerical string into an array of three digit groups.
 * Ex: "1234" -> {{0, 0, 1}, {2, 3, 4}}
 *
 * Parameters:
 *     num_string (char *): A string of digits.
 *
 * Returns:
 *     triples: An array of triples that represent the digits of the input
 * string.
 */
struct triple *group_into_triples(char *num_string, int *len) {
  for (int i = 0; i < strlen(num_string); i++) {
    if (!isdigit(num_string[i])) {
      die("String must be made of digits.");
    }
  }

  // Calculate bounds.
  int num_divisions = (strlen(num_string) + 2) / 3;
  int padding = (-strlen(num_string) - 1) % 3;
  struct triple *triples = malloc(sizeof(struct triple) * num_divisions);
  bzero(triples, sizeof(struct triple) * num_divisions);

  // Populate the `triples` array.
  for (int i = 0; i < strlen(num_string); i++) {
    int m = (i + padding) / 3;
    int n = (i + padding) % 3;
    switch (n) {
    case 0:
      triples[m].a = num_string[i] - '0';
      break;
    case 1:
      triples[m].b = num_string[i] - '0';
      break;
    case 2:
      triples[m].c = num_string[i] - '0';
      break;
    default:
      die("Invalid index.");
      break;
    }
  }

  // Return the array and its length.
  (*len) = num_divisions;
  return triples;
}

/*
 * Prints a number with separators to make human comprehension easier.
 * Ex: "3000" -> "3,000"
 *
 * Parameters:
 *     num_string: A string of digits.
 *     separator: The symbol to use to separate groupings.
 *
 * Returns:
 *     None
 */
void print_with_separators(char *num_string, char separator) {
  if (separator == 0) {
    separator = ',';
  }

  for (int i = 0; i < strlen(num_string); i++) {
    if (!isdigit(num_string[i])) {
      die("String must be made of digits.");
    }
  }

  // Turn the string into an array of triples.
  int len;
  struct triple *groups = group_into_triples(num_string, &len);

  if (len == 0) {
    return;
  }

  // Don't print leading zeroes.
  if (groups[0].b != 0) {
    if (groups[0].a != 0) {
      printf("%d", groups[0].a);
    }
    printf("%d", groups[0].b);
  }
  printf("%d", groups[0].c);

  // Print the remainder of the number.
  for (int i = 1; i < len; i++) {
    printf("%c", separator);
    printf("%d", groups[i].a);
    printf("%d", groups[i].b);
    printf("%d", groups[i].c);
  }
  printf("\n");
}

/*
 * Returns the English representation of the three digit "triple".
 * Ex: {1, 2, 3} -> "one hundred twenty three"
 *
 * Parameters:
 *     triple: An array of three digits.
 *
 * Returns:
 *     triple_string: A string representation of the provided number.
 */
char *triple_name(struct triple t) {
  char _hundreds[32];
  char _tens[32];
  char _ones[32];
  bzero(_hundreds, 32);
  bzero(_tens, 32);
  bzero(_ones, 32);

  // Populate the "hundreds" spot if it is nonzero.
  if (t.a != 0) {
    snprintf(_hundreds, 32, "%s hundred", digits[t.a]);
  }

  // The representation of the "ones" place varies based on what is in the "tens" place.
  if (t.b == 0) {
    strncpy(_ones, digits[t.c], 32);
  } else if (t.b == 1) {
    strncpy(_ones, teens[t.c], 32);
  } else {
    strncpy(_tens, tens[t.b], 32);
    strncpy(_ones, digits[t.c], 32);
  }

  // Calculate the size of the output string.
  int l = strlen(_hundreds) + strlen(_tens) + strlen(_ones);
  char *triple_string = malloc(l + 2);
  bzero(triple_string, l);

  // Construct the string from the `_hundreds`, `_tens`, and `_ones` variables.
  strncat(triple_string, _hundreds, l);
  if (strlen(_hundreds) && (strlen(_tens) || strlen(_ones))) {
    strncat(triple_string, " ", l);
  }
  strncat(triple_string, _tens, l);
  if (strlen(_tens) && strlen(_ones)) {
    strncat(triple_string, " ", l);
  }
  strncat(triple_string, _ones, l);

  return triple_string;
}

/*
 * Returns a string representing the base of a specified order.
 * Ex: 2 -> "million", 3-> "billion"
 *
 * Parameters:
 *     order: The desired "order" or "base" of the number.
 *
 * Returns:
 *     order_string: A string that represents the specified base.
 */
char *base_from_index(int order) {
  if (order < 0) {
    die("Number must be positive.");
  }
  if (order > 100) {
    die("Number is too large.");
  }

  char *base = malloc(128);
  bzero(base, 128);

  int n = order;

  // Special case.
  if (n == 0) {
    strncpy(base, "thousand", 128);
    return base;
  }

  // Special case.
  if (n == 100) {
    strncpy(base, "centillion", 128);
    return base;
  }

  // Special case.
  if (n < 10) {
    strncpy(base, small_base[n], 128);
    return base;
  }

  if (n % 10 != 0) {
    strncat(base, digit_prefixes[n % 10], 128);
  }

  strncat(base, teens_base[n / 10], 128);
  return base;
}

/*
 * Return the English representation of a string of digits.
 * Ex: "12341234" -> "twelve million, three hundred fourty one thousand, two
 * hundred thirty four"
 *
 * Parameters:
 *     num_string: A string of digits.
 *
 * Returns:
 *     num_text: The English representation of the input number.
 */
char *representation_of_number(char *num_string) {
  for (int i = 0; i < strlen(num_string); i++) {
    if (!isdigit(num_string[i])) {
      die("String must be made of digits.");
    }
  }
  if (strlen(num_string) > 306) {
    die("Number is too large.");
  }

  // Note: these are the longest numbers less than "1000" that can be written
  // out:
  //
  // three hundred seventy three
  // three hundred seventy seven
  // three hundred seventy eight
  // seven hundred seventy three
  // seven hundred seventy seven
  // seven hundred seventy eight
  // eight hundred seventy three
  // eight hundred seventy seven
  // eight hundred seventy eight

  // Because it is capped at "centillion", the largest number this program can
  // produce is:
  //
  // 373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373373,
  //
  // which is only 4741 characters long, so 5000 characters should be enough
  // for all circumstances.

  int num_text_length = 5000;
  char *num_text = malloc(num_text_length);
  bzero(num_text, 100);

  char *n = num_string;

  while (n[0] == '0') {
    n++;
  }

  if (strlen(n) == 0) {
    strncpy(num_text, "zero", 4);
    return num_text;
  }

  int len;
  struct triple *groups = group_into_triples(num_string, &len);

  for (int i = 0; i < len; i++) {

    // Skip "000" cases.
    if (groups[i].a == 0 && groups[i].b == 0 && groups[i].c == 0) {
      continue;
    }

    // Combine the triple name and the string representation of the order.
    int order = len - i - 1;
    strncat(num_text, triple_name(groups[i]), num_text_length);
    if (order != 0) {
      char *base = base_from_index(order - 1);
      strncat(num_text, " ", num_text_length);
      strncat(num_text, base, num_text_length);
      strncat(num_text, ", ", num_text_length);
      free(base);
    }
  }

  // Trim excess spaces and punctuation.
  if (num_text[strlen(num_text) - 1] == ' ') {
    num_text[strlen(num_text) - 1] = 0;
  }

  if (num_text[strlen(num_text) - 1] == ',') {
    num_text[strlen(num_text) - 1] = 0;
  }

  // Re-fit the memory.
  char *ret = malloc(strlen(num_text)+1);
  sprintf(ret, "%s", num_text);
  free(num_text);

  return ret;
}

int main(int argc, char *argv[]) {
  srand(time(0));

  FILE *outfile = NULL;

  // Handle program arguments.
  int opt;
  char *optstring = "hSo:t:";
  while ((opt = getopt(argc, argv, optstring)) != -1) {
    if (opt == 'S') {
    }
    if (opt == 'h') {
      usage(argv);
    }
    if (opt == 't') {
    }
    if (opt == 'o') {
      outfile = fopen(optarg, "wb");
      if (outfile == 0) {
        perror("fopen");
        usage(argv);
      }
    }
  }

  if (optind != argc) {
    fprintf(stderr, "Wrong number of arguments.\n");
    usage(argv);
  }

  char *num_str = generate_numerical_string(306);
  print_with_separators(num_str, 0);

  char *text;
  text = representation_of_number(num_str);
  puts(text);
  free(text);
  free(num_str);
}
