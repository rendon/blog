---
tags:
    - algorithms
    - data-structures
    - post
created: 2016-12-01
updated: 2024-05-06
---
# Advent of code 2015 - part 1

I recently found out about [Advent of Code](https://adventofcode.com/), and as part of my preparation for this year's event I'm solving the puzzles of the previous event ([AdventofCode.com/2015](https://adventofcode.com/2015)), in this short series I'll publish my solutions with a brief explanation.

A brief explanation about how Advent of Code works, there's one puzzle every day from December 1st to the 25th, each puzzle has two versions so you can earn up to two stars for every puzzle.

## Day 1: Not Quite Lisp
Problem description: [day/1](http://adventofcode.com/2015/day/1).

### Solution
For v1: Just use a variable for the current floor, increase by one when we find a `(`, decrease by 1 when we find a `)`.

```ruby
#!/usr/bin/env ruby
input = File.read('input.txt')
sequence = input.split(//)
floor = 0
sequence.each do |s|
  if s == '('
    floor += 1
  else
    floor -= 1
  end
end
puts floor
```

For v2: Similar to v1, we just need to keep track of the positions.

```ruby
#!/usr/bin/env ruby
input = File.read('input.txt')
sequence = input.split(//)
floor = 0
sequence.each_with_index do |s, i|
  if s == '('
    floor += 1
  else
    floor -= 1
  end
  if floor == -1
    puts i + 1
    break
  end
end
```


## Day 2: I Was Told There Would Be No Math
Problem description: [day/2](http://adventofcode.com/2015/day/2).

### Solution
For v1: Read all lines, parse the three integers and just apply the formula from the problem description.

```ruby
paper = 0
File.readlines('input.txt').each do |line|
  next if line.length == ''
  dimensions = line.split('x').map(&:to_i).sort
  l, w, h = dimensions
  paper += (2 * l * w) + (2 * l * h) + (2 * w * h) + (l * w)
end
puts paper
```

For v2: Take the lowest 2 values (out of 3) and compute the perimeter, plus the product of all of them.

```ruby
ribbon = 0
File.readlines('input.txt').each do |line|
  dimensions = line.split('x').map(&:to_i).sort
  l, w, h = dimensions
  ribbon += (2 * l + 2 * w) + (l * w * h)
end
puts ribbon
```

## Day 3: Perfectly Spherical Houses in a Vacuum
Problem description: [day/3](http://adventofcode.com/2015/day/3).

### Solution
For v1: A simulation problem, update your position in a 2-dimensional grid with every command, use a table to keep track of the unique positions you've been in.

```ruby
grid = {[0, 0] => true}
r = 0
c = 0
File.read('input.txt').split(//).each do |i|
  r += 1 if i == 'v'
  r -= 1 if i == '^'
  c += 1 if i == '>'
  c -= 1 if i == '<'
  grid[[r, c]] = true
end
puts grid.length
```

For v2: Likewise, except that you have to alternate commands with Robo-Santa, the first command is for Santa, the second one is for Robo-Santa, etc.

```ruby
grid = {[0, 0] => true}

def move(r, c, d)
  r += 1 if d == 'v'
  r -= 1 if d == '^'
  c += 1 if d == '>'
  c -= 1 if d == '<'
  return r, c
end

sr = 0
sc = 0
rr = 0
rc = 0
File.read('input.txt').split(//).each_with_index do |d, i|
  if i % 2 == 0
    sr, sc = move(sr, sc, d)
    grid[[sr, sc]] = true
  else
    rr, rc = move(rr, rc, d)
    grid[[rr, rc]] = true
  end
end
puts grid.length
```

## Day 4: The Ideal Stocking Stuffer
Problem description: [day/4](http://adventofcode.com/2015/day/4).

### Solution
For v1: Well, I just brute-forced this one, used Ruby's `Digest::MD5` to compute the checksum.

```ruby
require 'digest'

secret = 'bgvyzdsv'
key = 1
loop do
  md5 = Digest::MD5.new
  md5.update(secret + key.to_s)
  hex = md5.hexdigest
  if hex.start_with?('00000')
    puts key
    break
  end
  key += 1
end
```

For v2: The same as v1, just add one more zero.

```ruby
require 'digest'

secret = 'bgvyzdsv'
key = 1
loop do
  md5 = Digest::MD5.new
  md5.update(secret + key.to_s)
  hex = md5.hexdigest
  if hex.start_with?('000000')
    puts key
    break
  end
  key += 1
end
```

## Day 5: Doesn't He Have Intern-Elves For This?
Problem description: [day/5](http://adventofcode.com/2015/day/5).

### Solution
For v1: Just follow the instructions **carefully** and you should be able to solve this problem.

```ruby
def nice?(word)
  chars = word.split(//)
  vowels = {
    'a' => 0,
    'e' => 0,
    'i' => 0,
    'o' => 0,
    'u' => 0
  }
  forbidden = {
    'ab' => true,
    'cd' => true,
    'pq' => true,
    'xy' => true
  }
  consecutive = false
  0.upto(chars.length - 2) do |i|
    pair =  chars[i] + chars[i+1]
    return false if forbidden[pair] == true
    consecutive ||= (chars[i] == chars[i+1])
  end

  return false unless consecutive

  chars.each do |c|
    vowels[c] += 1 if vowels[c]
  end
  return vowels.values.reduce(&:+) >= 3
end

puts File.readlines('input.txt').select {|w| nice?(w.chomp) }.length
```

For v2: Just follow the instructions **even more carefully**, I was trapped by a moment by a pesky bug in this version.

```ruby
def nice?(word)
  chars = word.split(//)
  pairs = {}
  contains_pair = false
  prev = ''
  (chars.length - 1).downto(1) do |i|
    pair = chars[i-1] + chars[i]
    contains_pair ||= (pairs[pair] == true)
    pairs[prev] = true
    prev = pair
  end
  return false unless contains_pair

  0.upto(chars.length - 3) do |i|
    return true if chars[i] == chars[i+2]
  end
  false
end

puts File.readlines('input.txt').select {|w| nice?(w.chomp) }.length
puts nice?('qjhvhtzxzqqjkmpb')
puts nice?('xxyxx')
puts nice?('uurcxstgmygtbstg')
puts nice?('ieodomkazucvgmuy')
```
