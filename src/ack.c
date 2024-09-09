#include <stdio.h>
#include <stdlib.h>

void logDebug(long state[], long goal[], long value, int m);

int ackermann(long m, long n) {
  long state[m], goal[m - 1];
  for (int i = 0; i < m - 1; i++) {
    state[i] = 0;
    goal[i] = 1;
  }
  state[m - 1] = 0;
  long value = 1;
  logDebug(state, goal, value, m);
  while (state[m - 1] != n + 1) {
    value++;
    for (int i = 0; i < m; i++) {
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

void logDebug(long *state, long *goal, long value, int m) {
  #ifdef DEBUG
  printf("%ld   state: ", value);
  for (int i = 0; i < m; i++) {
    printf("%ld ", state[i]);
  }
  printf("  goal: ");
  for (int i = 0; i < m - 1; i++) {
    printf("%ld ", goal[i]);
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
  long m = strtol(argv[1], &end, 10);
  long n = strtol(argv[2], &end, 10);
  if (m >= 4 && n >= 2) {
    printf("ack(%ld, %ld) may take a _very_ long time to compute.\n", m, n);
    printf("Try with smaller values, or press Return to continue anyway.\n");
    char buf[10];
    fgets(buf, 10, stdin);
  }
  long result = ackermann(m, n);
  printf("ackermann(%ld, %ld) = %ld\n", m, n, result);
  return 0;
}
