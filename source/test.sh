#!/usr/bin/env bash

D_MAX=500

test_once() {
    DIMS="$(($RANDOM % D_MAX + 1)) $(($RANDOM % D_MAX + 1)) $(($RANDOM % D_MAX + 1))"
    echo "Dimensions: $DIMS"
    ./matmult $DIMS test || exit 1
}

for i in {1..100}; do
    test_once
done

./matmult 2000 2000 2000 test || exit 1
