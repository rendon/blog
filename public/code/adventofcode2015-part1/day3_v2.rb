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
