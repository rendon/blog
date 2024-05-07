# Huffman encoding
2016-02-18 2024-05-07 #algorithms #data-structures #post

Data compression is an interesting topic, and at last I had some time to explore this topic a little bit.

To keep things simple, we are going to compress text, characters that can be represented in 8 bits, a typical `char` type (usually) in C/C++.

## Basic idea

Even though 8 bits are used to represent each character, most characters don't use all the bits, for example, the ' ' (space) needs just 6 and the letter 'A' can be represented with 7 bits. If we could make the more frequent characters in a text have the shortest bit representation and the less frequent have the largest bit representation, using these new representations the number of bits needed to represent the orignal text could be reduced.

The Huffman coding algorithm finds an optimal representation for each character given the frequency of each of them in the original text.

The algorithm works as follows:

<ol>
  <li>Build a binary tree using the original characters as the leafs.</li>
  <li>The tree must be constructed in such a way that the most frequent characters have the shortest paths from the root to the leafs.</li>
  <li>Initially create a node for each character and its frequency in the text, keep these nodes in a list.</li>
  <ol>
    <li>Remove from the list the two nodes with minimum frequency, if there are many options, choose any of them.</li>
    <li>Take the sum of the frequencies of these two nodes and create a new one with frequency equal to the sum and character null.</li>
    <li>Repeat the previous two steps until just one node remains in the list. A priority queue is essential to make this procedure efficient.</li>
  </ol>
  <li>The new representation for each character is the sequence of bits from the root to the leafs, a '0' if you go to the left and a '1' if to the right, or conversely.</li>
  <li>Using the new codes just make the translation for each character in the text.</li>
</ol>

![Huffman Tree for the string "this is an example of a huffman tree" --Wikipedia](/huffman-coding/huffman_tree.svg)

For more detailed information see the References section.

## Implementation
Here is my code, as simple as possible :).

First, design the interface:

Embed: `interface.cpp`

And here the actual implementation:

Embed: `implementation.cpp`

The full source code is in [this gist](https://gist.github.com/rendon/f085937b73f2f5121caa).

## Tests
Let's see if this really works and how good it is.

First a dummy text:

<pre>
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
</pre>

Original size:

<pre theme="slate">
ls -lh test1.txt
-rw-r--r-- 1 rafa rafa 201 Aug 28 10:19 test1.txt
</pre>

Compress:

<pre theme="slate">
./huffman encode test1.txt test1.out
</pre>

After compression (removing metadata, i.e. frequencies, byte and bit count):

<pre theme="slate">
ls -lh test1.out
-rw-r--r-- 1 rafa rafa 39 Aug 28 10:21 test1.out
</pre>

Wow! 162 bytes less.

Now something less contrived, let's compress the book "The Iliad" By Homer, you can find the text version [here](http://classics.mit.edu/Homer/iliad.mb.txt):

Original size:

<pre theme="slate">
ls -lh iliad.mb.txt
-rw-r--r-- 1 rafa rafa 790K Aug 28 10:12 iliad.mb.txt
</pre>

Compress:

<pre theme="slate">
./huffman encode iliad.mb.txt iliad.mb.out
</pre>

After compression:

<pre theme="slate">
ls -lh iliad.mb.out
-rw-r--r-- 1 rafa rafa 437K Aug 28 10:30 iliad.mb.out
</pre>

Not too bad, 353K of reduction.

To complete the tests, decompress the output files and verify that the result is the same as the original input.

<pre theme="slate">
./huffman decode iliad.mb.out original.iliad.mb.txt
diff iliad.mb.txt original.iliad.mb.txt
</pre>

The last command should output NOTHING, otherwise something went wrong.

## References
- [Text Compression with Huffman Coding ](https://www.youtube.com/watch?v=ZdooBTdW5bM)
- [Huffman Encoding Compression Algorithm](http://www.cprogramming.com/tutorial/computersciencetheory/huffman.html)
- [Huffman coding](http://en.wikipedia.org/w/index.php?title=Huffman_coding)
