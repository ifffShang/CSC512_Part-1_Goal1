#!/bin/bash

# Run the program with Callgrind to profile it
valgrind --tool=callgrind ./test1.c

# The callgrind output file is usually called callgrind.out.*, where * is the process ID
# We can get the most recent file using ls
callgrind_file=$(ls -t callgrind.out.* | head -n 1)

# Extract the number of instructions from the callgrind output file
instructions=$(callgrind_annotate --auto=yes $callgrind_file | grep 'Collected' | awk '{print $2}')

echo "Instructions collected: $instructions"
