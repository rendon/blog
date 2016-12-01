ribbon = 0
File.readlines('input.txt').each do |line|
  dimensions = line.split('x').map(&:to_i).sort
  l, w, h = dimensions
  ribbon += (2 * l + 2 * w) + (l * w * h)
end
puts ribbon
