#include <valgrind/callgrind.h>

int main(int argc, char** argv) {
    CALLGRIND_START_INSTRUMENTATION;

    // Your program logic goes here

    int c;

    // for (c = 0; c < 2; c++) {
    //     c = c + 1;
    // }

    // for (c = 0; c < 2; c++) {
    //     c = c + 1;
    // }

    for (c = 0; c < 2; c++) {
        c = c + 1;
    }
    CALLGRIND_STOP_INSTRUMENTATION;
    CALLGRIND_DUMP_STATS;

    return 0;
}