#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_MAX_ALPHA_VALUE 123
#define MAX_PRIORITY 57
#define OCCURENCES_LEN MAX_PRIORITY + 1
static const unsigned short priority_lookup[ASCII_MAX_ALPHA_VALUE] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  27, 28, 29, 30, 31, 32, 33,
    34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
    52, 0,  0,  0,  0,  0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
    12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};

#define GROUPS_LEN 3

int exists(char c, const char *other);

unsigned short part_one(const char *line, size_t len) {
  size_t first_compartment_len = strlen(line) / 2;
  char *first_compartment = (char *)line;
  char *second_compartment = first_compartment + first_compartment_len;

  for (size_t i = 0; i < first_compartment_len; i++) {
    char item = first_compartment[i];
    if (exists(item, second_compartment)) {
      return priority_lookup[item];
    }
  }
  return 0;
}

int occurences[GROUPS_LEN][OCCURENCES_LEN] = {{0}};

int exists_in_others(unsigned short prio) {
  int exists_count = 0;
  for (size_t group = 1; group < GROUPS_LEN; group++) {
    for (size_t p = 1; p < OCCURENCES_LEN; p++) {
      unsigned short occurence_prio = occurences[group][p];
      if (occurence_prio > 0 && occurence_prio == prio) {
        exists_count++;

        if (exists_count == 2)
          return 1;
      }
    }
  }
}
unsigned short get_group_priority() {
  for (size_t prio = 1; prio < OCCURENCES_LEN; prio++) {
    if (occurences[0][prio] > 0 && occurences[1][prio] > 0 &&
        occurences[2][prio] > 0) {
      return prio;
    }
  }
}

void clear_occurences() {
  for (size_t i = 0; i < GROUPS_LEN; i++) {
    for (size_t k = 0; k < OCCURENCES_LEN; k++) {
      occurences[i][k] = 0;
    }
  }
}

unsigned short part_two(const char *line, size_t len) {
  static size_t group_counter = 0;

  for (size_t i = 0; i < len; i++) {
    char item = line[i];
    unsigned short item_priority = priority_lookup[item];
    occurences[group_counter][item_priority] += 1;
  }

  if (group_counter == 2) {
    unsigned short group_priority = get_group_priority();

    group_counter = 0;
    clear_occurences();
    return group_priority;
  }

  group_counter++;
  return 0;
}

int main(void) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  unsigned int total_priority = 0;

  fp = fopen("input.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  while ((read = getline(&line, &len, fp)) != -1) {
    total_priority += part_one(line, len);
  }

  fclose(fp);
  if (line)
    free(line);
  puts("C");
  printf("%u\n", total_priority);
  exit(EXIT_SUCCESS);
}

int exists(char c, const char *other) {
  char *tmp = (char *)other;
  while (*tmp) {
    if (c == *tmp++) {
      return 1;
    }
  }
  return 0;
}
