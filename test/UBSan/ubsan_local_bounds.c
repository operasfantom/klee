// REQUIRES: geq-llvm-20.1
// RUN: %clang %s -fsanitize=local-bounds -fno-sanitize-trap=local-bounds -fsanitize-recover=local-bounds -emit-llvm -g %O0opt -c -o %t.bc
// RUN: rm -rf %t.klee-out
// RUN: %klee --output-dir=%t.klee-out --emit-all-errors --ubsan-runtime %t.bc 2>&1 | FileCheck %s
// RUN: ls %t.klee-out/ | grep .ktest | wc -l | grep 1
// RUN: ls %t.klee-out/ | grep .local_bounds.err | wc -l | grep 1

int main(void) {
  int data[4] = {0, 1, 2, 3};

  // CHECK: KLEE: ERROR: {{.*}}runtime/Sanitizer/ubsan/ubsan_handlers.cpp:{{[0-9]+}}: local-out-of-bounds
  return data[4];
}
