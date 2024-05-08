#!/usr/bin/env bash
# Locates all article sources (files named source.md) into ERB files.

export PATH="$PWD/bin:$PATH"

function convert() {
    echo $dir
    # Convert markdown links
    link < source.md > out1

    pandoc --wrap=preserve -f markdown out1 -t html -o out2

    # Format metadata
    fmtmd < out2 > out3
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
