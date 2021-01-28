// REQUIRES: geq-llvm-8.0

// RUN: %clang %s -fsanitize=alignment -emit-llvm -g %O0opt -c -o %t.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out %t.bc 2>&1 | FileCheck %s

#include "klee/klee.h"
#include <stdlib.h>

int main() {
  size_t address;

  klee_make_symbolic(&address, sizeof(address), "address");

  char *ptr = (char *)address;

  // CHECK: ubsan_alignment-assumption.c:[[@LINE+1]]: assumption of 32768 byte alignment failed
  __builtin_assume_aligned(ptr, 0x8000);

  return 0;
}
