#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void logDebug(uint64_t state[], uint64_t goal[], uint64_t value, uint32_t m);

uint32_t ackermann(uint64_t m, uint64_t n) {
  uint64_t state[m], goal[m - 1];
  for (uint32_t i = 0; i < m - 1; i++) {
    state[i] = 0;
    goal[i] = 1;
  }
  state[m - 1] = 0;
  uint64_t value = 1;
  logDebug(state, goal, value, m);
  while (state[m - 1] != n + 1) {
    value++;
    for (uint32_t i = 0; i < m; i++) {
      if (state[i]++ != goal[i]) {
        break;
      }
      if (i != m - 1) {
        goal[i] = value;
      }
    }
    logDebug(state, goal, value, m);
  }
  return value;
}

void logDebug(uint64_t *state, uint64_t *goal, uint64_t value, uint32_t m) {
  #ifdef DEBUG
  printf("%d   state: ", value);
  for (uint32_t i = 0; i < m; i++) {
    printf("%d ", state[i]);
  }
  printf("  goal: ");
  for (uint32_t i = 0; i < m - 1; i++) {
    printf("%d ", goal[i]);
  }
  printf("\n");
  #endif
}

uint32_t main(uint32_t argc, char **argv) {
  char* end;
  if (argc != 3) {
    printf("Expecting 2 arguments but found %d\n", argc - 1);
    return 1;
  }
  uint64_t m = strtol(argv[1], &end, 10);
  uint64_t n = strtol(argv[2], &end, 10);
  if (m >= 4 && n >= 2) {
    printf("ack(%d, %d) may take a _very_ long time to compute.\n", m, n);
    printf("Try with smaller values, or press Return to continue anyway.\n");
    char buf[10];
    fgets(buf, 10, stdin);
  }
  uint64_t result = ackermann(m, n);
  printf("ackermann(%d, %d) = %d\n", m, n, result);
  return 0;
}
