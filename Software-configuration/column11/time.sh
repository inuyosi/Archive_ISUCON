#!/bin/bash

s=$(date +%s.%6N)
eval "$@"
t=$(date +%s.%6N)
echo "scale=1; $t - $s"|bc
