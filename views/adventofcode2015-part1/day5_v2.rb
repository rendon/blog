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
