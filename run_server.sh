#!/usr/bin/env bash
gcc -pthread server.c -o server
./server 30080