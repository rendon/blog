paper = 0
File.readlines('input.txt').each do |line|
  next if line.length == ''
  dimensions = line.split('x').map(&:to_i).sort
  l, w, h = dimensions
  paper += (2 * l * w) + (2 * l * h) + (2 * w * h) + (l * w)
end
puts paper
