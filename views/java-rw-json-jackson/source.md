# Read and write JSON documents in Java with Jackson
2016-02-18 2024-05-07 #dev #java #post

I'm working on my [graph tool](https://github.com/rendon/graph_illustrator/) and I just changed the file format to JSON, then the need to read and write JSON from and to a file.

What I needed was a lightweight library to parse and export JSON content, nothing fancy ... wait, with support for pretty printing, please. I ended up with Jackson, not exactly lightweight, but it did the job.

There are many libraries for this task, [json-simple](https://code.google.com/p/json-simple/), [Google Gson](https://code.google.com/p/google-gson/), [Jackson](http://jackson.codehaus.org/), to name a few. My first try was with json-simple, it's okay, but it lacks of pretty printing. I din't spend too much time on Gson, but it seems that is more suited to map JSON data to classes (and conversely). Jackson was tedious to set up because I had to guess what jar file to use, jackson-core, maybe jackson-databind, jackson-annotations, or all of them! I stayed with Jackson because the **Tree Model** seemed very convenient to read, and indeed it is.

Enough chitchat. Here is the input file that we'll parse:

Embed: `graph-sample.json`

And here is the code I used to parse it:

Embed: `read-json.java`

Compile and run with:

Embed: `compile.sh`

Download the Jars from [http://repo1.maven.org/maven2/com/fasterxml/jackson/core/](http://repo1.maven.org/maven2/com/fasterxml/jackson/core/) or use Google to find them.

Actually I don't just read the data and print it out, but store it in some data structures. Here's how the writing looks like:

Embed: `write-json.java`

This code doesn't compile by itself because it depends on some classes that I use in my project, but it gives you the idea. You can find the full source code [here](https://github.com/rendon/graph_illustrator/blob/master/src/edu/inforscience/Main.java).

I hope it helps. Bye!
