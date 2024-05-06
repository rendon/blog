#!/usr/bin/env bash
# # Locates all article sources (files named source.md) into ERB files.
cd public/pictures/
for dir in $(ls -1)
do
    if [[ ! -f $dir ]]
    then
        cd "$dir"
        mv -v * ~/projects/blog/views/$dir/
        cd -
    fi
done
cd -
