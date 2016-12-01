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
