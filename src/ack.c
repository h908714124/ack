#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void logDebug(uint64_t counters[], uint64_t goals[], uint64_t value, int m);

int ackermann(uint64_t m, uint64_t n) {
  uint64_t counters[m], goals[m - 1];
  for (int i = 0; i < m - 1; i++) {
    counters[i] = 0;
    goals[i] = 1;
  }
  counters[m - 1] = 0;
  uint64_t value = 1;
  logDebug(counters, goals, value, m);
  while (counters[m - 1] != n + 1) {
    value++;
    for (int i = 0; i < m; i++) {
      if (counters[i]++ != goals[i]) {
        break;
      }
      if (i != m - 1) {
        goals[i] = value;
      }
    }
    logDebug(counters, goals, value, m);
  }
  return value;
}

void logDebug(uint64_t *counters, uint64_t *goals, uint64_t value, int m) {
  #ifdef DEBUG
  printf("%d   counters: ", value);
  for (int i = 0; i < m; i++) {
    printf("%d ", counters[i]);
  }
  printf("  goals: ");
  for (int i = 0; i < m - 1; i++) {
    printf("%d ", goals[i]);
  }
  printf("\n");
  #endif
}

int main(int argc, char **argv) {
  char* end;
  if (argc != 3) {
    printf("Expecting 2 arguments but found %d\n", argc - 1);
    return 1;
  }
  uint64_t m = strtol(argv[1], &end, 10);
  uint64_t n = strtol(argv[2], &end, 10);
  uint64_t result = ackermann(m, n);
  printf("ackermann(%d, %d) = %d\n", m, n, result);
  return 0;
}
