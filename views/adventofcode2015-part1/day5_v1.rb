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
