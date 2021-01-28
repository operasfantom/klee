// REQUIRES: geq-llvm-10.0

// RUN: %clang %s -fsanitize=pointer-overflow -emit-llvm -g %O0opt -c -o %t.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out %t.bc 2>&1 | FileCheck %s

#include "klee/klee.h"
#include <stdio.h>

int main() {
  size_t address;
  volatile char *result;

  klee_make_symbolic(&address, sizeof(address), "address");

  char *ptr = (char *)address;

  // CHECK: ubsan_pointer_overflow-applying_nonzero_offset_to_null_pointer.c:[[@LINE+1]]: applying non-zero offset 1 to null pointer
  result = ptr + 1;
  return 0;
}
