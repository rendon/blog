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
