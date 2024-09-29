#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdint.h>
#include <curses.h>
#include <string.h>

static const int MAX_ACK = 6;

void printScreen(uint64_t counters[], uint64_t goals[], uint64_t value);

void increment(uint64_t *counters, uint64_t *goals, uint64_t value) {
  for (int i = 0; i < MAX_ACK; i++) {
    if (counters[i]++ != goals[i]) {
      break;
    }
    goals[i] = value;
  }
}

void decrement(uint64_t *counters, uint64_t *goals, uint64_t value) {
  for (int i = 0; i < MAX_ACK; i++) {
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
  curs_set(0);
  uint64_t counters[MAX_ACK], goals[MAX_ACK];
  for (int i = 0; i < MAX_ACK; i++) {
    counters[i] = 0;
    goals[i] = 1;
  }
  uint64_t value = 1;
  printScreen(counters, goals, value);
  while (1) {
    scanf("%c", &c);
    if (c == 'j') {
      value++;
      increment(counters, goals, value);
      printScreen(counters, goals, value);
    } else if (c == 'k' && value != 1) {
      decrement(counters, goals, value);
      value--;
      printScreen(counters, goals, value);
    } else if (c == 'u') {
      for (int i = 0; i < 20; i++) {
        if (value == 1) {
          break;
        }
        decrement(counters, goals, value);
        value--;
      }
      printScreen(counters, goals, value);
    } else if (c == 'd') {
      for (int i = 0; i < 20; i++) {
        value++;
        increment(counters, goals, value);
      }
      printScreen(counters, goals, value);
    } else if (c == 'q') {
      break;
    }
  }
  endwin();
  return 0;
}

void printRow(uint64_t *counters, uint64_t *goals, uint64_t value) {
  printw("%llu   counters: ", value);
  for (int i = 0; i < MAX_ACK; i++) {
    printw("%llu ", counters[i]);
  }
  printw("  goals: ");
  for (int i = 0; i < MAX_ACK; i++) {
    printw("%llu ", goals[i]);
  }
  printw("\n");
}

void printScreen(uint64_t *counters, uint64_t *goals, uint64_t value) {
  uint64_t goalsCopy[MAX_ACK];
  uint64_t countersCopy[MAX_ACK];
  memcpy(goalsCopy, goals, MAX_ACK * sizeof(uint64_t));
  memcpy(countersCopy, counters, MAX_ACK * sizeof(uint64_t));
  clear();
  printRow(countersCopy, goalsCopy, value);
  int col, row;
  getmaxyx(stdscr, row, col);
  for (int i = 1; i < row; i++) {
    value++;
    increment(countersCopy, goalsCopy, value);
    printRow(countersCopy, goalsCopy, value);
  }
  refresh();
}
