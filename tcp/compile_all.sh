#!/usr/bin/env bash
for file in *.c; do
    exe=$(basename "$file" .c)
    gcc -pthread "$file" -o "$exe"
done