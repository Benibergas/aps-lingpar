#!/usr/bin/env bash
set -e

for cook in *.cook; do
  exp="${cook%.cook}.expected"
  out="${cook%.cook}.out"
  printf "\n=== Test %s ===\n" "$cook"
  ../cooklang "$cook" > "$out"
  if diff --strip-trailing-cr -q "$exp" "$out"; then
    echo "✔ OK"
  else
    echo "✖ FAIL"
    diff "$exp" "$out" || true
  fi
done
