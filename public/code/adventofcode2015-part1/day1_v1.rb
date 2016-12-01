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
