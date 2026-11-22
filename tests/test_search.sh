#!/bin/sh
set -eu
cd "$(dirname "$0")/.."
cc -std=c11 -Wall -Wextra -Werror main.c -o mini-search
trap 'rm -f mini-search' EXIT
output=$(./mini-search sample.txt Python)
printf '%s\n' "$output" | grep -Fq 'Line 1 (1 match): Python is fun.'
printf '%s\n' "$output" | grep -Fq 'Line 3 (2 matches): Python can process text. Python is powerful.'
printf '%s\n' "$output" | grep -Fq 'Matching lines: 2 | Total matches: 3'
printf '%s\n' 'PASS: keyword matching and counts'
output=$(./mini-search sample.txt banana)
printf '%s\n' "$output" | grep -Fq 'Matching lines: 0 | Total matches: 0'
printf '%s\n' 'PASS: no matches'
if ./mini-search missing.txt Python >/dev/null 2>&1; then
  echo 'FAIL: missing file should return an error'
  exit 1
fi
printf '%s\n' 'PASS: missing file error'
if ./mini-search sample.txt '' >/dev/null 2>&1; then
  echo 'FAIL: empty keyword should return an error'
  exit 1
fi
printf '%s\n' 'PASS: empty keyword error'
