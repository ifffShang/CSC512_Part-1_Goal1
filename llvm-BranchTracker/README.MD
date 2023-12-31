## Goal 1 run by:
chmod +x run.sh
./run.sh

## Manually Compile & Run
```
$ mkdir build
$ cd build
$ cmake ..
$ make
$ cd ..

$ cc -c rtlib.c
$ clang -fpass-plugin='build/skeleton/BranchTrackerPass.so' -c test1.c -g
$ cc test1.o rtlib.o
$ ./a.out
```

## Input fileX.c
```c
#include <stdio.h>

int c;

void fun(int a) {
  printf("Value of a is %d\n", a);
}

int main() {
  void (*fun_ptr)(int) = &fun;
  (*fun_ptr)(10);


  int d;
  for (c = 0; c < 3; c++) {
    d = c + 1;
  }

  int b;
  for (c = 0; c < 3; c++) {
    b = c + 1;
  }

  return c;
}

```

## Output
```
main: func_0x9aa458
Branch Dictionary:
br_0: /home/yifei/Desktop/llvm-pass-skeleton-2/fileX.c, 15, 16
br_1: /home/yifei/Desktop/llvm-pass-skeleton-2/fileX.c, 15, 19
br_2: /home/yifei/Desktop/llvm-pass-skeleton-2/fileX.c, 20, 21
br_3: /home/yifei/Desktop/llvm-pass-skeleton-2/fileX.c, 20, 24

cc fileX.o rtlib.o
./a.out
Value of a is 10
br_0
br_0
br_0
br_1
br_2
br_2
br_2
br_3
```


## Goal 2 find the number of instructions:
## count instructions run by 

chmod +x get_instructions.sh
./get_instructions.sh

## output: 
check "Collected" number

## or mannually run in the terminal
```
gcc -g count_instructions_tool.c -o count_instructions_tool
valgrind --tool=callgrind ./count_instructions_tool
kcachegrind callgrind.out.<pid>
callgrind_annotate callgrind.out.<pid>
callgrind_annotate callgrind.out.<pid>.1 | grep -i "TOTALS" | awk '{print $1}'
```

