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
