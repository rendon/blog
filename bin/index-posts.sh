#!/usr/bin/env bash

echo '# All posts' > views/all/source.md
echo > views/all/source.md
while read file
do
    slug=$(basename $file)

    if [[ $slug == "all" ]]; then continue; fi

    echo "- [$slug](/$slug)" >> views/all/source.md
done < <(fd . -t d 'views/')
