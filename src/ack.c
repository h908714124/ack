#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdint.h>

void logDebug(uint64_t counters[], uint64_t goals[], uint64_t value);

void increment(uint64_t *counters, uint64_t *goals, uint64_t value) {
  for (int i = 0; i < 6; i++) {
    if (counters[i]++ != goals[i]) {
      break;
    }
    goals[i] = value;
  }
}

void decrement(uint64_t *counters, uint64_t *goals, uint64_t value) {
  for (int i = 0; i < 6; i++) {
    counters[i]--;
    if (goals[i] != value) {
      break;
    }
    goals[i] = counters[i];
  }
}

int main() {
  char c;
  static struct termios oldt, newt;
  tcgetattr( STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);
  uint64_t counters[6], goals[6];
  for (int i = 0; i < 6; i++) {
    counters[i] = 0;
    goals[i] = 1;
  }
  uint64_t value = 1;
  logDebug(counters, goals, value);
  while (1) {
    scanf("%c", &c);
    if (c == 'j') {
      value++;
      increment(counters, goals, value);
      logDebug(counters, goals, value);
    } else if (value != 1 && c == 'k') {
      decrement(counters, goals, value);
      value--;
      logDebug(counters, goals, value);
    }
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
