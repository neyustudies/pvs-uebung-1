#!/usr/bin/env bash

D_MAX=500

test_once() {
    DIMS="$(($RANDOM % D_MAX)) $(($RANDOM % D_MAX)) $(($RANDOM % D_MAX))"
    echo "Dimensions: $DIMS"
    build/source/matmult $DIMS test || exit 1
}

for i in {1..100}; do
    test_once
done
