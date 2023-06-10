#!/bin/bash

venv() {
    local VENVNAME="venv"

    if [ -d "./$VENVNAME" ]; then
        source "./$VENVNAME/bin/activate"
    else
        python3 -m venv "$VENVNAME"
        source "./$VENVNAME/bin/activate"
    fi
}
