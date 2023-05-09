#!/usr/bin/env bash
gcc -pthread client.c -o client
./client 127.0.0.1 30080