#!/usr/bin/env bash
set -euo pipefail

exec >/dev/null 2>&1

input_file="${1:-main.tex}"
output_dir="output"
log_file="$output_dir/build.log"
num_iter=2

if [[ ! -d "$output_dir" ]]; then
  mkdir -p "$output_dir"
  num_iter=3
fi

: > "$log_file"

for ((i = 1; i <= num_iter; i++)); do
  pdflatex -shell-escape -interaction=nonstopmode -halt-on-error \
    -output-directory="$output_dir" "$input_file" >> "$log_file" 2>&1
done
