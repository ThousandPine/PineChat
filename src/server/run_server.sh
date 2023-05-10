#!/usr/bin/env bash
if [ $# -eq 0 ]; then
    make run_server
else
    cd $1
fi

./server 30080