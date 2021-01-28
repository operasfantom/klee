// RUN: %clang %s -fsanitize=float-cast-overflow -emit-llvm -g %O0opt -c -o %t.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out %t.bc 2>&1 | FileCheck %s

#include "klee/klee.h"

int main() {
  float f = 0x7fffff80;
  volatile int result;

  //  klee_make_symbolic(&f, sizeof(f), "f");

  // CHECK: ubsan_float_cast_overflow.c:[[@LINE+1]]: floating point value is outside the range of representable values
  result = f + 0x80;
  return 0;
}
