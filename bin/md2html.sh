#!/usr/bin/env bash
# Locates all article sources (files named source.md) and converts them into ERB files.

export PATH="$PWD/bin:$PATH"

function convert() {
    echo $dir
    # Convert markdown links
    link < source.md > out1

    # Format metadata
    fmtmd < out1 > out2

    pandoc --wrap=preserve -f markdown out2 -t html -o out3

    mv out3 index.erb

    rm -f out1 out2 out3
}


cd views/
convert

for dir in $(ls -1)
do
    if [[ ! -f $dir ]]
    then
        cd "$dir"
        if [[ -f source.md ]]
        then
            convert
        fi
        cd ..
    fi
done
cd -
