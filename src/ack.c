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
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  curs_set(0);
  int col, row;
  getmaxyx(stdscr, row, col);
  uint64_t counters[MAX_ACK], goals[MAX_ACK];
  uint64_t scrollsize = row / 2;
  uint64_t input = 0;
  for (int i = 0; i < MAX_ACK; i++) {
    counters[i] = 0;
    goals[i] = 1;
  }
  uint64_t value = 1;
  printScreen(counters, goals, value);
  outer: while (1) {
    scanf("%c", &c);
    switch (c) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        input *= 10;
        input += (c - '0');
        break;
      case 'j':
        value++;
        increment(counters, goals, value);
        printScreen(counters, goals, value);
        input = 0;
        break;
      case 'k':
        if (value != 1) {
          decrement(counters, goals, value);
          value--;
          printScreen(counters, goals, value);
        }
        input = 0;
        break;
      case 'u':
        if (input != 0) {
          scrollsize = input;
        }
        for (int i = 0; i < scrollsize; i++) {
          if (value == 1) {
            break;
          }
          decrement(counters, goals, value);
          value--;
        }
        printScreen(counters, goals, value);
        input = 0;
        break;
      case 'd':
        if (input != 0) {
          scrollsize = input;
        }
        for (int i = 0; i < scrollsize; i++) {
          value++;
          increment(counters, goals, value);
        }
        printScreen(counters, goals, value);
        input = 0;
        break;
      case 'q':
        endwin();
        return 0;
    }
  }
}

void printArray(uint64_t *ar) {
  for (int i = 0; i < MAX_ACK; i++) {
    printw("%llu ", ar[i]);
  }
}

void printRow(uint64_t *counters, uint64_t *goals, uint64_t value) {
  printw("%llu   counters: ", value);
  printArray(counters);
  printw("  goals: ");
  printArray(goals);
  printw("\n");
}

void printScreen(uint64_t *counters, uint64_t *goals, uint64_t value) {
  uint64_t goalsCopy[MAX_ACK];
  uint64_t countersCopy[MAX_ACK];
  memcpy(goalsCopy, goals, MAX_ACK * sizeof(uint64_t));
  memcpy(countersCopy, counters, MAX_ACK * sizeof(uint64_t));
  clear();
  int col, row;
  getmaxyx(stdscr, row, col);
  for (int i = 0; i < row; i++) {
    printw("%llu   counters: ", value);
    printArray(countersCopy);
    int match = 1;
    if (i == 0) {
      printw("  goals: ");
      for (int i = 0; i < MAX_ACK; i++) {
        if (goals[i] == 1) {
          break;
        }
        if (match == 1 && goals[i] == counters[i]) {
          attron(COLOR_PAIR(2));
          printw("%llu ", goals[i]);
          attroff(COLOR_PAIR(2));
          continue;
        }
        attron(COLOR_PAIR(1));
        printw("%llu ", goals[i]);
        attroff(COLOR_PAIR(1));
        match = 0;
      }
    }
    printw("\n");
    value++;
    increment(countersCopy, goalsCopy, value);
  }
  refresh();
}
