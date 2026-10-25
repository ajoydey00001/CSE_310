#!/bin/bash
set -e
cd -- "$(dirname -- "$0")"
bash ../script.sh "${1:-Sample Input :Output File/input.txt}"
