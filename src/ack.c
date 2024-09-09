#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int ackermann(long m, long n) {
  long next[m + 1];
  long goal[m + 1];
  for (int i = 0; i < m; i++) {
    next[i] = 0;
    goal[i] = 1;
  }
  next[m] = 0;
  goal[m] = -1;
  next[0] = 1;
  long value = 1;
  do {
    value++;
    for (int i = 1; i <= m; i++) {
      int ni = next[i];
      next[i]++;
      if (ni != goal[i]) {
        break;
      }
      goal[i] = value;
    }
    #ifdef DEBUG
    printf("next: ");
    for (int i = 0; i <= m; i++) {
      printf("%ld ", next[i]);
    }
    printf(", goal: ");
    for (int i = 0; i <= m; i++) {
      printf("%ld ", goal[i]);
    }
    printf("\n");
    #endif
  } while (next[m] != n + 1);
  return value;
}

int stackermann(long mm, long nn) {
  int length = 2;
  int size = 120000 * mm;
  int maxstack = 2;
  long stack[size];
  stack[0] = mm;
  stack[1] = nn;
  while (length != 1) {
    long m = stack[length - 2];
    long n = stack[length - 1];
    #ifdef DEBUG
    for (int i = 0; i < length; i++) {
      printf("%ld ", stack[i]);
    }
    printf("\n");
    #endif
    if (m == 0) {
      stack[length - 2] = n + 1;
      length--;
    } else if (n == 0) {
      stack[length - 2] = m - 1;
      stack[length - 1] = 1;
    } else {
      stack[length - 2] = m - 1;
      stack[length - 1] = m;
      stack[length] = n - 1;
      length++;
      if (length == size) {
        printf("stack overflow\n");
        return -1;
      }
      if (length > maxstack) {
        maxstack = length;
      }
    }
  }
  printf("max stack: %d\n", maxstack);
  return stack[0];
}

int main(int argc, char **argv) {
  char* end;
  if (argc != 3) {
    printf("Expecting two arguments but found %d\n", argc - 1);
    return 1;
  }
  long m = strtol(argv[1], &end, 10);
  long n = strtol(argv[2], &end, 10);
  if (m >= 4 && n >= 2) {
    printf("ack(%ld, %ld) may take a _very_ long time to compute.\n", m, n);
    printf("Try with smaller values, or press Return to continue.\n");
    char buf[10];
    fgets(buf, 10, stdin);
  }
  long result = ackermann(m, n);
  printf("ackermann(%ld, %ld) = %ld\n", m, n, result);
//  result = stackermann(m, n);
//  printf("stackermann(%ld, %ld) = %ld\n", m, n, result);
  return 0;
}

int max(int a, int b) {
  return a < b ? b : a;
}
