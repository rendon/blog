# Read and write JSON documents in Java with Jackson
2016-02-18 2024-05-07 #dev #java #post

<p>I'm working on my <a href="https://github.com/rendon/graph_illustrator/" target="_blank">graph tool</a> and I just changed the file format to JSON, then the need to read and write JSON from and to a file.</p>

<p>What I needed was a lightweight library to parse and export JSON content, nothing fancy ... wait, with support for pretty printing, please. I ended up with Jackson, not exactly lightweight, but it did the job.</p>

<p>There are many libraries for this task, <a href="https://code.google.com/p/json-simple/" target="_blank">json-simple</a>, <a href="https://code.google.com/p/google-gson/" target="_blank">Google Gson</a>, <a href="http://jackson.codehaus.org/" target="_blank">Jackson</a>, to name a few. My first try was with json-simple, it's okay, but it lacks of pretty printing. I din't spend too much time on Gson, but it seems that is more suited to map JSON data to classes (and conversely). Jackson was tedious to set up because I had to guess what jar file to use, jackson-core, maybe jackson-databind, jackson-annotations, or all of them! I stayed with Jackson because the **Tree Model** seemed very convenient to read, and indeed it is.</p>

<p>Enough chitchat. Here is the input file that we'll parse:</p>

Embed: `graph-sample.json`

<p>And here is the code I used to parse it:</p>

Embed: `read-json.java`

<p>Compile and run with:</p>

Embed: `compile.sh`

<p>Download the Jars from [http://repo1.maven.org/maven2/com/fasterxml/jackson/core/](http://repo1.maven.org/maven2/com/fasterxml/jackson/core/) or use Google to find them.</p>

<p>Actually I don't just read the data and print it out, but store it in some data structures. Here's how the writing looks like:</p>

Embed: `write-json.java`

<p>This code doesn't compile by itself because it depends on some classes that I use in my project, but it gives you the idea. You can find the full source code [here](https://github.com/rendon/graph_illustrator/blob/master/src/edu/inforscience/Main.java).</p>

<p>I hope it helps. Bye!</p>
