#include <stdio.h>
#include <stdint.h>

void logDebug(uint64_t counters[], uint64_t goals[], uint64_t value);

int main() {
  uint64_t counters[6], goals[6];
  for (int i = 0; i < 6; i++) {
    counters[i] = 0;
    goals[i] = 1;
  }
  uint64_t value = 1;
  logDebug(counters, goals, value);
  while (1) {
    value++;
    for (int i = 0; i < 6; i++) {
      if (counters[i]++ != goals[i]) {
        break;
      }
      goals[i] = value;
    }
    logDebug(counters, goals, value);
  }
  return 0;
}

void logDebug(uint64_t *counters, uint64_t *goals, uint64_t value) {
  printf("%llu   counters: ", value);
  for (int i = 0; i < 6; i++) {
    printf("%llu ", counters[i]);
  }
  printf("  goals: ");
  for (int i = 0; i < 6; i++) {
    printf("%llu ", goals[i]);
  }
  printf("\n");
}
