#!/bin/bash

# This will export the following zshrc PS1 terminal settings and get my
#   terminal looking like how I preffer
# Looks like:
#
# bsawa@Z-Drive src
# ->  
#
export PS1="%{$(tput setaf 36)%}%n%{$(tput setaf 36)%}@%{$(tput setaf 36)%}%m %{$(tput setaf 36)%}%1~
%{$(tput sgr0)%}-> "

# This function is meant to be added to the end of your ~/.bashrc file
# so that you can more easily compile your project
function comp {
    local filename="${1%.*}.out"
    sudo g++ -w "$1" -o "$filename" && "./$filename" "${@:2}"
}