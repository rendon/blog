#!/usr/bin/env bash

while read file
do
    ~/projects/notes/bin/mm $file > tmp && mv tmp $file
done < <(fd -t f "\.md$")
