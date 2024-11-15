#!/bin/bash

# This function is meant to be added to the end of your ~/.bashrc file
# so that you can more easily compile your project
function comp {
    local filename="${1%.*}.out"
    sudo g++ -w "$1" -o "$filename" && "./$filename"
}