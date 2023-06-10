#!/bin/bash

push() {
    git add -u
    git commit --amend --no-edit
    git push --force
}
