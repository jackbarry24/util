#!/bin/bash

pd() {
    local level="${1:-1}"
    local dir=""
    for ((i=0; i < level; i++)); do
        dir="../$dir"
    done
    cd "$dir"
}
