// RUN: %clang %s -fsanitize=float-divide-by-zero -emit-llvm -g %O0opt -c -o %t.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out %t.bc 2>&1 | FileCheck %s

#include "klee/klee.h"

int main() {
  float x = 1.0;

  //  klee_make_symbolic(&x, sizeof(x), "x");
  //  klee_assume(x != 0.0);

  // CHECK: ubsan_float_divide_by_zero.c:[[@LINE+1]]: overflow on division or remainder
  volatile float result = x / 0;
}
