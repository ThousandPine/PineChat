#!/usr/bin/env bash
if [ $# -eq 0 ]; then
    make run_client
else
    cd $1
fi

./client 127.0.0.1 30080