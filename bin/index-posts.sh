#!/usr/bin/env bash

FD="fd"
# The fd-find package names the binary fdfind because of a name collision.
if [[ ! $(which fd) ]]
then
    FD="fdfind"
fi

echo '# All posts' > views/all/source.md
echo >> views/all/source.md
while read file
do
    slug=$(basename $file)

    if [[ $slug == "all" ]]; then continue; fi

    echo "- [$slug](/$slug)" >> views/all/source.md
done < <($FD . -t d 'views/')
