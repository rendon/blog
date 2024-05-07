#!/usr/bin/env bash

function convert() {
    # sed -i "s/<%= file(post, '\([^']*\)', '\([^']*\)') %>/[\2](\1)/g" source.md
    # sed -i "s/<%= src_file(post, '\([^']*\)') %>/[\1](\1)/g" source.md

    # # <%= link_to('http://adventofcode.com/', 'Advent of Code', target: :blank) %>
    # sed -i "s/<%= link_to('\([^']*\)', '\([^']*\)',[^)]*) %>/[\2](\1)/g" source.md
    # sed -i "s/<%= link_to_post('\([^']*\)', '\([^']*\)') %>/[\2](\1)/g" source.md

    # sed -i '/<%= initialize(); %>/d' source.md
    # sed -i '/<%= finalize(); %>/d' source.md

    # # Sections
    # sed -i "s/<%= section('\(.*\)');  %>/## \1/g" source.md
    # sed -i 's/<%= section("\(.*\)");  %>/## \1/g' source.md

    # sed -i "s/<%= subsection('\(.*\)');  %>/### \1/g" source.md
    # sed -i 's/<%= subsection("\(.*\)");  %>/### \1/g' source.md

    # sed -i 's/<%= subsubsection("\([^"]*\)");\? %>/#### \1/g' source.md
    # sed -i "s/<%= subsubsection('\([^']*\)');\? %>/#### \1/g" source.md


    # # # code blocks
    # # Inline code
    # sed -i 's/<code>\([^<]*\)<\/code>/`\1`/g' source.md
    # sed -i "s/<%= code(post, '\([^']*\)') %>/Embed: \`\1\`/g" source.md
    # sed -i 's/<%= code(post, "\([^"]*\)") %>/Embed: `\1`/g' source.md
    # #
    # # figures
    # sed -i "s/<%= figure(post, '\([^.]*\).\(\w*\)', caption: '\([^']*\)'.*$/\![\3](\1.\2)/g" source.md
    # sed -i 's/<%= figure(post, "\([^.]*\).\(\w*\)", caption: "\([^"]*\)".*$/\![\3](\1.\2)/g' source.md
    # #
    # # # Titles
    # sed -i "s/<% @title = '\([^']*\)' %>/# \1/g" source.md
    # sed -i 's/<% @title = "\([^"]*\)" %>/# \1/g' source.md
    # #
    # #
    # # Equations
    # sed -i "s/<%= equation('\([^']*\)',.*$/\$\$\1\$\$/g" source.md
    # sed -i 's/<%= equation("\([^"]*\)",.*$/\$\$\1\$\$/g' source.md
    # #
    # # # bib table
    # sed -i '/<%= generate_bib_table();\? %>/d' source.md

    # # add_bib
    # # <%= add_bib('edxai', 'Dan Klein and Pieter Abbeel', 'CS188.1x Artificial Intelligence', 'https://courses.edx.org/courses/BerkeleyX/CS188.1x/2013_Spring/info'); %>
    # sed -i "s/<%= add_bib('\([^']*\)', *'\([^']*\)', *'\([^']*\)', *'\([^']*\)');\? %>/- [\3](\4)/g" source.md
    # sed -i 's/<%= add_bib("\([^"]*\)", *"\([^"]*\)", *"\([^"]*\)", *"\([^"]*\)");\? %>/- [\3](\4)/g' source.md

    # sed -i "s/<% add_bib('\([^']*\)', *'\([^']*\)', *'\([^']*\)', *'\([^']*\)');\? %>/- [\3](\4)/g" source.md
    # sed -i 's/<% add_bib("\([^"]*\)", *"\([^"]*\)", *"\([^"]*\)", *"\([^"]*\)");\? %>/- [\3](\4)/g' source.md

    # sed -i "s/add_bib('\([^']*\)', *'\([^']*\)', *'\([^']*\)', *'\([^']*\)');\?/- [\3](\4)/g" source.md

    # sed -i "s/!\[\(.*\)\](\(.*\))/![\1](\/$1\/\2)/g" source.md
    # sed -i "/tex_set/d" source.md
    
    # <%= ref('dns_wicd_conf'); %>
    sed -i "s/<%= ref('.*') %>//g" source.md
    sed -i "s/<%= ref('.*'); %>//g" source.md


    sed -i 's/<%= ref(".*") %>//g' source.md
    sed -i 's/<%= ref(".*"); %>//g' source.md
}


# Locates all article sources (files named source.md) into ERB files.
cd views/
for dir in $(ls -1)
do
    if [[ ! -f $dir ]]
    then
        cd "$dir"
        if [[ -f source.md ]]
        then
            convert $dir
        fi
        cd -
    fi
done
cd -
