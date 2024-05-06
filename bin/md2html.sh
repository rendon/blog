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
            echo $dir
            # Convert markdown links
            ~/projects/blog/bin/link < source.md > out1

            pandoc --wrap=none -f markdown out1 -t html -o out2

            # Format metadata
            ~/projects/blog/bin/fmtmd < out2 > out3
            mv out3 index.erb

            rm -f out1 out2 out3
        fi
        cd ..
    fi
done
cd -
