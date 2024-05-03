#!/usr/bin/env bash
# Locates all article sources (files named source.md) into ERB files.
cd views/
for dir in $(ls -1)
do
    if [[ ! -f $dir ]]
    then
        cd "$dir"
        if [[ -f source.md ]]
        then
            pandoc source.md -t html -o index.erb
        fi
        cd -
    fi
done
cd -
