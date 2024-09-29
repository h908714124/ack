#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdint.h>
#include <curses.h>

void printRow(uint64_t counters[], uint64_t goals[], uint64_t value);

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
  initscr();
  clear();
  refresh();
  uint64_t counters[6], goals[6];
  for (int i = 0; i < 6; i++) {
    counters[i] = 0;
    goals[i] = 1;
  }
  uint64_t value = 1;
  printRow(counters, goals, value);
  while (1) {
    printRow(counters, goals, value);
    scanf("%c", &c);
    if (c == 'j') {
      value++;
      increment(counters, goals, value);
    } else if (c == 'k' && value != 1) {
      decrement(counters, goals, value);
      value--;
    } else if (c == 'q') {
      break;
    }
  }
  endwin();
  return 0;
}

void printRow(uint64_t *counters, uint64_t *goals, uint64_t value) {
  clear();
  printw("%llu   counters: ", value);
  for (int i = 0; i < 6; i++) {
    printw("%llu ", counters[i]);
  }
  printw("  goals: ");
  for (int i = 0; i < 6; i++) {
    printw("%llu ", goals[i]);
  }
  printw("\n");
  refresh();
}
